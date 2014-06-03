#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../bootloader_src/FrameWork/Framework.c ../bootloader_src/TransportLayer/Usb_HID_tasks.c ../bootloader_src/TransportLayer/usb_descriptors.c ../bootloader_src/USB/usb_device.c ../bootloader_src/USB/usb_function_hid.c ../bootloader_src/BootLoader.c ../bootloader_src/NVMem.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/502316088/Framework.o ${OBJECTDIR}/_ext/1833100226/Usb_HID_tasks.o ${OBJECTDIR}/_ext/1833100226/usb_descriptors.o ${OBJECTDIR}/_ext/1416911186/usb_device.o ${OBJECTDIR}/_ext/1416911186/usb_function_hid.o ${OBJECTDIR}/_ext/1192809561/BootLoader.o ${OBJECTDIR}/_ext/1192809561/NVMem.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/502316088/Framework.o.d ${OBJECTDIR}/_ext/1833100226/Usb_HID_tasks.o.d ${OBJECTDIR}/_ext/1833100226/usb_descriptors.o.d ${OBJECTDIR}/_ext/1416911186/usb_device.o.d ${OBJECTDIR}/_ext/1416911186/usb_function_hid.o.d ${OBJECTDIR}/_ext/1192809561/BootLoader.o.d ${OBJECTDIR}/_ext/1192809561/NVMem.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/502316088/Framework.o ${OBJECTDIR}/_ext/1833100226/Usb_HID_tasks.o ${OBJECTDIR}/_ext/1833100226/usb_descriptors.o ${OBJECTDIR}/_ext/1416911186/usb_device.o ${OBJECTDIR}/_ext/1416911186/usb_function_hid.o ${OBJECTDIR}/_ext/1192809561/BootLoader.o ${OBJECTDIR}/_ext/1192809561/NVMem.o

# Source Files
SOURCEFILES=../bootloader_src/FrameWork/Framework.c ../bootloader_src/TransportLayer/Usb_HID_tasks.c ../bootloader_src/TransportLayer/usb_descriptors.c ../bootloader_src/USB/usb_device.c ../bootloader_src/USB/usb_function_hid.c ../bootloader_src/BootLoader.c ../bootloader_src/NVMem.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX250F128D
MP_LINKER_FILE_OPTION=,--script="../bootloader_src/btl_32MX250F128D_generic.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/502316088/Framework.o: ../bootloader_src/FrameWork/Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/502316088 
	@${RM} ${OBJECTDIR}/_ext/502316088/Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/502316088/Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/502316088/Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DTRANSPORT_LAYER_USB -DDEMO_BOARD_USB_STARTER_KIT -I"/home/morgan/Storage/A/Projects/Badge-14/RVAsecBadge14.git/rvasec-badge-2014/Badge14/bootloader_src" -MMD -MF "${OBJECTDIR}/_ext/502316088/Framework.o.d" -o ${OBJECTDIR}/_ext/502316088/Framework.o ../bootloader_src/FrameWork/Framework.c   
	
${OBJECTDIR}/_ext/1833100226/Usb_HID_tasks.o: ../bootloader_src/TransportLayer/Usb_HID_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1833100226 
	@${RM} ${OBJECTDIR}/_ext/1833100226/Usb_HID_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1833100226/Usb_HID_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1833100226/Usb_HID_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DTRANSPORT_LAYER_USB -DDEMO_BOARD_USB_STARTER_KIT -I"/home/morgan/Storage/A/Projects/Badge-14/RVAsecBadge14.git/rvasec-badge-2014/Badge14/bootloader_src" -MMD -MF "${OBJECTDIR}/_ext/1833100226/Usb_HID_tasks.o.d" -o ${OBJECTDIR}/_ext/1833100226/Usb_HID_tasks.o ../bootloader_src/TransportLayer/Usb_HID_tasks.c   
	
${OBJECTDIR}/_ext/1833100226/usb_descriptors.o: ../bootloader_src/TransportLayer/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1833100226 
	@${RM} ${OBJECTDIR}/_ext/1833100226/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1833100226/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1833100226/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DTRANSPORT_LAYER_USB -DDEMO_BOARD_USB_STARTER_KIT -I"/home/morgan/Storage/A/Projects/Badge-14/RVAsecBadge14.git/rvasec-badge-2014/Badge14/bootloader_src" -MMD -MF "${OBJECTDIR}/_ext/1833100226/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1833100226/usb_descriptors.o ../bootloader_src/TransportLayer/usb_descriptors.c   
	
