#/**********************************************************************************************************************
#  @Copyright: (C) 1989-2023 Lauterbach GmbH, licensed for use with TRACE32(R) only
#**********************************************************************************************************************/

#/**********************************************************************************************************************
#  Description:  Patch SAFERTOS source files with ARTI hooks
#*********************************************************************************************************************/


# import used modules

import os, shutil, re

# sub-functions

def saveAndOpenFile (fileName):
    origFileName = fileName + ".original"
    if not os.path.exists(origFileName):
        shutil.copyfile(fileName, origFileName)
    fileOrig = open(origFileName, 'r')
    fileNew  = open(fileName, 'w')
    return fileOrig, fileNew

def closeFile (fileOrig, fileNew):
    fileNew.close()
    fileOrig.close()

# Patch task.c

fileOrig, fileNew = saveAndOpenFile ("kernel/task.c")

for fileLine in fileOrig:
    fileNew.write (fileLine)
    if "SAFERTOSTRACE " in fileLine:
        indent = fileLine[0:re.search("\S", fileLine).start()]
        if any([marker in fileLine for marker in ["TASKSWITCHEDIN ", "TASKSWITCHEDINELSE "]]):
            fileNew.write (indent + "if (t32_current != pxCurrentTCB->uxTCBNumber) {\n")
            fileNew.write (indent + "    portUnsignedBaseType newEvent;\n")
            fileNew.write (indent + "    if ((pxOldTCB->uxArtiEvent == OsTask_Start) ||\n")
            fileNew.write (indent + "           (pxOldTCB->uxArtiEvent == OsTask_Continue) ||\n")
            fileNew.write (indent + "           (pxOldTCB->uxArtiEvent == OsTask_Resume)) {\n")
            fileNew.write (indent + "       pxOldTCB->uxArtiEvent = OsTask_Preempt; \n")
            fileNew.write (indent + "       ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Preempt, pxOldTCB->uxTCBNumber)\n")
            fileNew.write (indent + "    }\n")
            fileNew.write (indent + "    switch (pxCurrentTCB->uxArtiEvent) {\n")
            fileNew.write (indent + "       case OsTask_Activate:\n")
            fileNew.write (indent + "           newEvent = OsTask_Start; break;\n")
            fileNew.write (indent + "       case OsTask_Release:\n")
            fileNew.write (indent + "           newEvent = OsTask_Continue; break;\n")
            fileNew.write (indent + "       case OsTask_Preempt:\n")
            fileNew.write (indent + "           newEvent = OsTask_Resume; break;\n")
            fileNew.write (indent + "       default:\n")
            fileNew.write (indent + "           newEvent = OsTask_Start; break; /* actually an error */\n")
            fileNew.write (indent + "    }\n")
            fileNew.write (indent + "    t32_current = pxCurrentTCB->uxTCBNumber;\n")
            fileNew.write (indent + "    pxCurrentTCB->uxArtiEvent = newEvent; \n")
            fileNew.write (indent + "    ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, newEvent, pxCurrentTCB->uxTCBNumber)\n")
            fileNew.write (indent + "}\n")
        elif "TASKCREATE " in fileLine:
            fileNew.write (indent + "uxTaskNumber++;\n")
            fileNew.write (indent + "pxNewTCB->uxTCBNumber = uxTaskNumber;\n")
            fileNew.write (indent + "pxNewTCB->uxArtiEvent = OsTask_Activate; \n")
            fileNew.write (indent + "ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Activate, pxNewTCB->uxTCBNumber)\n")
        elif "TASKDELETE " in fileLine:
            fileNew.write (indent + "pxTCB->uxArtiEvent = OsTask_Terminate; \n")
            fileNew.write (indent + "ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Terminate, pxTCB->uxTCBNumber)\n")
        elif any([marker in fileLine for marker in [
                "TASKDELAY ", "TASKDELAYUNTIL ", "TASKNOTIFYWAITBLOCK "]]):
            fileNew.write (indent + "pxCurrentTCB->uxArtiEvent = OsTask_Wait; \n")
            fileNew.write (indent + "ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Wait, pxCurrentTCB->uxTCBNumber)\n")
        elif "TASKSUSPEND " in fileLine:
            fileNew.write (indent + "pxTCB->uxArtiEvent = OsTask_Wait; \n")
            fileNew.write (indent + "ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Wait, pxTCB->uxTCBNumber)\n")
