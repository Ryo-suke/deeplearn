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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1121429291/Dataset.o \
	${OBJECTDIR}/_ext/382279727/ProductNode.o \
	${OBJECTDIR}/model/Node.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/_ext/1121161165/pimatrix.o \
	${OBJECTDIR}/_ext/1121429291/Cache.o \
	${OBJECTDIR}/model/InputNode.o \
	${OBJECTDIR}/_ext/1120904915/Util.o \
	${OBJECTDIR}/_ext/382279727/SumNode.o \
	${OBJECTDIR}/_ext/395856034/deeplearn.pb.o \
	${OBJECTDIR}/model/Model.o \
	${OBJECTDIR}/model/spnet/Spn.o \
	${OBJECTDIR}/model/Edge.o \
	${OBJECTDIR}/_ext/1121429291/DeepLearnDataHandler.o \
	${OBJECTDIR}/_ext/1121429291/DataHandler.o \
	${OBJECTDIR}/_ext/1121429291/Disk.o \
	${OBJECTDIR}/_ext/382279727/MaxNode.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2

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
LDLIBSOPTIONS=-L/home/hoaivu_pham/lib/boost_1_54_0/lib -Wl,-rpath /home/hoaivu_pham/lib/boost_1_54_0/lib -lprotobuf -lboost_filesystem -lboost_random -lboost_regex -lboost_serialization -lboost_system

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/deeplearn

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/deeplearn: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/deeplearn ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1121429291/Dataset.o: /home/hoaivu_pham/NetBeansProjects/deeplearn/data/Dataset.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1121429291
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1121429291/Dataset.o /home/hoaivu_pham/NetBeansProjects/deeplearn/data/Dataset.cpp

${OBJECTDIR}/_ext/382279727/ProductNode.o: /home/hoaivu_pham/NetBeansProjects/deeplearn/model/spnet/ProductNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/382279727
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/382279727/ProductNode.o /home/hoaivu_pham/NetBeansProjects/deeplearn/model/spnet/ProductNode.cpp

${OBJECTDIR}/model/Node.o: model/Node.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/model/Node.o model/Node.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/_ext/1121161165/pimatrix.o: /home/hoaivu_pham/NetBeansProjects/deeplearn/math/pimatrix.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1121161165
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1121161165/pimatrix.o /home/hoaivu_pham/NetBeansProjects/deeplearn/math/pimatrix.cpp

${OBJECTDIR}/_ext/1121429291/Cache.o: /home/hoaivu_pham/NetBeansProjects/deeplearn/data/Cache.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1121429291
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1121429291/Cache.o /home/hoaivu_pham/NetBeansProjects/deeplearn/data/Cache.cpp

${OBJECTDIR}/model/InputNode.o: model/InputNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/model/InputNode.o model/InputNode.cpp

${OBJECTDIR}/_ext/1120904915/Util.o: /home/hoaivu_pham/NetBeansProjects/deeplearn/util/Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1120904915
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1120904915/Util.o /home/hoaivu_pham/NetBeansProjects/deeplearn/util/Util.cpp

${OBJECTDIR}/_ext/382279727/SumNode.o: /home/hoaivu_pham/NetBeansProjects/deeplearn/model/spnet/SumNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/382279727
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/382279727/SumNode.o /home/hoaivu_pham/NetBeansProjects/deeplearn/model/spnet/SumNode.cpp

${OBJECTDIR}/_ext/395856034/deeplearn.pb.o: /home/hoaivu_pham/NetBeansProjects/deeplearn/model/deeplearn.pb.cc 
	${MKDIR} -p ${OBJECTDIR}/_ext/395856034
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/395856034/deeplearn.pb.o /home/hoaivu_pham/NetBeansProjects/deeplearn/model/deeplearn.pb.cc

${OBJECTDIR}/model/Model.o: model/Model.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/model/Model.o model/Model.cpp

${OBJECTDIR}/model/spnet/Spn.o: model/spnet/Spn.cpp 
	${MKDIR} -p ${OBJECTDIR}/model/spnet
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/model/spnet/Spn.o model/spnet/Spn.cpp

${OBJECTDIR}/model/Edge.o: model/Edge.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/model/Edge.o model/Edge.cpp

${OBJECTDIR}/_ext/1121429291/DeepLearnDataHandler.o: /home/hoaivu_pham/NetBeansProjects/deeplearn/data/DeepLearnDataHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1121429291
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1121429291/DeepLearnDataHandler.o /home/hoaivu_pham/NetBeansProjects/deeplearn/data/DeepLearnDataHandler.cpp

${OBJECTDIR}/_ext/1121429291/DataHandler.o: /home/hoaivu_pham/NetBeansProjects/deeplearn/data/DataHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1121429291
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1121429291/DataHandler.o /home/hoaivu_pham/NetBeansProjects/deeplearn/data/DataHandler.cpp

