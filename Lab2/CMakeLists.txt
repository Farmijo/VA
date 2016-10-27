cmake_minimum_required( VERSION 2.8.11 )
cmake_policy( VERSION 2.8.11 )

project( AdvancedVisualization )

#include( CMakeDependentOption )

#option( AV_OPTION_NAME "Description" false )

if( ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang" )
    message( STATUS "Found Clang" )
    # no built in variable for Clang so make one
    set (CMAKE_COMPILER_IS_CLANG TRUE)

    if( "${CMAKE_CXX_COMPILER_ID}" MATCHES "AppleClang" )
        message( STATUS "Found Apple Clang" )
        # no built in variable for Apple Clang so make one
        set (CMAKE_COMPILER_IS_APPLE_CLANG TRUE)
    endif()
endif()

if( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG )
    set( CMAKE_COMPILER_IS_GNUCXX_LIKE TRUE )
endif()

# determine bitness
set( IS_64_BIT FALSE )

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set( IS_64_BIT TRUE )
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

# determine processor architecture directory
if( WIN32 )
    # directory names for 32 and 64 bit
    if( IS_64_BIT )
        set( ARCH_DIR "x64" )
    else()
        set( ARCH_DIR "x86" )
    endif()
else()
    # on non windows systems use processor as architecture
    set( ARCH_DIR ${CMAKE_SYSTEM_PROCESSOR} )
endif()

message( STATUS "Using architecture ${ARCH_DIR}" )

# determine compiler directory
if( MSVC )
	set ( COMPILER_DIR "vc14" )
else()
	set ( COMPILER_DIR "linux" )
endif()

message( STATUS "Using compiler ${COMPILER_DIR}" )

# determine platform directory
if( MSVC )
  set ( PLATFORM_DIR "windows" )
else()
  set ( PLATFORM_DIR "linux" )
endif()

message( STATUS "Using platform ${PLATFORM_DIR}" )


function( copy_resources targetName )
    # TODO copy only files for debug or release rather than all DLLs
    if( MSVC )

        message( "${CMAKE_BUILD_TYPE}" )
        if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
            message("debug mode")
        endif()

        # collect a list of all the DLLs to copy
        #
        set( COPY_RES )

		file( GLOB files "3rdParty/freeglut/bin/${ARCH_DIR}/*.dll" )
		set( COPY_RES ${COPY_RES} ${files} )
		
		file( GLOB files "3rdParty/GLEW/bin/${ARCH_DIR}/*.dll" )
		set( COPY_RES ${COPY_RES} ${files} )

		file( GLOB files "3rdParty/SDL2/bin/${ARCH_DIR}/*.dll" )
		set( COPY_RES ${COPY_RES} ${files} )

		file( GLOB files "res/*.ASE" )
		set( COPY_RES ${COPY_RES} ${files} )
		
		file( GLOB files "res/*.bmp" )
		set( COPY_RES ${COPY_RES} ${files} )
		
		file( GLOB files "src/shaders/*.glsl" )
		set( COPY_RES ${COPY_RES} ${files} )

        foreach( RES_FILE ${COPY_RES} )
            add_custom_command( TARGET ${targetName} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different "${RES_FILE}" $<TARGET_FILE_DIR:${targetName}> )
        endforeach()

    endif( MSVC )
endfunction()


if( MSVC )
	message( STATUS "Adding freeglut includes ..." )

    include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/freeglut/include )
	set( FREEGLUT_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/freeglut/lib/${COMPILER_DIR}/${ARCH_DIR} )
endif()

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/GLEW/include )
set( GLEW_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/GLEW/lib/${COMPILER_DIR}/${ARCH_DIR} )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/SDL2/include )
set( SDL2_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/SDL2/lib/${COMPILER_DIR}/${ARCH_DIR} )


if( MSVC )
	message ( STATUS "Visual Studio compiler" )

	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D _CRT_SECURE_NO_WARNINGS" )
endif()

set( ALL_FILES )

set( MAIN
	src/includes.h
	src/main.cpp
)
source_group( "Main" FILES ${MAIN} )
set( ALL_FILES ${ALL_FILES} ${MAIN} )

set( Framework
	src/Application.cpp
    src/Application.h
    src/Camera.cpp
    src/Camera.h
    src/Maths.cpp
    src/Maths.h
    src/Mesh.cpp
    src/Mesh.h
    src/Utils.cpp
    src/Utils.h
)
source_group( "Framework" FILES ${Framework} )
set( ALL_FILES ${ALL_FILES} ${Framework} )



set( Extra
	src/extra/TextParser.cpp
	src/extra/TextParser.h
)
source_group( "Framework\\Extra" FILES ${Extra} )
set( ALL_FILES ${ALL_FILES} ${Extra} )


include_directories( src )

set( ProjectName "Practica2")

message( STATUS "Creating Practice 2 project." )
add_executable( ${ProjectName} ${ALL_FILES} )

copy_resources(${ProjectName})

if( MSVC )
	target_link_libraries( ${ProjectName} opengl32 )
	target_link_libraries( ${ProjectName} glu32 )
#	target_link_libraries( ${ProjectName} ${FREEGLUT_LIB_DIR}/freeglut.lib )
	target_link_libraries( ${ProjectName} ${GLEW_LIB_DIR}/glew32s.lib )

	target_link_libraries( ${ProjectName} ${SDL2_LIB_DIR}/SDL2.lib )
	target_link_libraries( ${ProjectName} ${SDL2_LIB_DIR}/SDL2main.lib )
elseif( CMAKE_COMPILER_IS_GNUCXX_LIKE )
	target_link_libraries( ${ProjectName} X11 )
	target_link_libraries( ${ProjectName} GL )
	target_link_libraries( ${ProjectName} GLU )
	target_link_libraries( ${ProjectName} ${GLEW_LIB_DIR}/libGLEW.so )
	target_link_libraries( ${ProjectName} glut )
	
	message(SEND_ERROR "SDL is not installed")
endif()

