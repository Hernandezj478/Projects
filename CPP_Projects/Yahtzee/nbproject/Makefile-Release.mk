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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/lib/inlcude/SHA1.o \
	${OBJECTDIR}/lib/inlcude/SHA256.o \
	${OBJECTDIR}/lib/inlcude/Scanner.o \
	${OBJECTDIR}/lib/src/AdminPlayer.o \
	${OBJECTDIR}/lib/src/Dice.o \
	${OBJECTDIR}/lib/src/Game.o \
	${OBJECTDIR}/lib/src/Menu.o \
	${OBJECTDIR}/lib/src/Player.o \
	${OBJECTDIR}/lib/src/ScoreCard.o \
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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yahtzee.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yahtzee.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yahtzee ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/lib/inlcude/SHA1.o: lib/inlcude/SHA1.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/inlcude
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Ilib/inlcude -include lib/inlcude/SHA.hpp -include lib/inlcude/SHA1.hpp -include lib/inlcude/SHA256.hpp -include lib/inlcude/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/inlcude/SHA1.o lib/inlcude/SHA1.cpp

${OBJECTDIR}/lib/inlcude/SHA256.o: lib/inlcude/SHA256.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/inlcude
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Ilib/inlcude -include lib/inlcude/SHA.hpp -include lib/inlcude/SHA1.hpp -include lib/inlcude/SHA256.hpp -include lib/inlcude/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/inlcude/SHA256.o lib/inlcude/SHA256.cpp

${OBJECTDIR}/lib/inlcude/Scanner.o: lib/inlcude/Scanner.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/inlcude
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Ilib/inlcude -include lib/inlcude/SHA.hpp -include lib/inlcude/SHA1.hpp -include lib/inlcude/SHA256.hpp -include lib/inlcude/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/inlcude/Scanner.o lib/inlcude/Scanner.cpp

${OBJECTDIR}/lib/src/AdminPlayer.o: lib/src/AdminPlayer.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Ilib/inlcude -include lib/inlcude/SHA.hpp -include lib/inlcude/SHA1.hpp -include lib/inlcude/SHA256.hpp -include lib/inlcude/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/AdminPlayer.o lib/src/AdminPlayer.cpp

${OBJECTDIR}/lib/src/AdminPlayer.hpp.gch: lib/src/AdminPlayer.hpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Ilib/inlcude -include lib/inlcude/SHA.hpp -include lib/inlcude/SHA1.hpp -include lib/inlcude/SHA256.hpp -include lib/inlcude/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o "$@" lib/src/AdminPlayer.hpp

${OBJECTDIR}/lib/src/Dice.o: lib/src/Dice.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Ilib/inlcude -include lib/inlcude/SHA.hpp -include lib/inlcude/SHA1.hpp -include lib/inlcude/SHA256.hpp -include lib/inlcude/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/Dice.o lib/src/Dice.cpp

${OBJECTDIR}/lib/src/Enums.hpp.gch: lib/src/Enums.hpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Ilib/inlcude -include lib/inlcude/SHA.hpp -include lib/inlcude/SHA1.hpp -include lib/inlcude/SHA256.hpp -include lib/inlcude/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o "$@" lib/src/Enums.hpp

${OBJECTDIR}/lib/src/Game.o: lib/src/Game.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Ilib/inlcude -include lib/inlcude/SHA.hpp -include lib/inlcude/SHA1.hpp -include lib/inlcude/SHA256.hpp -include lib/inlcude/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/Game.o lib/src/Game.cpp

${OBJECTDIR}/lib/src/Game.hpp.gch: lib/src/Game.hpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Ilib/inlcude -include lib/inlcude/SHA.hpp -include lib/inlcude/SHA1.hpp -include lib/inlcude/SHA256.hpp -include lib/inlcude/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o "$@" lib/src/Game.hpp

${OBJECTDIR}/lib/src/Menu.o: lib/src/Menu.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Ilib/inlcude -include lib/inlcude/SHA.hpp -include lib/inlcude/SHA1.hpp -include lib/inlcude/SHA256.hpp -include lib/inlcude/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/Menu.o lib/src/Menu.cpp

${OBJECTDIR}/lib/src/Menu.hpp.gch: lib/src/Menu.hpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Ilib/inlcude -include lib/inlcude/SHA.hpp -include lib/inlcude/SHA1.hpp -include lib/inlcude/SHA256.hpp -include lib/inlcude/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o "$@" lib/src/Menu.hpp

${OBJECTDIR}/lib/src/Player.o: lib/src/Player.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Ilib/inlcude -include lib/inlcude/SHA.hpp -include lib/inlcude/SHA1.hpp -include lib/inlcude/SHA256.hpp -include lib/inlcude/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/Player.o lib/src/Player.cpp

${OBJECTDIR}/lib/src/Player.hpp.gch: lib/src/Player.hpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Ilib/inlcude -include lib/inlcude/SHA.hpp -include lib/inlcude/SHA1.hpp -include lib/inlcude/SHA256.hpp -include lib/inlcude/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o "$@" lib/src/Player.hpp

${OBJECTDIR}/lib/src/ScoreCard.o: lib/src/ScoreCard.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Ilib/inlcude -include lib/inlcude/SHA.hpp -include lib/inlcude/SHA1.hpp -include lib/inlcude/SHA256.hpp -include lib/inlcude/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/src/ScoreCard.o lib/src/ScoreCard.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Ilib/inlcude -include lib/inlcude/SHA.hpp -include lib/inlcude/SHA1.hpp -include lib/inlcude/SHA256.hpp -include lib/inlcude/Scanner.hpp -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
