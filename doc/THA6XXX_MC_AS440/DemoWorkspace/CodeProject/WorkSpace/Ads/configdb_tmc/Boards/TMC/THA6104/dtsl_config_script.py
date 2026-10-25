from com.arm.debug.dtsl.configurations import ConfigurationBaseSDF
from com.arm.debug.dtsl.configurations import DTSLv1
from com.arm.debug.dtsl.components import FormatterMode
from com.arm.debug.dtsl.components import APBAP
from com.arm.debug.dtsl.components import AHBAP
from com.arm.debug.dtsl.components import Device
from com.arm.debug.dtsl.components import DeviceInfo
from com.arm.debug.dtsl.configurations.options import IIntegerOption
from com.arm.debug.dtsl.components import CSTMC
from com.arm.debug.dtsl.components import TMCETBTraceCapture
from com.arm.debug.dtsl.components import DSTREAMTraceCapture
from com.arm.debug.dtsl.components import DSTREAMSTStoredTraceCapture
from com.arm.debug.dtsl.components import DSTREAMPTStoreAndForwardTraceCapture
from com.arm.debug.dtsl.components import DSTREAMPTLiveStoredStreamingTraceCapture
from com.arm.debug.dtsl.components import CSCTI
from com.arm.debug.dtsl.components import ETMv4TraceSource
from com.arm.debug.dtsl.components import CSTPIU
from com.arm.debug.dtsl.configurations import TimestampInfo

clusterNames = ["Cortex-R52+_SMP_0"]
clusterCores = [["Cortex-R52+_0", "Cortex-R52+_1"]]
coreNames_cortexR52PLUS = ["Cortex-R52+_0", "Cortex-R52+_1"]
coreNames_sC300 = ["SC300"]

TRACE_RANGE_DESCRIPTION = '''Limit trace capture to the specified range. This is useful for restricting trace capture to an OS (e.g. Linux kernel)'''


