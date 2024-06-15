#generate library
include_directories(
					./
					${PROJECT_SOURCE_DIR}/source/include
					)
                    
#***************static library************
aux_source_directory(.  iCVIPLib_STATIC_LIB)
#***************shared library************
aux_source_directory(.  iCVIPLib_SHARED_LIB)

set(thirdparty_lib "")
set(thirdparty_lib_dir "")
list(APPEND thirdparty_lib_dir ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
list(APPEND thirdparty_lib_dir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" AND NOT BUILD_WITH_OPENCV)
	if (MSVC)
		list(APPEND thirdparty_lib "opencv_imgcodecs409d")
		list(APPEND thirdparty_lib "opencv_flann409d;opencv_calib3d409d;opencv_imgproc409d;opencv_core409d")
	else()
		list(APPEND thirdparty_lib "opencv_imgcodecsd")
		list(APPEND thirdparty_lib "opencv_flannd;opencv_calib3dd;opencv_imgprocd;opencv_cored")
	endif()
	list(APPEND thirdparty_lib "ittnotifyd;libpngd;libtiffd;libjpeg-turbod;libwebpd;zlibd;libopenjp2d")
else()
	if (MSVC)
		list(APPEND thirdparty_lib "opencv_imgcodecs409")
		list(APPEND thirdparty_lib "opencv_flann409;opencv_calib3d409;opencv_imgproc409;opencv_core409")
	else()
		list(APPEND thirdparty_lib "opencv_imgcodecs")
		list(APPEND thirdparty_lib "opencv_flann;opencv_calib3d;opencv_imgproc;opencv_core")
	endif()
	list(APPEND thirdparty_lib "ittnotify;libpng;libtiff;libjpeg-turbo;libwebp;zlib;libopenjp2")
endif()
link_directories(${thirdparty_lib_dir})
MESSAGE(STATUS "************thirdparty_lib_dir = ${thirdparty_lib_dir}")

if(MSVC)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON) #open directory
	#***************static library************
	add_library(iCVIPLib_static STATIC ${iCVIPLib_STATIC_LIB})
	#target_link_libraries (iCVIPLib_static ${thirdparty_lib})
	set_property(TARGET iCVIPLib_static PROPERTY FOLDER "iCVIPLibApi")
	#***************shared library************
	if(BUILD_IPL_SHARED)
		add_library(iCVIPLib_shared SHARED ${iCVIPLib_SHARED_LIB})
		target_link_libraries (iCVIPLib_shared ${thirdparty_lib})
		set_property(TARGET iCVIPLib_shared PROPERTY FOLDER "iCVIPLibApi")
	endif()
else ()
	#***************static library************
	add_library(${ENGINE_NAME_WITH_VERSION} STATIC ${iCVIPLib_STATIC_LIB})
	# set_target_properties(${ENGINE_NAME_WITH_VERSION} PROPERTIES LINK_FLAGS "-Wl,--no-undefined,--retain-symbols-file,${CMAKE_CURRENT_SOURCE_DIR}/iCVFrameWork_static.sym")
	#***************shared library************
    if(BUILD_IPL_SHARED)
		# for shared
		if (CMAKE_SYSTEM_NAME STREQUAL "Android")
			add_library(${ENGINE_NAME_WITH_VERSION} SHARED ${iCVIPLib_SHARED_LIB})
			target_link_libraries(${ENGINE_NAME_WITH_VERSION} ${thirdparty_lib})
		else()
			set(ENGINE_NAME_WITH_VERSION ${ENGINE_NAME} CACHE STRING "" FORCE)
			add_library(${ENGINE_NAME_WITH_VERSION} SHARED ${iCVIPLib_SHARED_LIB})
			target_link_libraries(${ENGINE_NAME_WITH_VERSION} ${thirdparty_lib})
			set_target_properties(${ENGINE_NAME_WITH_VERSION} PROPERTIES VERSION ${ENGINE_VERSION_MAJOR}.${ENGINE_VERSION_MINOR}.${ENGINE_VERSION_PATCH} SOVERSION ${ENGINE_VERSION_MAJOR})
		endif()
		if (NOT APPLE AND "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
			add_custom_command(TARGET ${ENGINE_NAME_WITH_VERSION} POST_BUILD
				WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
				COMMAND ${CMAKE_STRIP} -s "lib${ENGINE_NAME_WITH_VERSION}.so"
			)
			# set_target_properties(${ENGINE_NAME_WITH_VERSION} PROPERTIES LINK_FLAGS "-Wl,--no-undefined,--version-script,${CMAKE_CURRENT_SOURCE_DIR}/iCVFrameWork_shared.map")
		endif()		
	endif()
endif()
