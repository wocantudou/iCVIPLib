#  Minimum verion cmake required
cmake_minimum_required(VERSION 3.6)
#  Project
project  (iCVIPLib C CXX)
set(source_dir  "${PROJECT_SOURCE_DIR}/source")

set(ENGINE_NAME iCVIPLib)
set(ENGINE_VERSION_MAJOR 1.0)
set(ENGINE_VERSION_MINOR 100)
set(ENGINE_VERSION_PATCH 0)

FILE(STRINGS "${PROJECT_SOURCE_DIR}/version.txt" contents)
foreach(line ${contents})
    string(FIND "${line}" "#define ENGINE_VERSION_MAJOR" test)
	#MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~test = ${test}")
	#MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~line = ${line}")
    if (NOT(${test} STREQUAL "-1"))
		string(REPLACE "#define ENGINE_VERSION_MAJOR " "" ENGINE_VERSION_MAJOR ${line})
		continue() 
    endif()

    string(FIND "${line}" "#define ENGINE_VERSION_MINOR" test)
    if (NOT(${test} STREQUAL "-1"))
		string(REPLACE "#define ENGINE_VERSION_MINOR " "" ENGINE_VERSION_MINOR ${line})
		continue() 
    endif()

    string(FIND "${line}" "#define ENGINE_VERSION_PATCH" test)
    if (NOT(${test} STREQUAL "-1"))
		string(REPLACE "#define ENGINE_VERSION_PATCH " "" ENGINE_VERSION_PATCH ${line})
		continue() 
    endif()

	string(FIND "${line}" "#define ENGINE_NAME" test)
    if (NOT(${test} STREQUAL "-1"))
		#MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~test = ${test}")
		#MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~line = ${line}")
		string(REPLACE "#define ENGINE_NAME " "" ENGINE_NAME ${line})
		continue() 
    endif()
endforeach()

MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~ENGINE_NAME = ${ENGINE_NAME}")
MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~ENGINE_VERSION_MAJOR = ${ENGINE_VERSION_MAJOR}")
MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~ENGINE_VERSION_MINOR = ${ENGINE_VERSION_MINOR}")
MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~ENGINE_VERSION_PATCH = ${ENGINE_VERSION_PATCH}")

configure_file(
    "${source_dir}/iCVIPLib/iCVIPLib_config.h.in"
		"${PROJECT_BINARY_DIR}/iCVIPLib_config.h"
)

#set (ENGINE_NAME_WITH_VERSION "${ENGINE_NAME}${ENGINE_VERSION_MAJOR}_${ENGINE_VERSION_MINOR}")
string(CONCAT ENGINE_NAME_WITH_VERSION ${ENGINE_NAME} ${ENGINE_VERSION_MAJOR} "." ${ENGINE_VERSION_MINOR} "." ${ENGINE_VERSION_PATCH})
MESSAGE(STATUS "~~~~~~~~~~ENGINE_NAME_WITH_VERSION = ${ENGINE_NAME_WITH_VERSION}")

option(BUILD_IPL_TEST "Build Image Processing lib test." OFF)
option(BUILD_IPL_SHARED "Build shared lib." ON)
option(BUILD_WITH_OPENCV "Build with OpenCV." ON)
option(USE_FFMPEG "Build OpenCV with FFMpeg." OFF)

include(${PROJECT_SOURCE_DIR}/cmake/platform.cmake)
include_directories(
${PROJECT_BINARY_DIR}
)

# OpenCV 4.9.0
include_directories(
    ${PROJECT_SOURCE_DIR}/source/submodules/Opencv4.9.0/include
    ${PROJECT_SOURCE_DIR}/source/submodules/Opencv4.9.0/modules/core/include
    ${PROJECT_SOURCE_DIR}/source/submodules/Opencv4.9.0/modules/features2d/include
    ${PROJECT_SOURCE_DIR}/source/submodules/Opencv4.9.0/modules/flann/include
    ${PROJECT_SOURCE_DIR}/source/submodules/Opencv4.9.0/modules/highgui/include
    ${PROJECT_SOURCE_DIR}/source/submodules/Opencv4.9.0/modules/imgproc/include
    ${PROJECT_SOURCE_DIR}/source/submodules/Opencv4.9.0/modules/imgcodecs/include
    ${PROJECT_SOURCE_DIR}/source/submodules/Opencv4.9.0/modules/videoio/include
    ${PROJECT_SOURCE_DIR}/source/submodules/Opencv4.9.0/modules/calib3d/include
    )

if(BUILD_WITH_OPENCV)
    include_directories(${PROJECT_BINARY_DIR})
    set(BUILD_LIST "calib3d" CACHE STRING "" FORCE)
    list(APPEND BUILD_LIST "videoio")
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(WITH_IPP OFF CACHE BOOL "" FORCE)
    set(WITH_FFMPEG ${USE_FFMPEG} CACHE BOOL "" FORCE)
    add_subdirectory(${source_dir}/submodules/Opencv4.9.0)
else()
    include_directories(${source_dir}/include)
endif()

add_subdirectory(${source_dir}/iCVIPLib)

if (BUILD_IPL_TEST)
    # include_directories(${source_dir}/test)
    # add_subdirectory(${source_dir}/test)
endif()