class DtslScript(ConfigurationBaseSDF):
    @staticmethod
    def getOptionList():
        return [
            DTSLv1.tabSet("options", "Options", childOptions=
                [DTSLv1.tabPage("trace", "Trace Capture", childOptions=[
                    DTSLv1.integerOption('timestampFrequency', 'Timestamp frequency', defaultValue=25000000, isDynamic=False, description="This value will be used to set the Counter Base Frequency ID Register of the Timestamp generator.\nIt represents the number of ticks per second and is used to translate the timestamp value reported into a number of seconds.\nNote that changing this value may not result in a change in the observed frequency."),
                    DTSLv1.enumOption('traceCapture', 'Trace capture method', defaultValue="none",
                        values = [("none", "None"), ("CSTMC_0", "On Chip Trace Buffer (CSTMC_0/ETF)"), DtslScript.getOffChipTraceOption()]),
                ])]
                +[DTSLv1.tabPage("Cortex-R52+_SMP_0", "Cortex-R52+", childOptions=[
                    DTSLv1.booleanOption('coreTrace', 'Enable Cortex-R52+ core trace', defaultValue=False,
                        childOptions = [
                            DTSLv1.booleanOption('Cortex-R52+_SMP_0_0', 'Enable Cortex-R52+_0 trace', defaultValue=True),
                            DTSLv1.booleanOption('Cortex-R52+_SMP_0_1', 'Enable Cortex-R52+_1 trace', defaultValue=True),
                            DTSLv1.booleanOption('timestamp', "Enable ETM Timestamps", description="Controls the output of timestamps into the ETM output streams", defaultValue=True),
                            DTSLv1.booleanOption('contextIDs', "Enable ETM Context IDs", description="Controls the output of context ID values into the ETM output streams", defaultValue=True),
                            ETMv4TraceSource.cycleAccurateOption(DtslScript.getSourcesForCluster("Cortex-R52+_SMP_0")),
                            ETMv4TraceSource.dataOption(DtslScript.getSourcesForCluster("Cortex-R52+_SMP_0")),
                            # Trace range selection (e.g. for linux kernel)
                            DTSLv1.booleanOption('traceRange', 'Trace capture range', description=TRACE_RANGE_DESCRIPTION, defaultValue = False,
                                childOptions = [
                                    DTSLv1.integerOption('start', 'Start address',
                                        description='Start address for trace capture',
                                        defaultValue=0,
                                        display=IIntegerOption.DisplayFormat.HEX),
                                    DTSLv1.integerOption('end', 'End address',
                                        description='End address for trace capture',
                                        defaultValue=0xFFFFFFFF,
                                        display=IIntegerOption.DisplayFormat.HEX)
                                ])
                        ]
                    ),
                ])]
                +[DTSLv1.tabPage("sync", "CTI Synchronization", childOptions=[
                    DTSLv1.infoElement("Select the cores to be cross-triggered (not needed for SMP connections)"),
                    DTSLv1.booleanOption(coreNames_cortexR52PLUS[0], coreNames_cortexR52PLUS[0], description="Add core to synchronization group", defaultValue=False, isDynamic=True),
                    DTSLv1.booleanOption(coreNames_cortexR52PLUS[1], coreNames_cortexR52PLUS[1], description="Add core to synchronization group", defaultValue=False, isDynamic=True),
                    DTSLv1.booleanOption(coreNames_sC300[0], coreNames_sC300[0], description="Add core to synchronization group", defaultValue=False, isDynamic=True),
                ])]
            )
        ]
    
    @staticmethod
    def getOffChipTraceOption():
        return ("DSTREAM", "DSTREAM 4GB Trace Buffer",
            DTSLv1.infoElement("dstream", "Off-Chip Trace", "",
                childOptions=[
                    DTSLv1.enumOption('tpiuPortWidth', 'TPIU Port Width', defaultValue="16",
                        values = [("1", "1 bit"), ("2", "2 bit"), ("3", "3 bit"), ("4", "4 bit"), ("5", "5 bit"), ("6", "6 bit"), ("7", "7 bit"), ("8", "8 bit"), ("9", "9 bit"), ("10", "10 bit"), ("11", "11 bit"), ("12", "12 bit"), ("13", "13 bit"), ("14", "14 bit"), ("15", "15 bit"), ("16", "16 bit")], isDynamic=False),
                ]
            )
        )
    
    def __init__(self, root):
        ConfigurationBaseSDF.__init__(self, root)
        
        self.discoverDevices()
    
    # +----------------------------+
    # | Target dependent functions |
    # +----------------------------+
    
    def discoverDevices(self):
        '''Find and create devices'''
        
        # MEMAP devices
        APBAP(self, self.findDevice("CSMEMAP_0"), "CSMEMAP_0")
        APBAP(self, self.findDevice("CSMEMAP_1"), "CSMEMAP_1")
        AHBAP(self, self.findDevice("CSMEMAP_2"), "CSMEMAP_2")
        AHBAP(self, self.findDevice("CSMEMAP_3"), "CSMEMAP_3")
        
        # Trace start/stop CTIs
        CSCTI(self, self.findDevice("CSCTI_0"), "CSCTI_0")
        
        # The ATB stream ID which will be assigned to trace sources.
        streamID = 1
        
        self.sC300cores = []
        for coreName in (coreNames_sC300):
            # Create core
            coreDevice = Device(self, self.findDevice(coreName), coreName)
            deviceInfo = DeviceInfo("core", "Cortex-M3")
            coreDevice.setDeviceInfo(deviceInfo)
            self.sC300cores.append(coreDevice)
            self.addDeviceInterface(coreDevice)
            
            # Create CTI (if a CTI exists for this core)
            ctiName = self.getCTINameForCore(coreName)
            if not ctiName is None:
                CSCTI(self, self.findDevice(ctiName), ctiName)
                self.registerCoreForCrossSync(coreDevice)
            
        self.cortexR52PLUScores = []
        # Ensure that ETMv4 stream IDs are even
        streamID += (streamID % 2)
        for coreName in (coreNames_cortexR52PLUS):
            # Create core
            coreDevice = Device(self, self.findDevice(coreName), coreName)
            deviceInfo = DeviceInfo("core", "Cortex-R52+")
            coreDevice.setDeviceInfo(deviceInfo)
            self.cortexR52PLUScores.append(coreDevice)
            self.addDeviceInterface(coreDevice)
            
            # Create CTI (if a CTI exists for this core)
            ctiName = self.getCTINameForCore(coreName)
            if not ctiName is None:
                CSCTI(self, self.findDevice(ctiName), ctiName)
                self.registerCoreForCrossSync(coreDevice)
            
            # Create Trace Macrocell (if a macrocell exists for this core - disabled by default - will enable with option)
            tmName = self.getTraceSourceNameForCore(coreName)
            if not tmName == None:
                tm = ETMv4TraceSource(self, self.findDevice(tmName), streamID, tmName)
                streamID += 2
                tm.setEnabled(False)
            
        tmc = CSTMC(self, self.findDevice("CSTMC_0"), "CSTMC_0")
        tmc.setMode(CSTMC.Mode.ETF)
        
        tpiu = CSTPIU(self, self.findDevice("CSTPIU"), "CSTPIU")
        tpiu.setEnabled(False)
        tpiu.setFormatterMode(FormatterMode.CONTINUOUS)
        
        # Create and Configure Funnels
        self.createFunnel("CSTFunnel_2")
        
        self.setupCTISyncSMP()
        
    def createTMCETBTraceCapture(self, deviceName):
        tmcEtbTrace = TMCETBTraceCapture(self, self.getDeviceInterface(deviceName), deviceName)
        self.addTraceCaptureInterface(tmcEtbTrace)
    
    def createDSTREAMTraceCapture(self, dstreamMode):
        self.DSTREAM = DSTREAMTraceCapture(self, dstreamMode)
        self.addTraceCaptureInterface(self.DSTREAM)
    
    def getDstreamOptionString(self, dstreamMode):
        return "dstream"
    
    def postConnect(self):
        ConfigurationBaseSDF.postConnect(self)
        
        if self.getOptions().getOption("options.trace.timestampFrequency"):
            freq = self.getOptionValue("options.trace.timestampFrequency")
            # Update the value so the trace decoder can access it
            tsInfo = TimestampInfo(freq)
            self.setTimestampInfo(tsInfo)
        
    
    # +--------------------------------+
    # | Callback functions for options |
    # +--------------------------------+
    
    def optionValuesChanged(self):
        '''Callback to update the configuration state after options are changed'''
        if not self.isConnected():
            self.setInitialOptions()
        
        self.updateDynamicOptions()
        
    def setInitialOptions(self):
        '''Set the initial options'''
        
        coreTraceEnabled = self.getOptionValue("options.Cortex-R52+_SMP_0.coreTrace")
        for core in range(len(clusterCores[0])):
            tmName = self.getTraceSourceNameForCore(clusterCores[0][core])
            if tmName:
                coreTM = self.getDeviceInterface(tmName)
                thisCoreTraceEnabled = self.getOptionValue("options.Cortex-R52+_SMP_0.coreTrace.Cortex-R52+_SMP_0_%d" % core)
                enableSource = coreTraceEnabled and thisCoreTraceEnabled
                self.setTraceSourceEnabled(tmName, enableSource)
                if(self.getOptionValue("options.Cortex-R52+_SMP_0.coreTrace.traceRange")):
                    coreTM.clearAllTraceRanges()
                    coreTM.addTraceRange(self.getOptionValue("options.Cortex-R52+_SMP_0.coreTrace.traceRange.start"),
                                         self.getOptionValue("options.Cortex-R52+_SMP_0.coreTrace.traceRange.end"))
                coreTM.setTimestampingEnabled(self.getOptionValue("options.Cortex-R52+_SMP_0.coreTrace.timestamp"))
                self.setContextIDEnabled(coreTM,
                                     self.getOptionValue("options.Cortex-R52+_SMP_0.coreTrace.contextIDs"),
                                     "32")
        
        traceMode = self.getOptionValue("options.trace.traceCapture")
        if traceMode != "none":
            # TMC ETB/ETF Devices
            if traceMode == "CSTMC_0":
                self.createTMCETBTraceCapture("CSTMC_0")
            # DSTREAM
            if traceMode in ["DSTREAM", "DSTREAM_PT_Store_and_Forward", "DSTREAM_PT_StreamingTrace"]:
                self.createDSTREAMTraceCapture(traceMode)
                if self.getOptions().getOption("options.trace.traceCapture." + self.getDstreamOptionString(traceMode) + ".tpiuPortWidth"):
                    self.setPortWidth(int(self.getOptionValue("options.trace.traceCapture." + self.getDstreamOptionString(traceMode) + ".tpiuPortWidth")))
                
                if self.getOptions().getOption("options.trace.traceCapture." + self.getDstreamOptionString(traceMode) + ".traceBufferSize"):
                    self.setTraceBufferSize(self.getOptionValue("options.trace.traceCapture." + self.getDstreamOptionString(traceMode) + ".traceBufferSize"))
                
            self.enableTraceCapture(traceMode)
            self.configureTraceCapture(traceMode)
            
    def updateDynamicOptions(self):
        '''Update the dynamic options'''
        
        for cluster in range(len(clusterNames)):
            if not self.getDeviceInterface(clusterNames[cluster]).isConnected():
                for core in range(len(clusterCores[cluster])):
                    if self.getCTINameForCore(clusterCores[cluster][core]):
                        enable = self.getOptionValue('options.sync.%s' % clusterCores[cluster][core])
                        self.setCrossSyncEnabled(self.getDeviceInterface(clusterCores[cluster][core]), enable)
        
        for core in range(len(self.sC300cores)):
            enable = self.getOptionValue('options.sync.%s' % coreNames_sC300[core])
            self.setCrossSyncEnabled(self.sC300cores[core], enable)
        
    @staticmethod
    def getSourcesForCoreType(coreType):
        '''Get the Trace Sources for a given coreType
           Use parameter-binding to ensure that the correct Sources
           are returned for the core type passed only'''
        def getSources(self):
            return self.getTraceSourcesForCoreType(coreType)
        return getSources
    
    @staticmethod
    def getSourcesForCluster(cluster):
        '''Get the Trace Sources for a given coreType
           Use parameter-binding to ensure that the correct Sources
           are returned for the core type and cluster passed only'''
        def getClusterSources(self):
            return self.getTraceSourcesForCluster(cluster)
        return getClusterSources
    