${OBJECTDIR}/_ext/1416911186/usb_device.o: ../bootloader_src/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1416911186 
	@${RM} ${OBJECTDIR}/_ext/1416911186/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1416911186/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1416911186/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DTRANSPORT_LAYER_USB -DDEMO_BOARD_USB_STARTER_KIT -I"/home/morgan/Storage/A/Projects/Badge-14/RVAsecBadge14.git/rvasec-badge-2014/Badge14/bootloader_src" -MMD -MF "${OBJECTDIR}/_ext/1416911186/usb_device.o.d" -o ${OBJECTDIR}/_ext/1416911186/usb_device.o ../bootloader_src/USB/usb_device.c   
	
${OBJECTDIR}/_ext/1416911186/usb_function_hid.o: ../bootloader_src/USB/usb_function_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1416911186 
	@${RM} ${OBJECTDIR}/_ext/1416911186/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1416911186/usb_function_hid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1416911186/usb_function_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DTRANSPORT_LAYER_USB -DDEMO_BOARD_USB_STARTER_KIT -I"/home/morgan/Storage/A/Projects/Badge-14/RVAsecBadge14.git/rvasec-badge-2014/Badge14/bootloader_src" -MMD -MF "${OBJECTDIR}/_ext/1416911186/usb_function_hid.o.d" -o ${OBJECTDIR}/_ext/1416911186/usb_function_hid.o ../bootloader_src/USB/usb_function_hid.c   
	
${OBJECTDIR}/_ext/1192809561/BootLoader.o: ../bootloader_src/BootLoader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1192809561 
	@${RM} ${OBJECTDIR}/_ext/1192809561/BootLoader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1192809561/BootLoader.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1192809561/BootLoader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DTRANSPORT_LAYER_USB -DDEMO_BOARD_USB_STARTER_KIT -I"/home/morgan/Storage/A/Projects/Badge-14/RVAsecBadge14.git/rvasec-badge-2014/Badge14/bootloader_src" -MMD -MF "${OBJECTDIR}/_ext/1192809561/BootLoader.o.d" -o ${OBJECTDIR}/_ext/1192809561/BootLoader.o ../bootloader_src/BootLoader.c   
	
${OBJECTDIR}/_ext/1192809561/NVMem.o: ../bootloader_src/NVMem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1192809561 
	@${RM} ${OBJECTDIR}/_ext/1192809561/NVMem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1192809561/NVMem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1192809561/NVMem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DTRANSPORT_LAYER_USB -DDEMO_BOARD_USB_STARTER_KIT -I"/home/morgan/Storage/A/Projects/Badge-14/RVAsecBadge14.git/rvasec-badge-2014/Badge14/bootloader_src" -MMD -MF "${OBJECTDIR}/_ext/1192809561/NVMem.o.d" -o ${OBJECTDIR}/_ext/1192809561/NVMem.o ../bootloader_src/NVMem.c   
	
else
${OBJECTDIR}/_ext/502316088/Framework.o: ../bootloader_src/FrameWork/Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/502316088 
	@${RM} ${OBJECTDIR}/_ext/502316088/Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/502316088/Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/502316088/Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DTRANSPORT_LAYER_USB -DDEMO_BOARD_USB_STARTER_KIT -I"/home/morgan/Storage/A/Projects/Badge-14/RVAsecBadge14.git/rvasec-badge-2014/Badge14/bootloader_src" -MMD -MF "${OBJECTDIR}/_ext/502316088/Framework.o.d" -o ${OBJECTDIR}/_ext/502316088/Framework.o ../bootloader_src/FrameWork/Framework.c   
	