#        elif "TASKRESUME " in fileLine:  # not needed as it will run to TASKMOVEDTOREADYSTATE
#            fileNew.write (indent + "ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Release, pxTCB->uxTCBNumber)\n")
        elif "TASKMOVEDTOREADYSTATE " in fileLine:
            fileNew.write (indent + "if ((pxCurrentTCB != pxTCB) && (pxTCB->uxArtiEvent == OsTask_Wait)) {\n")
            fileNew.write (indent + "    pxTCB->uxArtiEvent = OsTask_Release; \n")
            fileNew.write (indent + "    ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Release, pxTCB->uxTCBNumber)\n")
            fileNew.write (indent + "}\n")
    elif "Update global volatile variables" in fileLine:
        indent = fileLine[0:re.search("\S", fileLine).start()]
        fileNew.write (indent + "pxOldTCB = pxCurrentTCB;\n")
    elif "File private variables" in fileLine:
        fileNew.write ("\nKERNEL_DATA portUnsignedBaseType uxTaskNumber = 0U;\n")
        fileNew.write (  "KERNEL_DATA xTCB                *pxOldTCB     = NULL;\n")
    elif '#include "task.h"' in fileLine:
        fileNew.write ('#include "..\\arti\\arti.h"\n')

closeFile (fileOrig, fileNew)

# Patch queue.c

fileOrig, fileNew = saveAndOpenFile ("kernel/queue.c")

for fileLine in fileOrig:
    fileNew.write (fileLine)
    if "SAFERTOSTRACE " in fileLine:
        indent = fileLine[0:re.search("\S", fileLine).start()]
        if any([marker in fileLine for marker in ["QUEUESENDBLOCKED ", "QUEUERECEIVEBLOCKED "]]):
            fileNew.write (indent + "pxCurrentTCB->uxArtiEvent = OsTask_Wait; \n")
            fileNew.write (indent + "ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Wait, t32_current)\n")
    elif '#include "task.h"' in fileLine:
        fileNew.write ('#include "..\\arti\\arti.h"\n')

closeFile (fileOrig, fileNew)

# Patch eventgroups.c

fileOrig, fileNew = saveAndOpenFile ("kernel/eventgroups.c")

for fileLine in fileOrig:
    fileNew.write (fileLine)
    if "SAFERTOSTRACE " in fileLine:
        indent = fileLine[0:re.search("\S", fileLine).start()]
        if "EVENTGROUPWAITBITS_BLOCK " in fileLine:
            fileNew.write (indent + "pxCurrentTCB->uxArtiEvent = OsTask_Wait; \n")
            fileNew.write (indent + "ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Wait, t32_current)\n")
    elif '#include "task.h"' in fileLine:
        fileNew.write ('#include "..\\arti\\arti.h"\n')

closeFile (fileOrig, fileNew)

# Patch types.h

fileOrig, fileNew = saveAndOpenFile ("api/055_ARM_CM7/apiComplexTypes.h")

for fileLine in fileOrig:
    fileNew.write (fileLine)
    if "SAFERTOSTRACE " in fileLine:
        indent = fileLine[0:re.search("\S", fileLine).start()]
        if "TCBTASKNUMBER " in fileLine:
            fileNew.write (indent + "portUnsignedBaseType uxTCBNumber; /* Unique task id. */\n")
            fileNew.write (indent + "portUnsignedBaseType uxArtiEvent; /* Saved ARTI state. */\n")

closeFile (fileOrig, fileNew)

# That's all folks!