class DtslScript_DSTREAM_ST(DtslScript):
    @staticmethod
    def getOptionList():
        return [
            DTSLv1.tabSet("options", "Options", childOptions=
                [DTSLv1.tabPage("trace", "Trace Capture", childOptions=[
                    DTSLv1.integerOption('timestampFrequency', 'Timestamp frequency', defaultValue=25000000, isDynamic=False, description="This value will be used to set the Counter Base Frequency ID Register of the Timestamp generator.\nIt represents the number of ticks per second and is used to translate the timestamp value reported into a number of seconds.\nNote that changing this value may not result in a change in the observed frequency."),
                    DTSLv1.enumOption('traceCapture', 'Trace capture method', defaultValue="none",
                        values = [("none", "None"), ("CSTMC_0", "On Chip Trace Buffer (CSTMC_0/ETF)"), DtslScript_DSTREAM_ST.getOffChipTraceOption()]),
                ])]
                +[DTSLv1.tabPage("Cortex-R52+_SMP_0", "Cortex-R52+", childOptions=[
                    DTSLv1.booleanOption('coreTrace', 'Enable Cortex-R52+ core trace', defaultValue=False,
                        childOptions = [
                            DTSLv1.booleanOption('Cortex-R52+_SMP_0_0', 'Enable Cortex-R52+_0 trace', defaultValue=True),
                            DTSLv1.booleanOption('Cortex-R52+_SMP_0_1', 'Enable Cortex-R52+_1 trace', defaultValue=True),
                            DTSLv1.booleanOption('timestamp', "Enable ETM Timestamps", description="Controls the output of timestamps into the ETM output streams", defaultValue=True),
                            DTSLv1.booleanOption('contextIDs', "Enable ETM Context IDs", description="Controls the output of context ID values into the ETM output streams", defaultValue=True),
                            ETMv4TraceSource.cycleAccurateOption(DtslScript.getSourcesForCluster("Cortex-R52+_SMP_0")),
                            ETMv4TraceSource.dataOption(DtslScript.getSourcesForCluster("Cortex-R52+_SMP_0")),
                            # Trace range selection (e.g. for linux kernel)
                            DTSLv1.booleanOption('traceRange', 'Trace capture range', description=TRACE_RANGE_DESCRIPTION, defaultValue = False,
                                childOptions = [
                                    DTSLv1.integerOption('start', 'Start address',
                                        description='Start address for trace capture',
                                        defaultValue=0,
                                        display=IIntegerOption.DisplayFormat.HEX),
                                    DTSLv1.integerOption('end', 'End address',
                                        description='End address for trace capture',
                                        defaultValue=0xFFFFFFFF,
                                        display=IIntegerOption.DisplayFormat.HEX)
                                ])
                        ]
                    ),
                ])]
                +[DTSLv1.tabPage("sync", "CTI Synchronization", childOptions=[
                    DTSLv1.infoElement("Select the cores to be cross-triggered (not needed for SMP connections)"),
                    DTSLv1.booleanOption(coreNames_cortexR52PLUS[0], coreNames_cortexR52PLUS[0], description="Add core to synchronization group", defaultValue=False, isDynamic=True),
                    DTSLv1.booleanOption(coreNames_cortexR52PLUS[1], coreNames_cortexR52PLUS[1], description="Add core to synchronization group", defaultValue=False, isDynamic=True),
                    DTSLv1.booleanOption(coreNames_sC300[0], coreNames_sC300[0], description="Add core to synchronization group", defaultValue=False, isDynamic=True),
                ])]
            )
        ]
    
    @staticmethod
    def getOffChipTraceOption():
        return ("DSTREAM", "DSTREAM-ST Streaming Trace",
            DTSLv1.infoElement("dstream", "Off-Chip Trace", "",
                childOptions=[
                    DTSLv1.enumOption('tpiuPortWidth', 'TPIU Port Width', defaultValue="4",
                        values = [("1", "1 bit"), ("2", "2 bit"), ("4", "4 bit")], isDynamic=False),
                    DTSLv1.enumOption('traceBufferSize', 'Host Trace Buffer Size', defaultValue="4GB",
                        values = [("64MB", "64MB"), ("128MB", "128MB"), ("256MB", "256MB"), ("512MB", "512MB"), ("1GB", "1GB"), ("2GB", "2GB"), ("4GB", "4GB"), ("8GB", "8GB"), ("16GB", "16GB"), ("32GB", "32GB"), ("64GB", "64GB"), ("128GB", "128GB")], isDynamic=False)
                ]
            )
        )
    
    def createDSTREAMTraceCapture(self, dstreamMode):
        self.DSTREAM = DSTREAMSTStoredTraceCapture(self, dstreamMode)
        self.addTraceCaptureInterface(self.DSTREAM)
        self.addStreamTraceCaptureInterface(self.DSTREAM)
    

