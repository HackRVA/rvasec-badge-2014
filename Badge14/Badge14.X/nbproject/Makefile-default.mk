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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Badge14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Badge14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/Common/uart2.c ../src/USB/usb_device.c ../src/USB/usb_function_cdc.c ../src/Nokia_5110_Example.c ../src/Sound.c ../src/badge14.c ../src/badge_common.c ../src/main.c ../src/time_date.c ../src/usb_descriptors.c ../src/touch.S

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1310178235/uart2.o ${OBJECTDIR}/_ext/659838314/usb_device.o ${OBJECTDIR}/_ext/659838314/usb_function_cdc.o ${OBJECTDIR}/_ext/1360937237/Nokia_5110_Example.o ${OBJECTDIR}/_ext/1360937237/Sound.o ${OBJECTDIR}/_ext/1360937237/badge14.o ${OBJECTDIR}/_ext/1360937237/badge_common.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/time_date.o ${OBJECTDIR}/_ext/1360937237/usb_descriptors.o ${OBJECTDIR}/_ext/1360937237/touch.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1310178235/uart2.o.d ${OBJECTDIR}/_ext/659838314/usb_device.o.d ${OBJECTDIR}/_ext/659838314/usb_function_cdc.o.d ${OBJECTDIR}/_ext/1360937237/Nokia_5110_Example.o.d ${OBJECTDIR}/_ext/1360937237/Sound.o.d ${OBJECTDIR}/_ext/1360937237/badge14.o.d ${OBJECTDIR}/_ext/1360937237/badge_common.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/time_date.o.d ${OBJECTDIR}/_ext/1360937237/usb_descriptors.o.d ${OBJECTDIR}/_ext/1360937237/touch.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1310178235/uart2.o ${OBJECTDIR}/_ext/659838314/usb_device.o ${OBJECTDIR}/_ext/659838314/usb_function_cdc.o ${OBJECTDIR}/_ext/1360937237/Nokia_5110_Example.o ${OBJECTDIR}/_ext/1360937237/Sound.o ${OBJECTDIR}/_ext/1360937237/badge14.o ${OBJECTDIR}/_ext/1360937237/badge_common.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/time_date.o ${OBJECTDIR}/_ext/1360937237/usb_descriptors.o ${OBJECTDIR}/_ext/1360937237/touch.o

# Source Files
SOURCEFILES=../src/Common/uart2.c ../src/USB/usb_device.c ../src/USB/usb_function_cdc.c ../src/Nokia_5110_Example.c ../src/Sound.c ../src/badge14.c ../src/badge_common.c ../src/main.c ../src/time_date.c ../src/usb_descriptors.c ../src/touch.S


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Badge14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX250F128D
MP_LINKER_FILE_OPTION=,--script="../src/app_32MX250F128D.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360937237/touch.o: ../src/touch.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/touch.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/touch.o.ok ${OBJECTDIR}/_ext/1360937237/touch.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/touch.o.d" "${OBJECTDIR}/_ext/1360937237/touch.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/touch.o.d"  -o ${OBJECTDIR}/_ext/1360937237/touch.o ../src/touch.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/touch.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
	
else
${OBJECTDIR}/_ext/1360937237/touch.o: ../src/touch.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/touch.o 
	@${RM} ${OBJECTDIR}/_ext/1360937237/touch.o.ok ${OBJECTDIR}/_ext/1360937237/touch.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/touch.o.d" "${OBJECTDIR}/_ext/1360937237/touch.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1360937237/touch.o.d"  -o ${OBJECTDIR}/_ext/1360937237/touch.o ../src/touch.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1360937237/touch.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1310178235/uart2.o: ../src/Common/uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1310178235 
	@${RM} ${OBJECTDIR}/_ext/1310178235/uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1310178235/uart2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1310178235/uart2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1310178235/uart2.o.d" -o ${OBJECTDIR}/_ext/1310178235/uart2.o ../src/Common/uart2.c   
	
${OBJECTDIR}/_ext/659838314/usb_device.o: ../src/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/659838314 
	@${RM} ${OBJECTDIR}/_ext/659838314/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/659838314/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659838314/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/659838314/usb_device.o.d" -o ${OBJECTDIR}/_ext/659838314/usb_device.o ../src/USB/usb_device.c   
	
${OBJECTDIR}/_ext/659838314/usb_function_cdc.o: ../src/USB/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/659838314 
	@${RM} ${OBJECTDIR}/_ext/659838314/usb_function_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/659838314/usb_function_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659838314/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/659838314/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/659838314/usb_function_cdc.o ../src/USB/usb_function_cdc.c   
	
