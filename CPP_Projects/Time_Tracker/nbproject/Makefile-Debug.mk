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
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/lib/include/SHA1.o \
	${OBJECTDIR}/lib/include/SHA256.o \
	${OBJECTDIR}/lib/include/Scanner.o \
	${OBJECTDIR}/lib/src/AdminUser.o \
	${OBJECTDIR}/lib/src/Application.o \
	${OBJECTDIR}/lib/src/Course.o \
	${OBJECTDIR}/lib/src/Menu.o \
	${OBJECTDIR}/lib/src/StandardUser.o \
	${OBJECTDIR}/lib/src/TimeTracker.o \
	${OBJECTDIR}/lib/src/User.o \
	${OBJECTDIR}/main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/time_tracker_v0.12.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/time_tracker_v0.12.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/time_tracker_v0.12 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/lib/include/SHA1.o: lib/include/SHA1.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/include
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/include -include lib/include/Enums.hpp -include lib/include/SHA.hpp -include lib/include/SHA1.hpp -include lib/include/SHA256.hpp -include lib/include/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/include/SHA1.o lib/include/SHA1.cpp

${OBJECTDIR}/lib/include/SHA256.o: lib/include/SHA256.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/include
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/include -include lib/include/Enums.hpp -include lib/include/SHA.hpp -include lib/include/SHA1.hpp -include lib/include/SHA256.hpp -include lib/include/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/include/SHA256.o lib/include/SHA256.cpp

${OBJECTDIR}/lib/include/Scanner.o: lib/include/Scanner.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/include
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/include -include lib/include/Enums.hpp -include lib/include/SHA.hpp -include lib/include/SHA1.hpp -include lib/include/SHA256.hpp -include lib/include/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/include/Scanner.o lib/include/Scanner.cpp

${OBJECTDIR}/lib/src/AdminUser.o: lib/src/AdminUser.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/include -include lib/include/Enums.hpp -include lib/include/SHA.hpp -include lib/include/SHA1.hpp -include lib/include/SHA256.hpp -include lib/include/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/AdminUser.o lib/src/AdminUser.cpp

${OBJECTDIR}/lib/src/Application.o: lib/src/Application.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/include -include lib/include/Enums.hpp -include lib/include/SHA.hpp -include lib/include/SHA1.hpp -include lib/include/SHA256.hpp -include lib/include/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/Application.o lib/src/Application.cpp

${OBJECTDIR}/lib/src/Course.o: lib/src/Course.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/include -include lib/include/Enums.hpp -include lib/include/SHA.hpp -include lib/include/SHA1.hpp -include lib/include/SHA256.hpp -include lib/include/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/Course.o lib/src/Course.cpp

${OBJECTDIR}/lib/src/Menu.o: lib/src/Menu.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/include -include lib/include/Enums.hpp -include lib/include/SHA.hpp -include lib/include/SHA1.hpp -include lib/include/SHA256.hpp -include lib/include/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/Menu.o lib/src/Menu.cpp

${OBJECTDIR}/lib/src/StandardUser.o: lib/src/StandardUser.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/include -include lib/include/Enums.hpp -include lib/include/SHA.hpp -include lib/include/SHA1.hpp -include lib/include/SHA256.hpp -include lib/include/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/StandardUser.o lib/src/StandardUser.cpp

${OBJECTDIR}/lib/src/TimeTracker.o: lib/src/TimeTracker.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/include -include lib/include/Enums.hpp -include lib/include/SHA.hpp -include lib/include/SHA1.hpp -include lib/include/SHA256.hpp -include lib/include/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/TimeTracker.o lib/src/TimeTracker.cpp

${OBJECTDIR}/lib/src/User.o: lib/src/User.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/include -include lib/include/Enums.hpp -include lib/include/SHA.hpp -include lib/include/SHA1.hpp -include lib/include/SHA256.hpp -include lib/include/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/User.o lib/src/User.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ilib/include -include lib/include/Enums.hpp -include lib/include/SHA.hpp -include lib/include/SHA1.hpp -include lib/include/SHA256.hpp -include lib/include/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