class DtslScript_DSTREAM_PT(DtslScript):
    @staticmethod
    def getOptionList():
        return [
            DTSLv1.tabSet("options", "Options", childOptions=
                [DTSLv1.tabPage("trace", "Trace Capture", childOptions=[
                    DTSLv1.integerOption('timestampFrequency', 'Timestamp frequency', defaultValue=25000000, isDynamic=False, description="This value will be used to set the Counter Base Frequency ID Register of the Timestamp generator.\nIt represents the number of ticks per second and is used to translate the timestamp value reported into a number of seconds.\nNote that changing this value may not result in a change in the observed frequency."),
                    DTSLv1.enumOption('traceCapture', 'Trace capture method', defaultValue="none",
                        values = [("none", "None"), ("CSTMC_0", "On Chip Trace Buffer (CSTMC_0/ETF)"), DtslScript_DSTREAM_PT.getStoreAndForwardOptions(), DtslScript_DSTREAM_PT.getStreamingTraceOptions()]),
                ])]
                +[DTSLv1.tabPage("Cortex-R52+_SMP_0", "Cortex-R52+", childOptions=[
                    DTSLv1.booleanOption('coreTrace', 'Enable Cortex-R52+ core trace', defaultValue=False,
                        childOptions = [
                            DTSLv1.booleanOption('Cortex-R52+_SMP_0_0', 'Enable Cortex-R52+_0 trace', defaultValue=True),
                            DTSLv1.booleanOption('Cortex-R52+_SMP_0_1', 'Enable Cortex-R52+_1 trace', defaultValue=True),
                            DTSLv1.booleanOption('timestamp', "Enable ETM Timestamps", description="Controls the output of timestamps into the ETM output streams", defaultValue=True),
                            DTSLv1.booleanOption('contextIDs', "Enable ETM Context IDs", description="Controls the output of context ID values into the ETM output streams", defaultValue=True),
                            ETMv4TraceSource.cycleAccurateOption(DtslScript.getSourcesForCluster("Cortex-R52+_SMP_0")),
                            ETMv4TraceSource.dataOption(DtslScript.getSourcesForCluster("Cortex-R52+_SMP_0")),
                            # Trace range selection (e.g. for linux kernel)
                            DTSLv1.booleanOption('traceRange', 'Trace capture range', description=TRACE_RANGE_DESCRIPTION, defaultValue = False,
                                childOptions = [
                                    DTSLv1.integerOption('start', 'Start address',
                                        description='Start address for trace capture',
                                        defaultValue=0,
                                        display=IIntegerOption.DisplayFormat.HEX),
                                    DTSLv1.integerOption('end', 'End address',
                                        description='End address for trace capture',
                                        defaultValue=0xFFFFFFFF,
                                        display=IIntegerOption.DisplayFormat.HEX)
                                ])
                        ]
                    ),
                ])]
                +[DTSLv1.tabPage("sync", "CTI Synchronization", childOptions=[
                    DTSLv1.infoElement("Select the cores to be cross-triggered (not needed for SMP connections)"),
                    DTSLv1.booleanOption(coreNames_cortexR52PLUS[0], coreNames_cortexR52PLUS[0], description="Add core to synchronization group", defaultValue=False, isDynamic=True),
                    DTSLv1.booleanOption(coreNames_cortexR52PLUS[1], coreNames_cortexR52PLUS[1], description="Add core to synchronization group", defaultValue=False, isDynamic=True),
                    DTSLv1.booleanOption(coreNames_sC300[0], coreNames_sC300[0], description="Add core to synchronization group", defaultValue=False, isDynamic=True),
                ])]
            )
        ]
    
    @staticmethod
    def getStoreAndForwardOptions():
        return ("DSTREAM_PT_Store_and_Forward", "DSTREAM-PT 8GB Trace Buffer",
            DTSLv1.infoElement("dpt_storeandforward", "Off-Chip Trace", "",
                childOptions=[
                    DTSLv1.enumOption('tpiuPortWidth', 'TPIU Port Width', defaultValue="16",
                        values = [("1", "1 bit"), ("2", "2 bit"), ("3", "3 bit"), ("4", "4 bit"), ("5", "5 bit"), ("6", "6 bit"), ("7", "7 bit"), ("8", "8 bit"), ("9", "9 bit"), ("10", "10 bit"), ("11", "11 bit"), ("12", "12 bit"), ("13", "13 bit"), ("14", "14 bit"), ("15", "15 bit"), ("16", "16 bit"), ("18", "18 bit"), ("20", "20 bit"), ("22", "22 bit"), ("24", "24 bit"), ("26", "26 bit"), ("28", "28 bit"), ("30", "30 bit"), ("32", "32 bit")], isDynamic=False),
                ]
            )
        )
    
    @staticmethod
    def getStreamingTraceOptions():
        return ("DSTREAM_PT_StreamingTrace", "DSTREAM-PT Streaming Trace",
            DTSLv1.infoElement("dpt_streamingtrace", "Off-Chip Trace", "",
                childOptions=[
                    DTSLv1.enumOption('tpiuPortWidth', 'TPIU Port Width', defaultValue="16",
                        values = [("1", "1 bit"), ("2", "2 bit"), ("3", "3 bit"), ("4", "4 bit"), ("5", "5 bit"), ("6", "6 bit"), ("7", "7 bit"), ("8", "8 bit"), ("9", "9 bit"), ("10", "10 bit"), ("11", "11 bit"), ("12", "12 bit"), ("13", "13 bit"), ("14", "14 bit"), ("15", "15 bit"), ("16", "16 bit"), ("18", "18 bit"), ("20", "20 bit"), ("22", "22 bit"), ("24", "24 bit"), ("26", "26 bit"), ("28", "28 bit"), ("30", "30 bit"), ("32", "32 bit")], isDynamic=False),
                    DTSLv1.enumOption('traceBufferSize', 'Host Trace Buffer Size', defaultValue="4GB",
                        values = [("64MB", "64MB"), ("128MB", "128MB"), ("256MB", "256MB"), ("512MB", "512MB"), ("1GB", "1GB"), ("2GB", "2GB"), ("4GB", "4GB"), ("8GB", "8GB"), ("16GB", "16GB"), ("32GB", "32GB"), ("64GB", "64GB"), ("128GB", "128GB")], isDynamic=False)
                ]
            )
        )
    
    def createDSTREAMTraceCapture(self, dstreamMode):
        if dstreamMode == "DSTREAM_PT_Store_and_Forward":
            self.DSTREAM = DSTREAMPTStoreAndForwardTraceCapture(self, "DSTREAM_PT_Store_and_Forward")
        elif dstreamMode == "DSTREAM_PT_StreamingTrace":
            self.DSTREAM = DSTREAMPTLiveStoredStreamingTraceCapture(self, "DSTREAM_PT_StreamingTrace")
        self.addTraceCaptureInterface(self.DSTREAM)
        self.addStreamTraceCaptureInterface(self.DSTREAM)
    
    def getDstreamOptionString(self, dstreamMode):
        if dstreamMode == "DSTREAM_PT_Store_and_Forward":
            return "dpt_storeandforward"
        if dstreamMode == "DSTREAM_PT_StreamingTrace":
            return "dpt_streamingtrace"
    

