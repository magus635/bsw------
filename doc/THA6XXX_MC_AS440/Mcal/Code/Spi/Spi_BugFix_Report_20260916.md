# Spi.c Bug 修复报告 — 2026-09-16 ～ 2026-09-17

范围：`Mcal/Code/Spi/src/Spi.c`（AUTOSAR 4.4.0 SPI Handler/Driver, THA6xxx Cortex-R52）。
本文档记录：Bug 10（GPIO CS 相位检查）、DeInit/SyncTransmit 竞态问题从 v1 到 v3 的完整演变（v1/v2 均被证明不完整，v3 是根因修复）、以及两轮独立审查（一次系统性人工复核 + 一次独立 code-review 技能审查）的发现。

项目目录未纳入 git 管理，因此变更历史以文件备份 + 本文档的形式留存。

**重要提示：v2 已被证明存在缺陷，不要参照 v2 的设计。** 第 3 节记录了 v2 为什么不够，第 4 节是最终的 v3 设计，只有 v3 是当前代码的真实状态。

---

## 目录

1. [Bug 10：GPIO CS 释放时机检查遗漏 TRAIL_STROBE 阶段](#bug-10)
2. [Bug 11：DeInit 可能在 Sequence 执行期间被错误接受（竞态条件）](#bug-11)
   - [v1 修复（仅覆盖同步侧）](#v1)
   - [系统性复核发现 v1 不完整（异步侧遗漏）](#review)
   - [v2 修复（统一方案，同时覆盖同步与异步）](#v2)
3. [独立 code-review 发现 v2 本身存在缺陷](#v2-review)
4. [v3 修复：根本重构（当前状态）](#v3)
5. [系统性复核总表（全部 12 项修复，针对 v1 时点）](#review-table)
6. [验证方式与已知局限](#limitations)
7. [备份文件索引](#backups)

---

<a id="bug-10"></a>
## 1. Bug 10：GPIO CS 释放时机检查遗漏 TRAIL_STROBE 阶段

### 1.1 问题描述

函数 `Spi_WaitPhaseStatus`（`Spi.c:4633`）在 `SPI_CUSTOMIZED_CS_EN == STD_ON` 且 `PullCSbyData == TRUE` 时被调用（调用点 `Spi.c:1798`、`Spi.c:3069`），用于在通过 GPIO 翻转释放片选（CS）信号**之前**，等待 ESPI 硬件完成当前的数据传输阶段。如果 CS 在硬件尚未完成传输时就被释放，会导致从机采样到错误的电平/时序，产生数据错误。

### 1.2 根因分析

ESPI 硬件的相位标志（`SDK/espi/inc/espi_hal.h`）定义了完整的状态机：

```c
#define ESPI_PHASE_FLAG_WAIT         (0x0U)
#define ESPI_PHASE_FLAG_IDLEA        (0x10000000U)
#define ESPI_PHASE_FLAG_IDLEB        (0x20000000U)
#define ESPI_PHASE_FLAG_LEAD         (0x30000000U)
#define ESPI_PHASE_FLAG_DATA         (0x40000000U)
#define ESPI_PHASE_FLAG_TRAIL        (0x50000000U)
#define ESPI_PHASE_FLAG_EXPECT       (0x60000000U)
#define ESPI_PHASE_FLAG_LEAD_STROBE  (0x70000000U)
#define ESPI_PHASE_FLAG_TRAIL_STROBE (0x80000000U)
```

修复前的判定条件（`Spi.c:4646-4647`，行号为修复前版本）：

```c
if((ESPI_PHASE_FLAG_WAIT == RegValue) ||
   (ESPI_PHASE_FLAG_EXPECT == (RegValue & ESPI_PHASE_FLAG_EXPECT)))
{
    RegStatus = TRUE;
}
```

第二个条件用掩码 `RegValue & ESPI_PHASE_FLAG_EXPECT`（即 `RegValue & 0x60000000`）判断高 4 位是否为 `0x6`。按位与运算的结果是：

| RegValue | `RegValue & 0x60000000` | 是否满足 `== 0x60000000` |
|---|---|---|
| `EXPECT` (0x6...) | 0x60000000 | 是 |
| `LEAD_STROBE` (0x7...) | 0x60000000 | 是（0111 & 0110 = 0110）|
| `TRAIL_STROBE` (0x8...) | 0x00000000 | **否**（1000 & 0110 = 0000）|

即该条件恰好覆盖 `EXPECT` 与 `LEAD_STROBE`，但**不包含 `TRAIL_STROBE`**——数据传输真正结束前的最后一个尾部选通阶段。函数会在硬件仍处于 `TRAIL_STROBE` 时判定"可以释放 CS"，与传输尚未完全结束的事实矛盾。

### 1.3 修复方案

在判定条件中补充对 `TRAIL_STROBE` 的显式检查（`Spi.c:4660-4663`）：

```c
if((ESPI_PHASE_FLAG_WAIT == RegValue) ||
   (ESPI_PHASE_FLAG_EXPECT == (RegValue & ESPI_PHASE_FLAG_EXPECT)) ||
   (ESPI_PHASE_FLAG_TRAIL_STROBE == RegValue))
{
    RegStatus = TRUE;
}
```

### 1.4 验证

- 代码审查：确认新增分支语义正确，三个分支覆盖 `WAIT`、`EXPECT`/`LEAD_STROBE`、`TRAIL_STROBE`。
- Diff 审查：改动局部，仅新增 1 行 + 相邻括号调整，未影响其他代码。
- CRLF/空白：与原文件一致。
- gcc 编译：**未执行**（见 [第 4 节](#limitations)）。
- 板级测试：**未执行**。
- 后续系统性复核（fork，见第 3 节）：**CONFIRMED CORRECT**，独立重新核对了三分支的存在与语义。

---

<a id="bug-11"></a>
## 2. Bug 11：DeInit 可能在 Sequence 执行期间被错误接受（竞态条件）

### 2.1 问题描述

`Spi_DeInit`（`Spi.c:5383`）在调用 `Spi_DeInitDriver` 复位硬件之前，通过 `Spi_GetDriverStatus`（`Spi.c:1362`，调用点 `Spi.c:5429`）判断驱动当前是否为 `SPI_BUSY`；只有非 BUSY 时才接受 DeInit（AUTOSAR SWS_Spi_00253）。同一个 `Spi_GetDriverStatus` 也被公开 API `Spi_GetStatus`（`Spi.c:6168`，调用点 `Spi.c:6202`）复用。

修复前的实现（原始版本）只遍历逐个物理单元（PhyUnit）的 `PhyUnitStatus`：

```c
SpiStatus = SPI_IDLE;
for(PhyUnitIndex = 0U; ... ; PhyUnitIndex++)
{
    SpiStatus = Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].PhyUnitStatus;
}
```

问题在于：一个 Sequence 在执行过程中，其占用的 PhyUnit 的 `PhyUnitStatus` 并非在整个 Sequence 期间持续保持 `SPI_BUSY`——在某些正常的中间状态下会被短暂设回 `SPI_IDLE`，即使 Sequence 尚未结束。

<a id="v1"></a>
### 2.2 v1 修复：同步侧的 Job-间隙窗口

**根因（同步侧）**：`Spi_SyncTransmit` 的内部实现（`Spi.c:1656` 附近的 Job 循环）里，**每完成一个 Job**（即使 Sequence 中还有后续 Job 待处理）都会：

1. 进入 `SyncTransmit` 临界区，把该 PhyUnit 的 `PhyUnitStatus` 设回 `SPI_IDLE`；
2. 退出临界区（中断重新使能）；
3. 调用 `JobEndNotification`（用户回调，耗时不确定）；
4. 在下一次循环迭代中才重新进入临界区、把 `PhyUnitStatus` 设回 `SPI_BUSY`。

在步骤 2～4 之间，如果调用 `Spi_DeInit`：`Spi_GetDriverStatus` 会看到该 PhyUnit 为 `SPI_IDLE`，从而错误地接受 DeInit——即使 Sequence 显然还没跑完，外层循环仍会继续尝试驱动一个刚被复位（甚至可能被后续代码以不同配置重新 Init）的硬件单元，导致未定义行为。

**v1 修复方案**：注意到代码里已经存在一个专门跟踪"整个 Sequence 期间（含 Job 之间）"状态的机制——`PhyUnitBusySyncStatusPtr`位掩码。它在 `Spi_SyncTransmit` 开始时设置保留位（`Spi.c` 原 6613 行附近），只有在整个 Sequence 完全结束（成功或失败）之后才清除（原 6692 行附近），中间不会因为 Job 切换而被清空。

在 `Spi_GetDriverStatus` 中加入该位掩码的检查：

```c
SpiStatus = SPI_IDLE;
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
if (0U != *(Spi_CoreStatus[CoreId]->PhyUnitBusySyncStatusPtr))
{
    SpiStatus = SPI_BUSY;
}
#endif
for(PhyUnitIndex = 0U; ... ) { ... }
```

`#if` 保护是必需的：该字段在 `Spi_GeneralTypes.h:520-523` 中被同样的条件包裹，`SPI_LEVEL1`（纯异步配置）下根本不存在这个字段，直接引用会编译失败。

**v1 验证**：CRLF 一致、diff 审查通过、代码审查确认逻辑正确。备份：`Spi.c.deinit_race`（v1 修复前状态）。

<a id="review"></a>
### 2.3 系统性复核发现 v1 不完整

在完成 v1 后，应用户要求对全部历史修复做了一次系统性复核（详见第 3 节）。复核独立重新分析了 v1 的逻辑，发现：

**v1 只堵住了同步侧的窗口，异步侧存在一个结构相同、未被覆盖的镜像窗口。**

`Spi_AsyncTransmit`（`Spi.c:5658`）的实现中：

```c
/* Spi.c:5803 —— 在 AsyncTransmit 临界区内 */
SPI_SEQ_STATUS(CoreId, Sequence) = SPI_SEQ_PENDING;
...
/* Spi.c:5826 —— 临界区退出，中断重新使能 */
SPI_EXIT_CRITICAL_SECTION(AsyncTransmit);
/* Spi.c:5830 —— 在临界区外调用，真正把目标 PhyUnit 设为 SPI_BUSY 的是这里面 */
RetResult = Spi_AsyncScheduleJob(CoreId, *JobIndexPtr, FALSE);
```

`SeqResult` 在第 5803 行已经被设为 `SPI_SEQ_PENDING`（Sequence 已经"占用"），但真正让目标 PhyUnit 的 `PhyUnitStatus` 变为 `SPI_BUSY` 的动作，在 `Spi_AsyncScheduleJob` 内部（临界区**之外**）才发生。

在第 5826～5830 行之间（以及 `Spi_AsyncScheduleJob` 内部真正置忙之前的执行时间窗口内），如果同一核心上（例如某个更高优先级的中断上下文）调用了 `Spi_DeInit`：

- 目标 PhyUnit 的 `PhyUnitStatus` 仍为 `SPI_IDLE`（尚未被置忙）；
- v1 新增的 `PhyUnitBusySyncStatusPtr` 检查对异步 Sequence 没有意义——该位掩码是纯同步机制，异步路径完全不会设置它；
- `Spi_GetDriverStatus` 因此返回 `SPI_IDLE`，`Spi_DeInit` 被错误接受，尽管该 Sequence 已经是 `SPI_SEQ_PENDING`。

**失败场景**：`Spi_AsyncTransmit` 刚返回（或即将返回）`PENDING`、目标硬件尚未被真正标记为占用的极窄时间片内，同核心的某中断服务程序调用 `Spi_DeInit`。

这不是 v1 引入的新问题，而是 v1 的覆盖范围本就只针对同步侧的 Job-间隙，异步侧这个结构类似的窗口自始就没有被任何一版修复处理过。

<a id="v2"></a>
### 2.4 v2 修复：统一方案，同时覆盖同步与异步

放弃"针对同步侧位掩码打补丁"的思路，改用一个更根本、更通用的判据：**是否存在任何 Sequence 处于 `SPI_SEQ_PENDING` 状态**。

依据：
- `SeqResult` 字段（`Spi_GeneralTypes.h:354`）在 `Spi_SequenceStateType` 结构体最顶部声明，**没有任何 `#if` 包裹**，在全部 `SPI_LEVEL_DELIVERED` 配置（L0/L1/L2）下都无条件存在。
- 无论同步还是异步路径，`SeqResult` 被设为 `SPI_SEQ_PENDING` 的时刻，都严格早于各自窗口打开的时刻：
  - 同步侧：与原 `PhyUnitBusySyncStatusPtr` 保留位在**同一个**临界区内一起设置；
  - 异步侧：在 `Spi_AsyncTransmit` 的 `AsyncTransmit` 临界区内（第 5803 行），早于该临界区退出（第 5826 行）、更早于 `Spi_AsyncScheduleJob` 真正置忙（第 5830 行内部）。
- 因此，用一次 `SeqResult == SPI_SEQ_PENDING` 的遍历，可以同时覆盖两侧的窗口，且不需要任何条件编译分支。

最终代码（`Spi.c:1362-1400`）：

```c
static FUNC(Spi_StatusType, SPI_PRIVATE_CODE) Spi_GetDriverStatus
(
    Mcal_CoreType CoreId
)
{
    Spi_StatusType                  SpiStatus;
    Spi_HWUnitType                  PhyUnitIndex;
    Spi_SequenceType                SeqIndex;
    /*  SWS_Spi_00346 / SWS_Spi_00347 ... */
    SpiStatus = SPI_IDLE;
    /* A Sequence is SPI_SEQ_PENDING for its whole duration, including gaps where
       PhyUnitStatus is briefly IDLE: between two Jobs of an ongoing synchronous
       Sequence, and between Spi_AsyncTransmit marking the Sequence PENDING and
       Spi_AsyncScheduleJob marking its first Job's PhyUnit BUSY. Report BUSY while any
       Sequence is still PENDING, so DeInit/GetStatus are not fooled by either gap. */
    for(SeqIndex = 0U; ((SeqIndex < Spi_ConfigPtr->CoreConfigPtr[CoreId]->MaxSeq) &&
        (SPI_IDLE == SpiStatus)); SeqIndex++)
    {
        if (SPI_SEQ_PENDING == Spi_CoreStatus[CoreId]->SequenceStatusPtr[SeqIndex].SeqResult)
        {
            SpiStatus = SPI_BUSY;
        }
    }
    /* Check if there is any hardware that is not IDLE */
    for(PhyUnitIndex = 0U; ... ; PhyUnitIndex++)
    {
        SpiStatus = Spi_CoreStatus[CoreId]->PhyUnitStatusPtr[PhyUnitIndex].PhyUnitStatus;
    }

    return SpiStatus;
}
```

v1 中针对 `PhyUnitBusySyncStatusPtr` 的 `#if`/检查被完全移除，由这个统一循环取代。

**排除死锁风险**：另外核实了调度失败路径——若 `Spi_AsyncScheduleJob` 未能启动 Job（HW 不可用等），会走 `Spi_AsyncAbortJob` → `Spi_AsyncReportAbortedJob`，正确把 `SeqResult` 从 `PENDING` 清回 `FAILED`（或在 Sequence 正常完成时清回 `OK`）。因此新的检查不会因为某次调度失败而让 `SPI_SEQ_PENDING` 永久悬挂，不会导致 `Spi_DeInit` 被永久阻塞。

### 2.5 验证

- 代码审查：三次独立推导（v1 设计、复核发现问题、v2 重新设计）均可自洽。
- Diff 审查（v1→v2）：改动局部，仅函数体内部，无扩散。
- CRLF/空白：与备份一致。
- 类型核对：`Spi_SequenceType`（`MaxSeq` 类型）与新增的 `SeqIndex` 变量类型一致；`SequenceStatusPtr[SeqIndex]` 直接索引方式与 `Spi_DeInitDriver` 中已有的同类循环写法一致。
- gcc 编译：**未执行**。
- 板级测试：**未执行**。

---

<a id="v2-review"></a>
## 3. 独立 code-review 发现 v2 本身存在缺陷

2026-09-17，用户要求"重新 review spi 的有关代码"（一次全新的、开放式审查，不同于第 5 节那次针对历史修复的回顾性验证）。启动了 `code-review` 技能，其审查范围按协议自动选定为"最近一次尚未被独立审查过的改动"——也就是 v2 相对于 v2-修复前备份（`Spi.c.deinit_race_v2`）的 diff，即 `Spi_GetDriverStatus` 这一处改动。

审查采用多角度并行查找 + 独立验证 + 复扫的流程（7 个角度并行查找 → 去重得 12 个候选 → 逐个独立验证 → 复扫查漏），发现 v2 存在真实缺陷，而不是我们此前以为的"完整修复"。核心发现（已经过本人独立重读代码逐条核实，全部属实）：

### 3.1 v2 把窗口从"Job 之间"搬到了"收尾阶段"，而不是消除它

`Spi_GetDriverStatus` 的 v2 实现检查 `SeqResult == SPI_SEQ_PENDING`。但 `SeqResult` 被设为终态（`SPI_SEQ_OK`/`SPI_SEQ_FAILED`）的时刻，早于该 Sequence"真正完全结束"的时刻：

- **同步侧**：`Spi_SyncTransmit` 在 `SPI_SEQ_STATUS(...) = SPI_SEQ_OK;`（原第 6653 行）之后，还要经过一个 Job 循环（清除 `PhyUnitBusySyncStatusPtr`、调用 `Spi_AsyncScheduleNextJob` 调度排队的异步 Job）以及 `SeqEndNotificationPtr()` 回调，才算真正收尾完毕。这中间没有临界区连续保护。
- **异步侧**：`Spi_AsyncJobTransferFinished`/`Spi_AsyncAbortJob` 同理，`SeqResult` 在通知回调、`Spi_AsyncScheduleNextJob` 之前就已经变为终态。

也就是说，v2 的 `SeqResult` 扫描会在"收尾工作尚未做完"的这段时间里，提前报告 `SPI_IDLE`——这正是这一整条修复链本来要消除的那类 bug，只是窗口从"两个 Job 之间"平移到了"传输完成到收尾完成之间"。

**具体后果**：如果 `Spi_DeInit` 在这个窗口内被（错误地）接受：
1. `Spi_DeInitDriver` 会无条件把所有 `SeqResult`/`JobResult` 覆盖为 `SPI_SEQ_OK`/`SPI_JOB_OK`（`Spi.c` 原 5231/5242 行附近），不检查旧值——一个刚刚真实发生的 `SPI_SEQ_FAILED` 会被静默抹除，应用层永远看不到真正的失败。
2. 若 DeInit 抢先执行了 `Espi_Hal_ResetModule`，`Spi_SyncTransmit` 收尾阶段里仍会调用 `Spi_AsyncScheduleNextJob`——它会看到目标 PhyUnit 已经是 `SPI_UNINIT`（被复位过），内部 guard 会静默丢弃这次调度（不崩溃，但排队的异步 Job 被孤儿化、永不执行、无任何报错）；而 `SeqEndNotificationPtr()` 依然会在驱动已经被拆除之后触发到应用层代码。

### 3.2 v2 完全没有解决它本来要解决的问题（sync/async 并发竞态）

`Spi_SyncCheckPhyUnitsFree`——真正阻止一个**并发的 `Spi_SyncTransmit` 调用**在某 PhyUnit 上启动的把关函数——从始至终只检查 `PhyUnitBusySyncStatusPtr`（纯同步专用位掩码）和 `PhyUnitStatus`，从来不检查 `SeqResult`。

也就是说，v1 最初想解决的窗口（`Spi_AsyncTransmit` 把 `SeqResult` 设为 `PENDING` 之后、`Spi_AsyncScheduleJob` 真正把目标 PhyUnit 置为 `SPI_BUSY` 之前的间隙），对于 `Spi_GetDriverStatus`（服务于 `Spi_DeInit`/`Spi_GetStatus`）这一个消费者而言，v2 确实堵上了；但对于 `Spi_SyncCheckPhyUnitsFree`（服务于"是否可以启动一个新的同步 Sequence"）这另一个消费者而言，v1 和 v2 都从未触及它，这个窗口原封不动地还在——一个同步 Sequence 完全可能在异步 Sequence 刚刚声明、尚未真正占用某 PhyUnit 的瞬间，抢先在同一个 PhyUnit 上启动，两者在硬件层面产生真实的数据竞争。

（第 3 组、第 4 组共另有 6 项较低优先级的发现——性能类：v2 的 O(MaxSeq) 扫描在原来 `SPI_LEVEL1` 下是零开销、现在变成每次 `Spi_GetStatus`/`Spi_DeInit` 都有非零的裸中断关闭时间，随 `MaxSeq` 线性增长；风格类：与 `Spi_InitDriver`/`Spi_DeInitDriver` 中已有的同款遍历骨架三次重复；以及两个独立、非本次改动引入的既有问题——DET 关闭时 `NumJobs==0` 的 Sequence 导致无符号下溢和越界解引用，DET 关闭时 `Spi_DeInit` 缺少对 `Spi_CoreStatus[CoreId]` 的 NULL 检查。这两个既有问题不在 v3 的修复范围内，见第 6 节。）

### 3.3 根因

审查给出的诊断：`Spi_GetDriverStatus`、`Spi_SyncCheckPhyUnitsFree`、`Spi_AsyncScheduleJob` 的可用性检查，三者各自从三个独立维护的标志（`PhyUnitStatus`、`PhyUnitBusySyncStatusPtr`、`SeqResult`）里挑一个子集来重新推导"是否忙"，而不是共用一个在"真正开始"时设置一次、"真正结束"时清除一次的权威指示器。这是同一个函数第二次因为这一类问题被打补丁（v1 补同步侧，v2 补异步侧但又漏了一个消费者），只打补丁不会收敛，必须做架构层面的修复。用户在看到这个诊断后，明确选择"根本重构"而非继续打补丁。

---

<a id="v3"></a>
## 4. v3 修复：根本重构（当前状态）

### 4.1 设计

新增一个独立的状态字段 `PhyUnitPendingTeardownStatusPtr`（`uint16` 位掩码，逐 PhyUnit 一个 bit），语义精确定义为：

> bit x = 1，表示 PhyUnit x 从属于一个已经被声明（同步或异步）、但其收尾工作——**包括结束通知回调**——尚未完成的 Sequence。

这个字段被设计为与现有的 `PhyUnitBusySyncStatusPtr` **完全独立、职责分离**：

| 字段 | 用途 | 清除时机 |
|---|---|---|
| `PhyUnitBusySyncStatusPtr`（既有） | 供 `Spi_AsyncScheduleJob` 做调度判断：一个排队的异步 Job 是否可以在这个 PhyUnit 上启动 | 尽早清除（在 `Spi_AsyncScheduleNextJob` 调用之前）——若挪到通知之后会卡住排队的异步 Job，见下 |
| `PhyUnitPendingTeardownStatusPtr`（新增） | 供 `Spi_GetDriverStatus`/`Spi_SyncCheckPhyUnitsFree` 做"忙碌探测"判断 | 收尾工作**全部完成（含通知回调）之后**才清除 |

**为什么不能复用/延后清除 `PhyUnitBusySyncStatusPtr` 本身**：该位在 `Spi_SyncTransmit` 收尾阶段的清除，是排队的异步 Job 能被 `Spi_AsyncScheduleNextJob` 正确调度启动的前提条件。如果把这个清除动作也推迟到通知回调之后，会导致收尾阶段本应被立即调度的排队异步 Job，白白多等一整个通知回调的时间（且如果通知回调里又同步等待某些外部状态，甚至可能引入新的死锁）。这正是不能简单"移动现有标志清除时机"、而必须新增一个独立标志的原因。

### 4.2 新字段的存储

不同于 `PhyUnitBusySyncStatusPtr`（受 `#if SPI_LEVEL0||SPI_LEVEL2` 保护），新字段在 `Spi_CoreStatusType`（`Spi_GeneralTypes.h`）中**无条件声明**，因为同步和异步任一侧存在就需要它。对应地在 `Spi.c` 中，为支持的 4 个核心（Core0–Core3，`MCAL_NUMBER_OF_CORES` 可配置到 4）分别新增了无条件的静态存储变量 `Spi_PendingTeardownStatusCoreN`，并加入对应的 `Spi_StatusSetCoreN` 初始化列表。这些存储变量和其他既有的状态变量（如 `Spi_SyncTransferStatusCoreN`）一样，是 `Spi.c` 内部的本地静态变量，不依赖任何生成的配置文件，因此新增字段是完全自包含、可控的改动。

### 4.3 设置点（2 处）

- **`Spi_SyncTransmit`**：在为 Sequence 设置 `SPI_SEQ_PENDING` 之后、原有"Reserve the used HW units for the whole Sequence"循环（同时设置 `PhyUnitBusySyncStatusPtr`）里，为同一批 PhyUnit 顺带设置新标志位，同一个临界区内完成。
- **`Spi_AsyncTransmit`**：在为 Sequence 设置 `SPI_SEQ_PENDING` 之后、原有把每个 Job 状态设为 `SPI_JOB_QUEUED` 的循环里，为该 Sequence 涉及的每一个 PhyUnit 顺带设置新标志位，同一个临界区内完成。

两处都遵循与既有同步侧设计一致的哲学：**整个 Sequence 期间，其涉及的全部 PhyUnit 都视为被保留**，即使某一时刻只有其中一个 PhyUnit 在物理传输——这不是本次新增的取舍，而是延续了 `PhyUnitBusySyncStatusPtr` 原有的设计惯例。

### 4.4 清除点（同步侧 1 处，异步侧 4 处）

**同步侧**（`Spi_SyncTransmit`）：新增一个循环，位置在"清除 `PhyUnitBusySyncStatusPtr`→调度排队异步 Job"和"调用 `SeqEndNotificationPtr()`"两步都完成**之后**，遍历该 Sequence 的全部 Job，清除各自 PhyUnit 的新标志位。

**异步侧**：新增 helper 函数 `Spi_AsyncReleaseSeqPhyUnits(CoreId, SeqCfgPtr)`（自带 `AsyncTransmit` 临界区，遍历 `SeqCfgPtr` 的全部 Job 清位），在恰好 4 个"Sequence 真正、完全终结"的地方调用，这 4 处是通过系统性追踪代码里所有把 `SeqResult` 写为终态的位置、逐一确认后得出的完整集合（不多不少）：

1. `Spi_AsyncJobTransferFinished` 的 CANCELLED/FAILED 分支（`Spi_AsyncUnlockRemainingJobs` + 通知之后）；
2. `Spi_AsyncJobTransferFinished` 的正常完成分支（`SeqResult=SPI_SEQ_OK` + 通知之后）；
3. `Spi_AsyncReportAbortedJob`——**特别处理了 `CallNotification == FALSE` 的情况**：这是 `Spi_AsyncTransmit` 第一个 Job 就调度失败、E_NOT_OK 同步返回给调用者、不调用任何通知回调的路径。即便不调用通知，Sequence 的生命周期也已经真正终结（不会再有回调），所以清除逻辑被放在"是否调用通知"判断**之外**，只要 `SeqCfgPtr != NULL_PTR` 就执行；
4. `Spi_AsyncReportCancelledSeq`——该函数原本没有 `CoreId` 参数（因为不需要访问 `Spi_CoreStatus`），为了调用 helper 函数，给它新增了 `CoreId` 参数，同步更新了全部 3 个调用点。

覆盖完整性的验证方法：不是靠"应该覆盖到了"的直觉，而是逐一列出全部会把 `Spi_AsyncAbortJob` 与 `Spi_AsyncReportAbortedJob`（负责实际中止和实际报告两个动作）配对起来的调用点——全文件共 5 对，逐一确认每一对都通过局部变量或输出参数正确关联，无遗漏、无错配。

### 4.5 消费者侧改造（2 处）

- **`Spi_GetDriverStatus`**：从 v2 的 `for` 循环扫描全部 Sequence（`O(MaxSeq)`，且运行在调用者的裸 `SuspendAllInterrupts()` 临界区内）简化为一次 `*(...PhyUnitPendingTeardownStatusPtr) != 0` 的位运算判断（`O(1)`）。这同时修复了独立审查中提到的一个 v2 引入的次要问题：v2 的扫描循环使得每次 `Spi_GetStatus()`/`Spi_DeInit()` 调用关中断的时长随 `MaxSeq` 线性增长，且这在原来 `SPI_LEVEL1`（纯异步）配置下是完全不需要付出的成本（原 `PhyUnitBusySyncStatusPtr` 检查受 `#if` 保护，在 L1 下编译为空）。v3 版本虽然不再有这个 `#if`（因为字段本身在 L1 下也需要），但整个检查退化为一次位运算，性能影响可忽略。
- **`Spi_SyncCheckPhyUnitsFree`**：新增一条与既有 `PhyUnitBusySyncStatusPtr` 检查并列的判断——`SeqCfgPtr->MaskSeqUsedPhyUnit & *(...PhyUnitPendingTeardownStatusPtr)` 非零则拒绝启动。这是 3.2 节所述"v1/v2 都未触及"的那个消费者，只有加上这一条，sync 与 async 之间的并发抢占窗口才算真正被堵住。

`Spi_AsyncScheduleJob` 内部原有的可用性判断**未被改动**——它继续只检查 `PhyUnitBusySyncStatusPtr`，不检查新标志，这是刻意的：如果检查新标志，一个异步 Sequence 会在自己刚刚为自己设置的位上把自己挡住，造成死锁。新标志只服务于"忙碌探测"这一个用途，不参与任何调度决策，这正是它与 `PhyUnitBusySyncStatusPtr` 分离存在的原因。

### 4.6 验证

- **Diff 审查**：对照 `Spi.c.deinit_race_v2`（v2 修复前的备份，同时也是本次 v3 改动前唯一存在的备份点）做了全文件级别的 diff，用锚点重同步算法识别出全部 30 个差异块，逐块核对，每一块都精确对应上述某一处预期改动，没有发现任何意外或多余的修改。少数几处显示为"移除了行尾空格"的差异，经字节级别核实，确认只是 Edit 工具在处理相邻行时的已知副作用（空白字符层面），没有丢失任何实际代码内容。
- **逻辑走查**：重新通读了 `Spi_SyncTransmit` 收尾部分的完整代码路径，确认"设置→（可能失败提前退出，此时新标志从未被设置）→清除"这条链路上，只要新标志被设置过，必然会执行到清除，不存在"设置了但没清除"的死锁分支。对异步侧同样做了 5 对 Abort/Report 调用点的逐一核对（见 4.4 节）。
- **类型与作用域核对**：新增的局部变量（`Spi_AsyncTransmit` 里的 `PendingJobCfgPtr`）没有与已有的、受 `#if SPI_DEV_ERROR_DETECT` 条件保护的同名变量冲突；`Spi_AsyncReleaseSeqPhyUnits`、`Spi_AsyncReportCancelledSeq` 的前向声明与实现签名一致。
- **特性守卫核对**：确认新增的 helper 函数体所在位置，落在既有的 `#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))` 大块保护范围内（通过检索该范围内所有 `#if`/`#endif` 配对，确认中间没有提前闭合）。
- **CRLF/编码**：与备份一致。
- gcc 编译：**未执行**（原因见第 6 节）。
- 板级测试、MISRA 分析：**未执行**。

### 4.7 v3 明确不处理的问题（超出本次范围）

以下是独立 code-review 在同一轮审查中发现的、与"DeInit/SyncTransmit 竞态"这一类问题无关的独立问题，v3 没有修复，如实记录：

- `SPI_DEV_ERROR_DETECT == STD_OFF` 时，`Spi_AsyncTransmit` 对 `NumJobs == 0` 的 Sequence 缺少防护：会导致 `RemainingJobs = NumJobsInSequence - 1U` 无符号下溢，以及对空 `JobIndexListPtr[0]` 的越界解引用。是否可达取决于具体配置是否会定义这样的 Sequence（该项目里看不到实际的 `Spi_Cfg.c` 生成文件来确认）。
- `SPI_DEV_ERROR_DETECT == STD_OFF` 时，`Spi_DeInit` 调用 `Spi_GetDriverStatus(CoreId)` 之前缺少对 `Spi_CoreStatus[CoreId]` 的 NULL 检查——这是本次改动之前就存在的暴露风险，v3 只是多加了一次同样未受保护的解引用，没有让风险面变得更大或更小。

---

<a id="review-table"></a>
## 5. 系统性复核总表（全部 12 项修复，针对 v1 时点）

应用户要求，对此前全部声称完成的修复（Bug 1–10、Bug 9 的两个批次、以及本文档 2.2 节的 v1 DeInit 修复）做了一次独立复核，不依赖历史记忆描述，全部基于复核时点的实际代码。

| # | 修复项 | 判定 | 备注 |
|---|---|---|---|
| 1 | `Spi_WriteIB(NULL)` 默认数据填充 | ✅ CONFIRMED CORRECT | `Spi.c:5558-5581`，`#if USAGE0/USAGE2` 包裹正确 |
| 2 | `Spi_AsyncJobTransferFinished` 的 `RemainingJobs` 检查 | ✅ CONFIRMED CORRECT | `Spi.c:3264-3350`，无越界解引用 |
| 3 | 长度检查 + Job 中止/取消链接 | ✅ CONFIRMED CORRECT | 用具体数值验证无双重 free / 漏 Job |
| 4 | `Spi_MainFunction_Handling` 轮询 | ✅ CONFIRMED CORRECT | `Spi.c:7119-7193`，无跳过/重复 |
| 5 | `Spi_SyncCheckPhyUnitsFree` 二次检查 | ✅ CONFIRMED CORRECT | 检查与保留在同一临界区内完成，无竞态窗口 |
| 6 | `Spi_Cancel` / CANCELLED 旁路移除 | ✅ CONFIRMED CORRECT | 未见旁路残留 |
| 7 | SRSTB 复位范围收窄 + `espi_hal.c` 掩码 | ✅ CONFIRMED CORRECT | 独立读取 SDK 源码确认掩码为 `0xFFFFF`，精确覆盖 [19:0] |
| 8 | `Spi_InitDriver` IB 初始化 + DET EB_UNIT 检查范围 | ✅ CONFIRMED CORRECT | IB TX buffer 确认未被自动填充（设计意图） |
| 9a | 同步失败即复位（Bug9 批次1） | ✅ CONFIRMED CORRECT | 所有失败路径汇入同一复位出口，无重复复位 |
| 9b | 异步 abort/超时监督全链路（Bug9 批次2） | ✅ CONFIRMED CORRECT | 所有权协议、DMA 两阶段中止顺序、迟到事件 guard、超时预算、`#error` 分支均核对无误 |
| 10 | GPIO CS 三阶段检查 | ✅ CONFIRMED CORRECT | 见第 1 节 |
| 11 (v1) | DeInit/SyncTransmit 竞态 | ⚠️ CONCERN FOUND → 已修复为 v2 | 见第 2 节，唯一发现问题的一项 |

**跨修复交互检查**：
- Bug6(Cancel)、Bug9批次2(abort/超时)、Bug11(DeInit race) 三者操作的状态变量（`SeqResult`、`JobResult`、`PhyUnitStatus`、`PhyUnitBusySyncStatusPtr`、`TimeoutCount`）逐一核对，未发现互相覆盖或遗漏同步点。
- 临界区嵌套：抽查了约 10 处有明确前置条件声明的函数调用点，均满足各自声明的前置条件，未发现嵌套违规。**这只是定向抽查，不是对全部约 50 个函数调用图的穷举证明**，全文件层面的嵌套安全性未被穷尽验证。

---

<a id="limitations"></a>
## 6. 验证方式与已知局限

本次及此前所有修复均遵循同一验证流程：备份原文件 → 按现有代码风格编辑（`/* #Violation: ... */`、`#if` 特性守卫、完整函数头注释块）→ diff 审查 → CRLF/尾随空白核对。

**未能完成的验证**：
- **gcc 编译矩阵**：此前修复曾用 `arm-none-eabi-gcc` 跑过 10 变体配置矩阵；本次尝试复现时发现该项目目录**没有完整构建系统**——`Spi_GeneralTypes.h` 包含的 `Mcal.h` 在整个项目树下都不存在，只靠手工拼接 `-I` 路径（Spi/include、DemoMcal 某型号 Spi_Cfg.h、SDK）无法编译通过。真正的构建大概率需要 DemoWorkspace 对应的 IDE/工程文件。此问题已记录，本次两处修复（Bug10、Bug11）均只做了代码审查 + diff 比对，**没有编译验证**。
- **板级测试**：未在任何硬件上运行。
- **MISRA 静态分析**：未执行。
- **临界区嵌套的穷举验证**：见第 3 节复核结果的说明。

---

<a id="backups"></a>
## 7. 备份文件索引

均位于 `Mcal/Code/Spi/src/` 目录下：

| 文件名 | 对应状态 |
|---|---|
| `Spi.c.bug9b` | Bug 10（GPIO CS 三阶段检查）修复前 |
| `Spi.c.deinit_race` | DeInit 竞态 v1 修复前（即 Bug10 修复后、v1 修复前） |
| `Spi.c.deinit_race_v2` | DeInit 竞态 v2 修复前（即 v1 修复后、v2/v3 修复前） |

**流程说明**：v3（根本重构）是直接在 v2 的基础上连续编辑完成的，中间没有单独创建"v3 修复前"的备份点——这是本次工作流程的一处疏漏（此前每次修复都遵循"先备份再编辑"，这次因为改动是连续演进的多个小步骤而漏掉了）。因此 `Spi.c.deinit_race_v2` 是当前最新的独立备份点，它同时早于 v2 和 v3。若需要回退，只能退回到这一个点（即回到 Bug10 完成后、DeInit 竞态问题完全未修复的状态），无法单独退回"只有 v2、没有 v3"的中间状态。

当前 `Spi.c` 是应用了 Bug10 + v3（根本重构版）之后的最新状态。`Spi_GeneralTypes.h` 也在 v3 中被修改（新增 `PhyUnitPendingTeardownStatusPtr` 字段），但从未被单独备份过——这是该文件第一次被这个修复系列改动。
