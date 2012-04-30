#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1309969090/FakeDevice.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/_ext/1309969090/DeviceSelector.o \
	${OBJECTDIR}/_ext/1309969090/DeviceTreeNode.o \
	${OBJECTDIR}/_ext/1309969090/ECGReceiver.o \
	${OBJECTDIR}/_ext/1309969090/WaitingDialog.o \
	${OBJECTDIR}/_ext/1309969090/NeedWaitingDialog.o \
	${OBJECTDIR}/_ext/1309969090/ECGSignal.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++0x
CXXFLAGS=-std=c++0x

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs gtkmm-3.0` -lpthread  bluez-cpp/dist/Debug/GNU-Linux-x86/libbluez-cpp.so  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ecgreceiver

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ecgreceiver: bluez-cpp/dist/Debug/GNU-Linux-x86/libbluez-cpp.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ecgreceiver: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ecgreceiver ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1309969090/FakeDevice.o: /home/tomko/moje_dziela/Telemedycyna/ECGReceiver/src/FakeDevice.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1309969090
	${RM} $@.d
	$(COMPILE.cc) -g -Ibluez-cpp `pkg-config --cflags gtkmm-3.0`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1309969090/FakeDevice.o /home/tomko/moje_dziela/Telemedycyna/ECGReceiver/src/FakeDevice.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Ibluez-cpp `pkg-config --cflags gtkmm-3.0`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/_ext/1309969090/DeviceSelector.o: /home/tomko/moje_dziela/Telemedycyna/ECGReceiver/src/DeviceSelector.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1309969090
	${RM} $@.d
	$(COMPILE.cc) -g -Ibluez-cpp `pkg-config --cflags gtkmm-3.0`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1309969090/DeviceSelector.o /home/tomko/moje_dziela/Telemedycyna/ECGReceiver/src/DeviceSelector.cpp

${OBJECTDIR}/_ext/1309969090/DeviceTreeNode.o: /home/tomko/moje_dziela/Telemedycyna/ECGReceiver/src/DeviceTreeNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1309969090
	${RM} $@.d
	$(COMPILE.cc) -g -Ibluez-cpp `pkg-config --cflags gtkmm-3.0`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1309969090/DeviceTreeNode.o /home/tomko/moje_dziela/Telemedycyna/ECGReceiver/src/DeviceTreeNode.cpp

${OBJECTDIR}/_ext/1309969090/ECGReceiver.o: /home/tomko/moje_dziela/Telemedycyna/ECGReceiver/src/ECGReceiver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1309969090
	${RM} $@.d
	$(COMPILE.cc) -g -Ibluez-cpp `pkg-config --cflags gtkmm-3.0`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1309969090/ECGReceiver.o /home/tomko/moje_dziela/Telemedycyna/ECGReceiver/src/ECGReceiver.cpp

${OBJECTDIR}/_ext/1309969090/WaitingDialog.o: /home/tomko/moje_dziela/Telemedycyna/ECGReceiver/src/WaitingDialog.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1309969090
	${RM} $@.d
	$(COMPILE.cc) -g -Ibluez-cpp `pkg-config --cflags gtkmm-3.0`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1309969090/WaitingDialog.o /home/tomko/moje_dziela/Telemedycyna/ECGReceiver/src/WaitingDialog.cpp

${OBJECTDIR}/_ext/1309969090/NeedWaitingDialog.o: /home/tomko/moje_dziela/Telemedycyna/ECGReceiver/src/NeedWaitingDialog.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1309969090
	${RM} $@.d
	$(COMPILE.cc) -g -Ibluez-cpp `pkg-config --cflags gtkmm-3.0`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1309969090/NeedWaitingDialog.o /home/tomko/moje_dziela/Telemedycyna/ECGReceiver/src/NeedWaitingDialog.cpp

${OBJECTDIR}/_ext/1309969090/ECGSignal.o: /home/tomko/moje_dziela/Telemedycyna/ECGReceiver/src/ECGSignal.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1309969090
	${RM} $@.d
	$(COMPILE.cc) -g -Ibluez-cpp `pkg-config --cflags gtkmm-3.0`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1309969090/ECGSignal.o /home/tomko/moje_dziela/Telemedycyna/ECGReceiver/src/ECGSignal.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ecgreceiver

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