class DtslScript_DebugAndOnChipTrace(DtslScript):
    @staticmethod
    def getOptionList():
        return [
            DTSLv1.tabSet("options", "Options", childOptions=
                [DTSLv1.tabPage("trace", "Trace Capture", childOptions=[
                    DTSLv1.integerOption('timestampFrequency', 'Timestamp frequency', defaultValue=25000000, isDynamic=False, description="This value will be used to set the Counter Base Frequency ID Register of the Timestamp generator.\nIt represents the number of ticks per second and is used to translate the timestamp value reported into a number of seconds.\nNote that changing this value may not result in a change in the observed frequency."),
                    DTSLv1.enumOption('traceCapture', 'Trace capture method', defaultValue="none",
                        values = [("none", "None"), ("CSTMC_0", "On Chip Trace Buffer (CSTMC_0/ETF)")]),
                ])]
                +[DTSLv1.tabPage("Cortex-R52+_SMP_0", "Cortex-R52+", childOptions=[
                    DTSLv1.booleanOption('coreTrace', 'Enable Cortex-R52+ core trace', defaultValue=False,
                        childOptions = [
                            DTSLv1.booleanOption('Cortex-R52+_SMP_0_0', 'Enable Cortex-R52+_0 trace', defaultValue=True),
                            DTSLv1.booleanOption('Cortex-R52+_SMP_0_1', 'Enable Cortex-R52+_1 trace', defaultValue=True),
                            DTSLv1.booleanOption('timestamp', "Enable ETM Timestamps", description="Controls the output of timestamps into the ETM output streams", defaultValue=True),
                            DTSLv1.booleanOption('contextIDs', "Enable ETM Context IDs", description="Controls the output of context ID values into the ETM output streams", defaultValue=True),
                            ETMv4TraceSource.cycleAccurateOption(DtslScript.getSourcesForCluster("Cortex-R52+_SMP_0")),
                            ETMv4TraceSource.dataOption(DtslScript.getSourcesForCluster("Cortex-R52+_SMP_0")),
                            # Trace range selection (e.g. for linux kernel)
                            DTSLv1.booleanOption('traceRange', 'Trace capture range', description=TRACE_RANGE_DESCRIPTION, defaultValue = False,
                                childOptions = [
                                    DTSLv1.integerOption('start', 'Start address',
                                        description='Start address for trace capture',
                                        defaultValue=0,
                                        display=IIntegerOption.DisplayFormat.HEX),
                                    DTSLv1.integerOption('end', 'End address',
                                        description='End address for trace capture',
                                        defaultValue=0xFFFFFFFF,
                                        display=IIntegerOption.DisplayFormat.HEX)
                                ])
                        ]
                    ),
                ])]
                +[DTSLv1.tabPage("sync", "CTI Synchronization", childOptions=[
                    DTSLv1.infoElement("Select the cores to be cross-triggered (not needed for SMP connections)"),
                    DTSLv1.booleanOption(coreNames_cortexR52PLUS[0], coreNames_cortexR52PLUS[0], description="Add core to synchronization group", defaultValue=False, isDynamic=True),
                    DTSLv1.booleanOption(coreNames_cortexR52PLUS[1], coreNames_cortexR52PLUS[1], description="Add core to synchronization group", defaultValue=False, isDynamic=True),
                    DTSLv1.booleanOption(coreNames_sC300[0], coreNames_sC300[0], description="Add core to synchronization group", defaultValue=False, isDynamic=True),
                ])]
            )
        ]