${OBJECTDIR}/_ext/1121429291/Disk.o: /home/hoaivu_pham/NetBeansProjects/deeplearn/data/Disk.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1121429291
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1121429291/Disk.o /home/hoaivu_pham/NetBeansProjects/deeplearn/data/Disk.cpp

${OBJECTDIR}/_ext/382279727/MaxNode.o: /home/hoaivu_pham/NetBeansProjects/deeplearn/model/spnet/MaxNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/382279727
	${RM} $@.d
	$(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/382279727/MaxNode.o /home/hoaivu_pham/NetBeansProjects/deeplearn/model/spnet/MaxNode.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/_ext/389674410/test_spn.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/_ext/389674410/test_util.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/_ext/389674410/test_spn.o: /home/hoaivu_pham/NetBeansProjects/deeplearn/tests/test_spn.cpp 
	${MKDIR} -p ${TESTDIR}/_ext/389674410
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -I. -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${TESTDIR}/_ext/389674410/test_spn.o /home/hoaivu_pham/NetBeansProjects/deeplearn/tests/test_spn.cpp


${TESTDIR}/_ext/389674410/test_util.o: /home/hoaivu_pham/NetBeansProjects/deeplearn/tests/test_util.cpp 
	${MKDIR} -p ${TESTDIR}/_ext/389674410
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -I. -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -MMD -MP -MF $@.d -o ${TESTDIR}/_ext/389674410/test_util.o /home/hoaivu_pham/NetBeansProjects/deeplearn/tests/test_util.cpp


${OBJECTDIR}/_ext/1121429291/Dataset_nomain.o: ${OBJECTDIR}/_ext/1121429291/Dataset.o /home/hoaivu_pham/NetBeansProjects/deeplearn/data/Dataset.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1121429291
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1121429291/Dataset.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1121429291/Dataset_nomain.o /home/hoaivu_pham/NetBeansProjects/deeplearn/data/Dataset.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1121429291/Dataset.o ${OBJECTDIR}/_ext/1121429291/Dataset_nomain.o;\
	fi

${OBJECTDIR}/_ext/382279727/ProductNode_nomain.o: ${OBJECTDIR}/_ext/382279727/ProductNode.o /home/hoaivu_pham/NetBeansProjects/deeplearn/model/spnet/ProductNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/382279727
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/382279727/ProductNode.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/382279727/ProductNode_nomain.o /home/hoaivu_pham/NetBeansProjects/deeplearn/model/spnet/ProductNode.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/382279727/ProductNode.o ${OBJECTDIR}/_ext/382279727/ProductNode_nomain.o;\
	fi

${OBJECTDIR}/model/Node_nomain.o: ${OBJECTDIR}/model/Node.o model/Node.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	@NMOUTPUT=`${NM} ${OBJECTDIR}/model/Node.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/model/Node_nomain.o model/Node.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/model/Node.o ${OBJECTDIR}/model/Node_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/_ext/1121161165/pimatrix_nomain.o: ${OBJECTDIR}/_ext/1121161165/pimatrix.o /home/hoaivu_pham/NetBeansProjects/deeplearn/math/pimatrix.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1121161165
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1121161165/pimatrix.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1121161165/pimatrix_nomain.o /home/hoaivu_pham/NetBeansProjects/deeplearn/math/pimatrix.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1121161165/pimatrix.o ${OBJECTDIR}/_ext/1121161165/pimatrix_nomain.o;\
	fi

${OBJECTDIR}/_ext/1121429291/Cache_nomain.o: ${OBJECTDIR}/_ext/1121429291/Cache.o /home/hoaivu_pham/NetBeansProjects/deeplearn/data/Cache.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1121429291
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1121429291/Cache.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1121429291/Cache_nomain.o /home/hoaivu_pham/NetBeansProjects/deeplearn/data/Cache.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1121429291/Cache.o ${OBJECTDIR}/_ext/1121429291/Cache_nomain.o;\
	fi

${OBJECTDIR}/model/InputNode_nomain.o: ${OBJECTDIR}/model/InputNode.o model/InputNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	@NMOUTPUT=`${NM} ${OBJECTDIR}/model/InputNode.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/model/InputNode_nomain.o model/InputNode.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/model/InputNode.o ${OBJECTDIR}/model/InputNode_nomain.o;\
	fi

${OBJECTDIR}/_ext/1120904915/Util_nomain.o: ${OBJECTDIR}/_ext/1120904915/Util.o /home/hoaivu_pham/NetBeansProjects/deeplearn/util/Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1120904915
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1120904915/Util.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1120904915/Util_nomain.o /home/hoaivu_pham/NetBeansProjects/deeplearn/util/Util.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1120904915/Util.o ${OBJECTDIR}/_ext/1120904915/Util_nomain.o;\
	fi

${OBJECTDIR}/_ext/382279727/SumNode_nomain.o: ${OBJECTDIR}/_ext/382279727/SumNode.o /home/hoaivu_pham/NetBeansProjects/deeplearn/model/spnet/SumNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/382279727
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/382279727/SumNode.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/382279727/SumNode_nomain.o /home/hoaivu_pham/NetBeansProjects/deeplearn/model/spnet/SumNode.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/382279727/SumNode.o ${OBJECTDIR}/_ext/382279727/SumNode_nomain.o;\
	fi

${OBJECTDIR}/_ext/395856034/deeplearn.pb_nomain.o: ${OBJECTDIR}/_ext/395856034/deeplearn.pb.o /home/hoaivu_pham/NetBeansProjects/deeplearn/model/deeplearn.pb.cc 
	${MKDIR} -p ${OBJECTDIR}/_ext/395856034
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/395856034/deeplearn.pb.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/395856034/deeplearn.pb_nomain.o /home/hoaivu_pham/NetBeansProjects/deeplearn/model/deeplearn.pb.cc;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/395856034/deeplearn.pb.o ${OBJECTDIR}/_ext/395856034/deeplearn.pb_nomain.o;\
	fi

${OBJECTDIR}/model/Model_nomain.o: ${OBJECTDIR}/model/Model.o model/Model.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	@NMOUTPUT=`${NM} ${OBJECTDIR}/model/Model.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/model/Model_nomain.o model/Model.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/model/Model.o ${OBJECTDIR}/model/Model_nomain.o;\
	fi

${OBJECTDIR}/model/spnet/Spn_nomain.o: ${OBJECTDIR}/model/spnet/Spn.o model/spnet/Spn.cpp 
	${MKDIR} -p ${OBJECTDIR}/model/spnet
	@NMOUTPUT=`${NM} ${OBJECTDIR}/model/spnet/Spn.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/model/spnet/Spn_nomain.o model/spnet/Spn.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/model/spnet/Spn.o ${OBJECTDIR}/model/spnet/Spn_nomain.o;\
	fi

${OBJECTDIR}/model/Edge_nomain.o: ${OBJECTDIR}/model/Edge.o model/Edge.cpp 
	${MKDIR} -p ${OBJECTDIR}/model
	@NMOUTPUT=`${NM} ${OBJECTDIR}/model/Edge.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/model/Edge_nomain.o model/Edge.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/model/Edge.o ${OBJECTDIR}/model/Edge_nomain.o;\
	fi

${OBJECTDIR}/_ext/1121429291/DeepLearnDataHandler_nomain.o: ${OBJECTDIR}/_ext/1121429291/DeepLearnDataHandler.o /home/hoaivu_pham/NetBeansProjects/deeplearn/data/DeepLearnDataHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1121429291
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1121429291/DeepLearnDataHandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1121429291/DeepLearnDataHandler_nomain.o /home/hoaivu_pham/NetBeansProjects/deeplearn/data/DeepLearnDataHandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1121429291/DeepLearnDataHandler.o ${OBJECTDIR}/_ext/1121429291/DeepLearnDataHandler_nomain.o;\
	fi

${OBJECTDIR}/_ext/1121429291/DataHandler_nomain.o: ${OBJECTDIR}/_ext/1121429291/DataHandler.o /home/hoaivu_pham/NetBeansProjects/deeplearn/data/DataHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1121429291
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1121429291/DataHandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1121429291/DataHandler_nomain.o /home/hoaivu_pham/NetBeansProjects/deeplearn/data/DataHandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1121429291/DataHandler.o ${OBJECTDIR}/_ext/1121429291/DataHandler_nomain.o;\
	fi

${OBJECTDIR}/_ext/1121429291/Disk_nomain.o: ${OBJECTDIR}/_ext/1121429291/Disk.o /home/hoaivu_pham/NetBeansProjects/deeplearn/data/Disk.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1121429291
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1121429291/Disk.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1121429291/Disk_nomain.o /home/hoaivu_pham/NetBeansProjects/deeplearn/data/Disk.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1121429291/Disk.o ${OBJECTDIR}/_ext/1121429291/Disk_nomain.o;\
	fi

${OBJECTDIR}/_ext/382279727/MaxNode_nomain.o: ${OBJECTDIR}/_ext/382279727/MaxNode.o /home/hoaivu_pham/NetBeansProjects/deeplearn/model/spnet/MaxNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/382279727
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/382279727/MaxNode.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Imath -Imodel -Idata -Iutil -I/home/hoaivu_pham/lib/boost_1_54_0/include -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/382279727/MaxNode_nomain.o /home/hoaivu_pham/NetBeansProjects/deeplearn/model/spnet/MaxNode.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/382279727/MaxNode.o ${OBJECTDIR}/_ext/382279727/MaxNode_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/deeplearn

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
