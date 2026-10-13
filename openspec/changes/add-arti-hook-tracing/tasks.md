## 1. 事件表与配置参数
- [x] 1.1 插件 `config/Os.xdm`：在 `OsOS` 下新增 `OsVendorArtiStateModel`（ENUM，默认 ENHANCED）和六个 `OsVendorArtiTrace<Class>` 布尔（SERVICECALLS 默认 false），描述注明是本 OS 私有参数
- [x] 1.2 `templates/Os/Os_ArtiEvents.m`：按 D1/D3 计算启用的 (context, class, event, TypeMap) 列表；服务调用只列内核已实现的 API
- [x] 1.3 测试夹具 `tests/generator/os_arti_fixture.py` 增加这些参数，以及自旋锁、应用 hook 等对象

## 2. ARTI 描述
- [x] 2.1 `Os_Arti.arxml`：新增 `TM_ArtiCoreIndex`、`TM_SpinlockId`，以及服务调用、hook 参数用的 TypeMap（`TM_ResourceId`、`TM_AlarmId`、`TM_CounterId`、`TM_ScheduleTableId`、`TM_ProtectionReaction`）
- [x] 2.2 `Os_Arti.arxml`：每个启用的事件生成一个 `ArtiHook`（Context/Class/Instance/EventName 加两个 TypeMap 引用），`ArtiOsInstanceHookRef` 引用全部 hook
- [x] 2.3 `ArtiStatesTaskEnhanced` 改为取自 `OsVendorArtiStateModel`（增强模型同时声明 Activated / Preempted / Released）
- [x] 2.4 测试：hook 与 ParamDef 结构一致，TypeMap 输入值在 0..65535 内，XSD 校验通过，类开关和模型切换的效果正确

## 3. 包装宏与 Mock
- [x] 3.1 `templates/Os/Os_ArtiHooks.h`（以及开关头文件 `Os_ArtiCfg.h`）：按类生成包装宏、应用专属 hook 的分发宏、服务调用辅助宏；关闭时全部为 `((void)0)` 或空
- [x] 3.2 `templates/Os/Os_Arti_Mock.h` / `.c`：对四个字面 token 做 `##` 拼接，只定义 `ArtiHook` 里列出的组合，并把事件记入按核分开的环形缓冲区
- [x] 3.3 测试：头文件里的 token 集合与 `ArtiHook` 的集合完全相等（两种模型、各种类开关组合）

## 4. 内核插桩（tr002_THA6_OS_Project/Os）
- [x] 4.1 `Os_TaskDynamicType` / `Os_IsrDynamicType` 增加 `ArtiState`（`#if` 保护），初始化放在 `OsTask_TaskInit`
- [x] 4.2 任务：ActivateTask、DoScheduling（换下、换上）、TerminateTask、ChainTask、Schedule、TaskDeinit
- [x] 4.3 事件：WaitEvent、SetEvent（本核与跨核两条路径）
- [x] 4.4 Cat2 ISR：PreISR、PostISR、PostServiceCallISR，含嵌套
- [x] 4.5 自旋锁：Get、TryToGet、Release、DeInit
- [x] 4.6 应用：Start、Restart、AllowAccess、Terminate
- [x] 4.7 Hook：Error、Protection（Return 参数为处置动作）、PreTask、PostTask、Startup、Shutdown，以及应用专属 hook
- [x] 4.8 服务调用：在现有 `OsOrti_ServiceStart/End` 处，只在应用上下文调用时发；非 StatusType 输出在失败时传无效值
- [x] 4.9 逐点核对 `_contextName` 并回写事件表（不能确定中断状态的路径改为本地加锁，见 design "实现中的调整"）

## 5. 验证
- [x] 5.1 本机 `arm-none-eabi-gcc` 用 t1 生成代码和 Mock 编译内核，两种模型、各种类开关都要编译通过
- [x] 5.2 `OsUseArti` 关闭时，改动前后的目标文件段内容相同（打开但六类全关时也相同）
- [x] 5.3 `tools/arti/check_event_stream.py` 及其单元测试（合法 / 非法迁移、ISR 时序、同核双 Running）
- [x] 5.4 输出上板用例清单与期望事件序列（`doc/ARTI/ARTI_hook_tracing.md` 第 5 节）
- [ ] 5.5 在目标板上运行上板用例并用检查脚本检查（用户执行）

## 6. 部署与文档
- [x] 6.1 新模板复制到插件 `generate_PB/` 和 t1 的 `templates/Os/`，t1 的 `Os.xdm` 同步；在 t1 里打开 `OsUseArti` 生成并核对（XSD 校验通过，内核用 Mock 编译通过）
- [x] 6.2 开发说明：修正 D1 中列出的不符之处，更新参数名、第九节待确认事项，补 D10 的默认约定
- [x] 6.3 集成手册要点：`doc/ARTI/ARTI_hook_tracing.md`