${OBJECTDIR}/_ext/1833100226/Usb_HID_tasks.o: ../bootloader_src/TransportLayer/Usb_HID_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1833100226 
	@${RM} ${OBJECTDIR}/_ext/1833100226/Usb_HID_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1833100226/Usb_HID_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1833100226/Usb_HID_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DTRANSPORT_LAYER_USB -DDEMO_BOARD_USB_STARTER_KIT -I"/home/morgan/Storage/A/Projects/Badge-14/RVAsecBadge14.git/rvasec-badge-2014/Badge14/bootloader_src" -MMD -MF "${OBJECTDIR}/_ext/1833100226/Usb_HID_tasks.o.d" -o ${OBJECTDIR}/_ext/1833100226/Usb_HID_tasks.o ../bootloader_src/TransportLayer/Usb_HID_tasks.c   
	
${OBJECTDIR}/_ext/1833100226/usb_descriptors.o: ../bootloader_src/TransportLayer/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1833100226 
	@${RM} ${OBJECTDIR}/_ext/1833100226/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1833100226/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1833100226/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DTRANSPORT_LAYER_USB -DDEMO_BOARD_USB_STARTER_KIT -I"/home/morgan/Storage/A/Projects/Badge-14/RVAsecBadge14.git/rvasec-badge-2014/Badge14/bootloader_src" -MMD -MF "${OBJECTDIR}/_ext/1833100226/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1833100226/usb_descriptors.o ../bootloader_src/TransportLayer/usb_descriptors.c   
	
${OBJECTDIR}/_ext/1416911186/usb_device.o: ../bootloader_src/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1416911186 
	@${RM} ${OBJECTDIR}/_ext/1416911186/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1416911186/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1416911186/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DTRANSPORT_LAYER_USB -DDEMO_BOARD_USB_STARTER_KIT -I"/home/morgan/Storage/A/Projects/Badge-14/RVAsecBadge14.git/rvasec-badge-2014/Badge14/bootloader_src" -MMD -MF "${OBJECTDIR}/_ext/1416911186/usb_device.o.d" -o ${OBJECTDIR}/_ext/1416911186/usb_device.o ../bootloader_src/USB/usb_device.c   
	
${OBJECTDIR}/_ext/1416911186/usb_function_hid.o: ../bootloader_src/USB/usb_function_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1416911186 
	@${RM} ${OBJECTDIR}/_ext/1416911186/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1416911186/usb_function_hid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1416911186/usb_function_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DTRANSPORT_LAYER_USB -DDEMO_BOARD_USB_STARTER_KIT -I"/home/morgan/Storage/A/Projects/Badge-14/RVAsecBadge14.git/rvasec-badge-2014/Badge14/bootloader_src" -MMD -MF "${OBJECTDIR}/_ext/1416911186/usb_function_hid.o.d" -o ${OBJECTDIR}/_ext/1416911186/usb_function_hid.o ../bootloader_src/USB/usb_function_hid.c   
	
${OBJECTDIR}/_ext/1192809561/BootLoader.o: ../bootloader_src/BootLoader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1192809561 
	@${RM} ${OBJECTDIR}/_ext/1192809561/BootLoader.o.d 
	@${RM} ${OBJECTDIR}/_ext/1192809561/BootLoader.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1192809561/BootLoader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DTRANSPORT_LAYER_USB -DDEMO_BOARD_USB_STARTER_KIT -I"/home/morgan/Storage/A/Projects/Badge-14/RVAsecBadge14.git/rvasec-badge-2014/Badge14/bootloader_src" -MMD -MF "${OBJECTDIR}/_ext/1192809561/BootLoader.o.d" -o ${OBJECTDIR}/_ext/1192809561/BootLoader.o ../bootloader_src/BootLoader.c   
	
${OBJECTDIR}/_ext/1192809561/NVMem.o: ../bootloader_src/NVMem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1192809561 
	@${RM} ${OBJECTDIR}/_ext/1192809561/NVMem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1192809561/NVMem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1192809561/NVMem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DTRANSPORT_LAYER_USB -DDEMO_BOARD_USB_STARTER_KIT -I"/home/morgan/Storage/A/Projects/Badge-14/RVAsecBadge14.git/rvasec-badge-2014/Badge14/bootloader_src" -MMD -MF "${OBJECTDIR}/_ext/1192809561/NVMem.o.d" -o ${OBJECTDIR}/_ext/1192809561/NVMem.o ../bootloader_src/NVMem.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../bootloader_src/btl_32MX250F128D_generic.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -o dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../bootloader_src/btl_32MX250F128D_generic.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -o dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Bootloader.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
