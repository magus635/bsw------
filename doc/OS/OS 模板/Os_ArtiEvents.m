[!/* *********************************************************************************************
   FileName      : Os_ArtiEvents.m
   BSW Module    : Os
   brief         : The single list of ARTI hook events (SWS OS R21-11 7.17). Os_Arti.arxml (ArtiHook
                   containers), Os_ArtiHooks.h (kernel wrapper macros) and Os_Arti_Mock.h (strict mock)
                   are all generated from it, so the literal tokens cannot diverge.
                   openspec/changes/add-arti-hook-tracing/design.md D1, D2, D3, D7.

   Call "Os_ArtiEventList" with the Os module node as context. It sets:
     ArtiOn          'true' when OsUseArti is on
     ArtiEnhanced    'true' for OsVendorArtiStateModel = ENHANCED (also the default)
     ArtiOsName      <OS Short Name> = SHORT-NAME of the OsOS container (_instanceName)
     ArtiTaskClass   AR_CP_OSARTI_TASK or AR_CP_OS_TASK, '' when the class is off
     ArtiIsrClass    AR_CP_OSARTI_CAT2ISR or AR_CP_OS_CAT2ISR, '' when off
     ArtiTrace<Cls>  'true' / 'false' per class: Application Task Cat2Isr ServiceCalls Spinlock Hook
     ArtiEvents      'ctx:class:event:typemap;...' for every enabled event; typemap '-' = none.
                     The instance parameter is always decoded by TM_ArtiCoreIndex.
     ArtiServices    'Api/StartTypeMap/ReturnTypeMap,...' of all service calls the kernel implements, set
                     whether or not the class is traced ('-' = no type map, ReturnTypeMap 'x' = the
                     service never returns)
     ArtiAppHooks    'Hook/App/AppId,...' of the configured application-specific hooks
                     (Hook = ErrorHook, StartupHook or ShutdownHook; AppId = ApplicationType)
   A parameter that is missing from the configuration takes its Os.xdm default.
   ********************************************************************************************* */!][!//
[!VAR "ArtiEventsLoaded" = "'true'"!][!//
[!MACRO "Os_ArtiEventList"!][!//
[!VAR "ArtiOn" = "'false'"!][!IF "node:value(./OsOS/OsUseArti) = 'true'"!][!VAR "ArtiOn" = "'true'"!][!ENDIF!][!//
[!VAR "ArtiOsName" = "node:name(./OsOS)"!][!//
[!VAR "ArtiModel" = "'ENHANCED'"!][!IF "node:exists(./OsOS/OsVendorArtiStateModel) and node:value(./OsOS/OsVendorArtiStateModel) != ''"!][!VAR "ArtiModel" = "node:value(./OsOS/OsVendorArtiStateModel)"!][!ENDIF!][!//
[!VAR "ArtiEnhanced" = "'false'"!][!IF "$ArtiModel = 'ENHANCED'"!][!VAR "ArtiEnhanced" = "'true'"!][!ENDIF!][!//
[!VAR "ArtiTraceApplication" = "'true'"!][!IF "node:exists(./OsOS/OsVendorArtiTraceApplication) and node:value(./OsOS/OsVendorArtiTraceApplication) != ''"!][!VAR "ArtiTraceApplication" = "node:value(./OsOS/OsVendorArtiTraceApplication)"!][!ENDIF!][!//
[!VAR "ArtiTraceTask" = "'true'"!][!IF "node:exists(./OsOS/OsVendorArtiTraceTask) and node:value(./OsOS/OsVendorArtiTraceTask) != ''"!][!VAR "ArtiTraceTask" = "node:value(./OsOS/OsVendorArtiTraceTask)"!][!ENDIF!][!//
[!VAR "ArtiTraceCat2Isr" = "'true'"!][!IF "node:exists(./OsOS/OsVendorArtiTraceCat2Isr) and node:value(./OsOS/OsVendorArtiTraceCat2Isr) != ''"!][!VAR "ArtiTraceCat2Isr" = "node:value(./OsOS/OsVendorArtiTraceCat2Isr)"!][!ENDIF!][!//
[!VAR "ArtiTraceServiceCalls" = "'false'"!][!IF "node:exists(./OsOS/OsVendorArtiTraceServiceCalls) and node:value(./OsOS/OsVendorArtiTraceServiceCalls) != ''"!][!VAR "ArtiTraceServiceCalls" = "node:value(./OsOS/OsVendorArtiTraceServiceCalls)"!][!ENDIF!][!//
[!VAR "ArtiTraceSpinlock" = "'true'"!][!IF "node:exists(./OsOS/OsVendorArtiTraceSpinlock) and node:value(./OsOS/OsVendorArtiTraceSpinlock) != ''"!][!VAR "ArtiTraceSpinlock" = "node:value(./OsOS/OsVendorArtiTraceSpinlock)"!][!ENDIF!][!//
[!VAR "ArtiTraceHook" = "'true'"!][!IF "node:exists(./OsOS/OsVendorArtiTraceHook) and node:value(./OsOS/OsVendorArtiTraceHook) != ''"!][!VAR "ArtiTraceHook" = "node:value(./OsOS/OsVendorArtiTraceHook)"!][!ENDIF!][!//
[!IF "$ArtiOn != 'true'"!][!//
[!VAR "ArtiTraceApplication" = "'false'"!][!VAR "ArtiTraceTask" = "'false'"!][!VAR "ArtiTraceCat2Isr" = "'false'"!][!//
[!VAR "ArtiTraceServiceCalls" = "'false'"!][!VAR "ArtiTraceSpinlock" = "'false'"!][!VAR "ArtiTraceHook" = "'false'"!][!//
[!ENDIF!][!//
[!VAR "ArtiEvents" = "''"!][!//
[!/* ---- AR_CP_OS_APPLICATION (SWS_Os_00838) ---- */!][!//
[!IF "$ArtiTraceApplication = 'true'"!][!//
[!LOOP "text:split('Start,Restart,AllowAccess,Terminate', ',')"!][!//
[!VAR "ArtiEvents" = "concat($ArtiEvents, 'NOSUSP:AR_CP_OS_APPLICATION:OsApplication_', ., ':ApplicationId;')"!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!/* ---- AR_CP_OS_TASK / AR_CP_OSARTI_TASK (SWS_Os_00840, 00841) ---- */!][!//
[!VAR "ArtiTaskClass" = "''"!][!//
[!IF "$ArtiTraceTask = 'true'"!][!//
[!IF "$ArtiEnhanced = 'true'"!][!//
[!VAR "ArtiTaskClass" = "'AR_CP_OSARTI_TASK'"!][!VAR "Evs" = "'Activate,Start,Preempt,Resume,Wait,Release,Continue,Terminate'"!][!//
[!ELSE!][!//
[!VAR "ArtiTaskClass" = "'AR_CP_OS_TASK'"!][!VAR "Evs" = "'Activate,Start,Preempt,Wait,Release,Terminate'"!][!//
[!ENDIF!][!//
[!LOOP "text:split($Evs, ',')"!][!//
[!VAR "ArtiEvents" = "concat($ArtiEvents, 'NOSUSP:', $ArtiTaskClass, ':OsTask_', ., ':TaskId;')"!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!/* ---- AR_CP_OS_CAT2ISR / AR_CP_OSARTI_CAT2ISR (SWS_Os_00849, 00842) ---- */!][!//
[!VAR "ArtiIsrClass" = "''"!][!//
[!IF "$ArtiTraceCat2Isr = 'true'"!][!//
[!IF "$ArtiEnhanced = 'true'"!][!//
[!VAR "ArtiIsrClass" = "'AR_CP_OSARTI_CAT2ISR'"!][!VAR "Evs" = "'Activate,Start,Preempt,Resume,Stop'"!][!//
[!ELSE!][!//
[!VAR "ArtiIsrClass" = "'AR_CP_OS_CAT2ISR'"!][!VAR "Evs" = "'Start,Stop'"!][!//
[!ENDIF!][!//
[!LOOP "text:split($Evs, ',')"!][!//
[!VAR "ArtiEvents" = "concat($ArtiEvents, 'NOSUSP:', $ArtiIsrClass, ':OsCat2Isr_', ., ':Isr2Id;')"!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!/* ---- AR_CP_OS_SERVICECALLS (SWS_Os_00843, 00844): every SWS OS service the kernel implements
     (StartNonAutosarCore is not implemented). Called in system mode with interrupts enabled: SPRVSR.
     Start / Return type maps follow the SWS OS 7.17.4 parameter table; StatusType returns use LastError. */!][!//
[!VAR "ArtiServices" = "'ActivateTask/TaskId/LastError,TerminateTask/TaskId/LastError,ChainTask/TaskId/LastError,Schedule/-/LastError,GetTaskID/-/TaskId,GetTaskState/TaskId/TaskState,'"!][!//
[!VAR "ArtiServices" = "concat($ArtiServices, 'EnableAllInterrupts/-/-,DisableAllInterrupts/-/-,ResumeAllInterrupts/-/-,SuspendAllInterrupts/-/-,ResumeOSInterrupts/-/-,SuspendOSInterrupts/-/-,')"!][!//
[!VAR "ArtiServices" = "concat($ArtiServices, 'GetResource/ResourceId/LastError,ReleaseResource/ResourceId/LastError,SetEvent/TaskId/LastError,ClearEvent/-/LastError,GetEvent/TaskId/-,WaitEvent/-/LastError,')"!][!//
[!VAR "ArtiServices" = "concat($ArtiServices, 'GetAlarmBase/AlarmId/-,GetAlarm/AlarmId/-,SetRelAlarm/AlarmId/LastError,SetAbsAlarm/AlarmId/LastError,CancelAlarm/AlarmId/LastError,')"!][!//
[!VAR "ArtiServices" = "concat($ArtiServices, 'GetActiveApplicationMode/-/AppMode,StartOS/AppMode/x,ShutdownOS/LastError/x,GetApplicationID/-/ApplicationId,GetCurrentApplicationID/-/ApplicationId,GetISRID/-/Isr2Id,')"!][!//
[!VAR "ArtiServices" = "concat($ArtiServices, 'CallTrustedFunction/-/LastError,CheckISRMemoryAccess/Isr2Id/-,CheckTaskMemoryAccess/TaskId/-,CheckObjectAccess/ApplicationId/-,CheckObjectOwnership/-/ApplicationId,')"!][!//
[!VAR "ArtiServices" = "concat($ArtiServices, 'StartScheduleTableRel/ScheduleTableId/LastError,StartScheduleTableAbs/ScheduleTableId/LastError,StopScheduleTable/ScheduleTableId/LastError,NextScheduleTable/ScheduleTableId/LastError,')"!][!//
[!VAR "ArtiServices" = "concat($ArtiServices, 'StartScheduleTableSynchron/ScheduleTableId/LastError,SyncScheduleTable/ScheduleTableId/LastError,SetScheduleTableAsync/ScheduleTableId/LastError,GetScheduleTableStatus/ScheduleTableId/-,')"!][!//
[!VAR "ArtiServices" = "concat($ArtiServices, 'IncrementCounter/CounterId/LastError,GetCounterValue/CounterId/-,GetElapsedValue/CounterId/-,TerminateApplication/ApplicationId/LastError,AllowAccess/-/LastError,GetApplicationState/ApplicationId/-,')"!][!//
[!VAR "ArtiServices" = "concat($ArtiServices, 'GetNumberOfActivatedCores/-/-,GetCoreID/-/-,StartCore/-/LastError,GetSpinlock/SpinlockId/LastError,ReleaseSpinlock/SpinlockId/LastError,TryToGetSpinlock/SpinlockId/LastError,')"!][!//
[!VAR "ArtiServices" = "concat($ArtiServices, 'ShutdownAllCores/LastError/x,ControlIdle/-/LastError,ReadPeripheral8/-/LastError,ReadPeripheral16/-/LastError,ReadPeripheral32/-/LastError,WritePeripheral8/-/LastError,')"!][!//
[!VAR "ArtiServices" = "concat($ArtiServices, 'WritePeripheral16/-/LastError,WritePeripheral32/-/LastError,ModifyPeripheral8/-/LastError,ModifyPeripheral16/-/LastError,ModifyPeripheral32/-/LastError,')"!][!//
[!VAR "ArtiServices" = "concat($ArtiServices, 'EnableInterruptSource/Isr2Id/LastError,DisableInterruptSource/Isr2Id/LastError,ClearPendingInterrupt/Isr2Id/LastError,ActivateTaskAsyn/TaskId/-,SetEventAsyn/TaskId/-')"!][!//
[!IF "$ArtiTraceServiceCalls = 'true'"!][!//
[!LOOP "text:split($ArtiServices, ',')"!][!//
[!VAR "Api" = "text:split(., '/')[1]"!][!//
[!VAR "ArtiEvents" = "concat($ArtiEvents, 'SPRVSR:AR_CP_OS_SERVICECALLS:OsServiceCall_', $Api, '_Start:', text:split(., '/')[2], ';')"!][!//
[!IF "text:split(., '/')[3] != 'x'"!][!//
[!VAR "ArtiEvents" = "concat($ArtiEvents, 'SPRVSR:AR_CP_OS_SERVICECALLS:OsServiceCall_', $Api, '_Return:', text:split(., '/')[3], ';')"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!/* ---- AR_CP_OS_SPINLOCK (SWS_Os_00845, 00846) ---- */!][!//
[!IF "$ArtiTraceSpinlock = 'true' and count(./OsSpinlock/*) > 0"!][!//
[!VAR "ArtiEvents" = "concat($ArtiEvents, 'NOSUSP:AR_CP_OS_SPINLOCK:OsSpinlock_Locked:SpinlockId;')"!][!//
[!VAR "ArtiEvents" = "concat($ArtiEvents, 'NOSUSP:AR_CP_OS_SPINLOCK:OsSpinlock_Released:SpinlockId;')"!][!//
[!ENDIF!][!//
[!/* ---- AR_CP_OS_HOOK (SWS_Os_00856, 00857): configured hooks only. The Start parameter of
     Error/Shutdown hooks is the error code, of the ProtectionHook the fatal error; the
     ProtectionHook Return carries the reaction the OS actually takes. ---- */!][!//
[!VAR "ArtiAppHooks" = "''"!][!//
[!IF "$ArtiTraceHook = 'true'"!][!//
[!IF "node:value(./OsOS/OsHooks/OsErrorHook) = 'true'"!][!VAR "ArtiEvents" = "concat($ArtiEvents, 'NOSUSP:AR_CP_OS_HOOK:OsHook_ErrorHook_Start:LastError;NOSUSP:AR_CP_OS_HOOK:OsHook_ErrorHook_Return:-;')"!][!ENDIF!][!//
[!IF "node:value(./OsOS/OsHooks/OsPreTaskHook) = 'true'"!][!VAR "ArtiEvents" = "concat($ArtiEvents, 'NOSUSP:AR_CP_OS_HOOK:OsHook_PreTaskHook_Start:-;NOSUSP:AR_CP_OS_HOOK:OsHook_PreTaskHook_Return:-;')"!][!ENDIF!][!//
[!IF "node:value(./OsOS/OsHooks/OsPostTaskHook) = 'true'"!][!VAR "ArtiEvents" = "concat($ArtiEvents, 'NOSUSP:AR_CP_OS_HOOK:OsHook_PostTaskHook_Start:-;NOSUSP:AR_CP_OS_HOOK:OsHook_PostTaskHook_Return:-;')"!][!ENDIF!][!//
[!IF "node:value(./OsOS/OsHooks/OsProtectionHook) = 'true'"!][!VAR "ArtiEvents" = "concat($ArtiEvents, 'NOSUSP:AR_CP_OS_HOOK:OsHook_ProtectionHook_Start:LastError;NOSUSP:AR_CP_OS_HOOK:OsHook_ProtectionHook_Return:ProtectionReaction;')"!][!ENDIF!][!//
[!IF "node:value(./OsOS/OsHooks/OsStartupHook) = 'true'"!][!VAR "ArtiEvents" = "concat($ArtiEvents, 'NOSUSP:AR_CP_OS_HOOK:OsHook_StartupHook_Start:-;NOSUSP:AR_CP_OS_HOOK:OsHook_StartupHook_Return:-;')"!][!ENDIF!][!//
[!IF "node:value(./OsOS/OsHooks/OsShutdownHook) = 'true'"!][!VAR "ArtiEvents" = "concat($ArtiEvents, 'NOSUSP:AR_CP_OS_HOOK:OsHook_ShutdownHook_Start:LastError;NOSUSP:AR_CP_OS_HOOK:OsHook_ShutdownHook_Return:-;')"!][!ENDIF!][!//
[!LOOP "node:order(./OsApplication/*,'@index')"!][!//
[!VAR "App" = "node:name(.)"!][!//
[!IF "node:value(./OsApplicationHooks/OsAppErrorHook) = 'true'"!][!//
[!VAR "ArtiAppHooks" = "concat($ArtiAppHooks, 'ErrorHook/', $App, '/', num:i(@index), ',')"!][!//
[!VAR "ArtiEvents" = "concat($ArtiEvents, 'NOSUSP:AR_CP_OS_HOOK:OsHook_ErrorHook_', $App, '_Start:LastError;NOSUSP:AR_CP_OS_HOOK:OsHook_ErrorHook_', $App, '_Return:-;')"!][!//
[!ENDIF!][!//
[!IF "node:value(./OsApplicationHooks/OsAppStartupHook) = 'true'"!][!//
[!VAR "ArtiAppHooks" = "concat($ArtiAppHooks, 'StartupHook/', $App, '/', num:i(@index), ',')"!][!//
[!VAR "ArtiEvents" = "concat($ArtiEvents, 'NOSUSP:AR_CP_OS_HOOK:OsHook_StartupHook_', $App, '_Start:-;NOSUSP:AR_CP_OS_HOOK:OsHook_StartupHook_', $App, '_Return:-;')"!][!//
[!ENDIF!][!//
[!IF "node:value(./OsApplicationHooks/OsAppShutdownHook) = 'true'"!][!//
[!VAR "ArtiAppHooks" = "concat($ArtiAppHooks, 'ShutdownHook/', $App, '/', num:i(@index), ',')"!][!//
[!VAR "ArtiEvents" = "concat($ArtiEvents, 'NOSUSP:AR_CP_OS_HOOK:OsHook_ShutdownHook_', $App, '_Start:LastError;NOSUSP:AR_CP_OS_HOOK:OsHook_ShutdownHook_', $App, '_Return:-;')"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDMACRO!][!//
