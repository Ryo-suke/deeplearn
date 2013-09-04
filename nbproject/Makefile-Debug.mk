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
	${OBJECTDIR}/model/Node.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/model/InputNode.o \
	${OBJECTDIR}/model/Model.o \
	${OBJECTDIR}/model/spnet/Spn.o \
	${OBJECTDIR}/model/Edge.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/deeplearn

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/deeplearn: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/deeplearn ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/model/Node.o: model/Node.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} $@.d
	$(COMPILE.cc) -g -Imath -Imodel -Idependencies/boost_1_54_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/model/Node.o model/Node.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Imath -Imodel -Idependencies/boost_1_54_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/model/InputNode.o: model/InputNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} $@.d
	$(COMPILE.cc) -g -Imath -Imodel -Idependencies/boost_1_54_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/model/InputNode.o model/InputNode.cpp

${OBJECTDIR}/model/Model.o: model/Model.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} $@.d
	$(COMPILE.cc) -g -Imath -Imodel -Idependencies/boost_1_54_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/model/Model.o model/Model.cpp

${OBJECTDIR}/model/spnet/Spn.o: model/spnet/Spn.cpp 
	${MKDIR} -p ${OBJECTDIR}/model/spnet
	${RM} $@.d
	$(COMPILE.cc) -g -Imath -Imodel -Idependencies/boost_1_54_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/model/spnet/Spn.o model/spnet/Spn.cpp

${OBJECTDIR}/model/Edge.o: model/Edge.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} $@.d
	$(COMPILE.cc) -g -Imath -Imodel -Idependencies/boost_1_54_0 -MMD -MP -MF $@.d -o ${OBJECTDIR}/model/Edge.o model/Edge.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/deeplearn

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
