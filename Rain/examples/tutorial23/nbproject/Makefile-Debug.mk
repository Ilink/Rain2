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
	${OBJECTDIR}/lighting_technique.o \
	${OBJECTDIR}/tutorial23.o \
	${OBJECTDIR}/glut_backend.o \
	${OBJECTDIR}/mesh.o \
	${OBJECTDIR}/pipeline.o \
	${OBJECTDIR}/shadow_map_fbo.o \
	${OBJECTDIR}/math_3d.o \
	${OBJECTDIR}/camera.o \
	${OBJECTDIR}/technique.o \
	${OBJECTDIR}/shadow_map_technique.o \
	${OBJECTDIR}/texture.o


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
LDLIBSOPTIONS=-lglut -lGLEW -lMagick++ -lassimp

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tutorial23

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tutorial23: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tutorial23 ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/lighting_technique.o: lighting_technique.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/ImageMagick -I/usr/local/include/assimp -MMD -MP -MF $@.d -o ${OBJECTDIR}/lighting_technique.o lighting_technique.cpp

${OBJECTDIR}/tutorial23.o: tutorial23.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/ImageMagick -I/usr/local/include/assimp -MMD -MP -MF $@.d -o ${OBJECTDIR}/tutorial23.o tutorial23.cpp

${OBJECTDIR}/glut_backend.o: glut_backend.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/ImageMagick -I/usr/local/include/assimp -MMD -MP -MF $@.d -o ${OBJECTDIR}/glut_backend.o glut_backend.cpp

${OBJECTDIR}/mesh.o: mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/ImageMagick -I/usr/local/include/assimp -MMD -MP -MF $@.d -o ${OBJECTDIR}/mesh.o mesh.cpp

${OBJECTDIR}/pipeline.o: pipeline.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/ImageMagick -I/usr/local/include/assimp -MMD -MP -MF $@.d -o ${OBJECTDIR}/pipeline.o pipeline.cpp

${OBJECTDIR}/shadow_map_fbo.o: shadow_map_fbo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/ImageMagick -I/usr/local/include/assimp -MMD -MP -MF $@.d -o ${OBJECTDIR}/shadow_map_fbo.o shadow_map_fbo.cpp

${OBJECTDIR}/math_3d.o: math_3d.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/ImageMagick -I/usr/local/include/assimp -MMD -MP -MF $@.d -o ${OBJECTDIR}/math_3d.o math_3d.cpp

${OBJECTDIR}/camera.o: camera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/ImageMagick -I/usr/local/include/assimp -MMD -MP -MF $@.d -o ${OBJECTDIR}/camera.o camera.cpp

${OBJECTDIR}/technique.o: technique.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/ImageMagick -I/usr/local/include/assimp -MMD -MP -MF $@.d -o ${OBJECTDIR}/technique.o technique.cpp

${OBJECTDIR}/shadow_map_technique.o: shadow_map_technique.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/ImageMagick -I/usr/local/include/assimp -MMD -MP -MF $@.d -o ${OBJECTDIR}/shadow_map_technique.o shadow_map_technique.cpp

${OBJECTDIR}/texture.o: texture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/ImageMagick -I/usr/local/include/assimp -MMD -MP -MF $@.d -o ${OBJECTDIR}/texture.o texture.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tutorial23

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
