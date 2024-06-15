#*************executable target*********
include_directories(
					./
					${PROJECT_SOURCE_DIR}/source/iCVIPLibApi
					${PROJECT_SOURCE_DIR}/source/include
					)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}  UNIT_TEST)
set(thirdparty_lib_dir "")
set(thirdparty_lib "")

if(MSVC)
	list(APPEND thirdparty_lib_dir "../../thirdparty/opencv/x64/vc15/lib")
	list(APPEND thirdparty_lib_dir ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
	list(APPEND thirdparty_lib_dir ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
	list(APPEND thirdparty_lib ${ENGINE_NAME_WITH_VERSION})
else ()
	# add thridyparty library
	list(APPEND thirdparty_lib_dir ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
	list(APPEND thirdparty_lib_dir ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
	if (NOT CMAKE_SYSTEM_NAME STREQUAL "QNX")
		list(APPEND thirdparty_lib "dl")
	endif ()
	if (CMAKE_SYSTEM_NAME STREQUAL "Android")
		list(APPEND thirdparty_lib ${ENGINE_NAME_WITH_VERSION})
	else()
		list(APPEND thirdparty_lib ${ENGINE_NAME})
	endif()
endif ()

link_directories(
    ${thirdparty_lib_dir}
)

set(EXE_TARGET_NAME iCVIPLibTest)
#*************executable target*********
if(MSVC)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON) #open directory
	#*************executable target*********
	add_executable(${EXE_TARGET_NAME}  ${UNIT_TEST})
	target_link_libraries (${EXE_TARGET_NAME} ${thirdparty_lib})
	set_property(TARGET ${EXE_TARGET_NAME} PROPERTY FOLDER "iCVIPLibTest")
	#new add 
	SET_TARGET_PROPERTIES(${EXE_TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}")
	set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)
	target_include_directories(${EXE_TARGET_NAME} PUBLIC ${INC_DIR})
	# source_group(TREE ${INC_DIR} PREFIX "Header Files" FILES ${INC_DIR}/iCVLogger/*.h ${INC_DIR}/utils/*.hpp ${INC_DIR}/iCVLogger/*.h ${INC_DIR}/iCVJson/*hpp ${INC_DIR}/iCVConfig/*hpp)
else()
	add_executable(${EXE_TARGET_NAME}  ${UNIT_TEST})
	target_link_libraries (${EXE_TARGET_NAME} ${thirdparty_lib})
	if (NOT APPLE AND "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
		add_custom_command(TARGET ${EXE_TARGET_NAME} POST_BUILD
							WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
							COMMAND ${CMAKE_STRIP} "-s" "${EXE_TARGET_NAME}")
	endif ()
endif ()

