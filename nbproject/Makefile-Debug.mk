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
CC=g++
CCC=gcc
CXX=gcc
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Chromosome.o \
	${OBJECTDIR}/City.o \
	${OBJECTDIR}/InsertMutation.o \
	${OBJECTDIR}/InversionMutation.o \
	${OBJECTDIR}/InvertedDisplacementMutation.o \
	${OBJECTDIR}/PartiallyMappedCrossover.o \
	${OBJECTDIR}/RandomMutation.o \
	${OBJECTDIR}/RandonImmigrantGenetic.o \
	${OBJECTDIR}/SwapMutation.o \
	${OBJECTDIR}/TournamentSelection.o \
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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/genetic

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/genetic: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/genetic ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Chromosome.o: Chromosome.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Chromosome.o Chromosome.c

${OBJECTDIR}/City.o: City.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/City.o City.c

${OBJECTDIR}/InsertMutation.o: InsertMutation.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InsertMutation.o InsertMutation.c

${OBJECTDIR}/InversionMutation.o: InversionMutation.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InversionMutation.o InversionMutation.c

${OBJECTDIR}/InvertedDisplacementMutation.o: InvertedDisplacementMutation.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InvertedDisplacementMutation.o InvertedDisplacementMutation.c

${OBJECTDIR}/PartiallyMappedCrossover.o: PartiallyMappedCrossover.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PartiallyMappedCrossover.o PartiallyMappedCrossover.c

${OBJECTDIR}/RandomMutation.o: RandomMutation.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RandomMutation.o RandomMutation.c

${OBJECTDIR}/RandonImmigrantGenetic.o: RandonImmigrantGenetic.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RandonImmigrantGenetic.o RandonImmigrantGenetic.c

${OBJECTDIR}/SwapMutation.o: SwapMutation.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SwapMutation.o SwapMutation.c

${OBJECTDIR}/TournamentSelection.o: TournamentSelection.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TournamentSelection.o TournamentSelection.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/genetic

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
