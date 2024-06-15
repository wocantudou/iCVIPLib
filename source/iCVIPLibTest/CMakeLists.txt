#*************executable target*********
include_directories(
					./
					${PROJECT_SOURCE_DIR}/source/iCVIPLibApi
					)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}  UNIT_TEST)
set(thirdparty_lib_dir "")
set(thirdparty_lib "")

if (NOT MSVC AND NOT CMAKE_SYSTEM_NAME STREQUAL "QNX")
    list(APPEND thirdparty_lib "dl")
endif ()


link_directories(
	${thirdparty_lib_dir}
)

set(EXE_TARGET_NAME iCVIPLibTest)
#*************executable target*********
if(MSVC)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON) #open directory
	#*************executable target*********
	# windows getopt support
	#add_definitions(-D__cplusplus)
	#include_directories(
	#${CMAKE_CURRENT_SOURCE_DIR}/../include/common/get_opt
	#)
	#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../include/common/get_opt  UNIT_TEST)

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