${OBJECTDIR}/_ext/1360937237/Nokia_5110_Example.o: ../src/Nokia_5110_Example.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Nokia_5110_Example.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Nokia_5110_Example.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Nokia_5110_Example.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Nokia_5110_Example.o.d" -o ${OBJECTDIR}/_ext/1360937237/Nokia_5110_Example.o ../src/Nokia_5110_Example.c   
	
${OBJECTDIR}/_ext/1360937237/Sound.o: ../src/Sound.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Sound.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Sound.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Sound.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Sound.o.d" -o ${OBJECTDIR}/_ext/1360937237/Sound.o ../src/Sound.c   
	
${OBJECTDIR}/_ext/1360937237/badge14.o: ../src/badge14.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/badge14.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/badge14.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/badge14.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/badge14.o.d" -o ${OBJECTDIR}/_ext/1360937237/badge14.o ../src/badge14.c   
	
${OBJECTDIR}/_ext/1360937237/badge_common.o: ../src/badge_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/badge_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/badge_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/badge_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/badge_common.o.d" -o ${OBJECTDIR}/_ext/1360937237/badge_common.o ../src/badge_common.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/1360937237/time_date.o: ../src/time_date.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/time_date.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/time_date.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/time_date.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/time_date.o.d" -o ${OBJECTDIR}/_ext/1360937237/time_date.o ../src/time_date.c   
	
${OBJECTDIR}/_ext/1360937237/usb_descriptors.o: ../src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1360937237/usb_descriptors.o ../src/usb_descriptors.c   
	
else
${OBJECTDIR}/_ext/1310178235/uart2.o: ../src/Common/uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1310178235 
	@${RM} ${OBJECTDIR}/_ext/1310178235/uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1310178235/uart2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1310178235/uart2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1310178235/uart2.o.d" -o ${OBJECTDIR}/_ext/1310178235/uart2.o ../src/Common/uart2.c   
	
${OBJECTDIR}/_ext/659838314/usb_device.o: ../src/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/659838314 
	@${RM} ${OBJECTDIR}/_ext/659838314/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/659838314/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659838314/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/659838314/usb_device.o.d" -o ${OBJECTDIR}/_ext/659838314/usb_device.o ../src/USB/usb_device.c   
	
${OBJECTDIR}/_ext/659838314/usb_function_cdc.o: ../src/USB/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/659838314 
	@${RM} ${OBJECTDIR}/_ext/659838314/usb_function_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/659838314/usb_function_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/659838314/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/659838314/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/659838314/usb_function_cdc.o ../src/USB/usb_function_cdc.c   
	
${OBJECTDIR}/_ext/1360937237/Nokia_5110_Example.o: ../src/Nokia_5110_Example.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Nokia_5110_Example.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Nokia_5110_Example.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Nokia_5110_Example.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Nokia_5110_Example.o.d" -o ${OBJECTDIR}/_ext/1360937237/Nokia_5110_Example.o ../src/Nokia_5110_Example.c   
	
${OBJECTDIR}/_ext/1360937237/Sound.o: ../src/Sound.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Sound.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Sound.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Sound.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Sound.o.d" -o ${OBJECTDIR}/_ext/1360937237/Sound.o ../src/Sound.c   
	
${OBJECTDIR}/_ext/1360937237/badge14.o: ../src/badge14.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/badge14.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/badge14.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/badge14.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/badge14.o.d" -o ${OBJECTDIR}/_ext/1360937237/badge14.o ../src/badge14.c   
	
${OBJECTDIR}/_ext/1360937237/badge_common.o: ../src/badge_common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/badge_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/badge_common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/badge_common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/badge_common.o.d" -o ${OBJECTDIR}/_ext/1360937237/badge_common.o ../src/badge_common.c   
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/1360937237/time_date.o: ../src/time_date.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/time_date.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/time_date.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/time_date.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/time_date.o.d" -o ${OBJECTDIR}/_ext/1360937237/time_date.o ../src/time_date.c   
	
${OBJECTDIR}/_ext/1360937237/usb_descriptors.o: ../src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -fschedule-insns -DPIC32MX460F512L_PIM -DGLCD_DEVICE_PIC24H -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../src" -MMD -MF "${OBJECTDIR}/_ext/1360937237/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1360937237/usb_descriptors.o ../src/usb_descriptors.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Badge14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/app_32MX250F128D.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/Badge14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=512,--defsym=_min_stack_size=512,-Map="mappit",--cref
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Badge14.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/app_32MX250F128D.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/Badge14.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--defsym=_min_stack_size=512,-Map="mappit",--cref
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Badge14.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
