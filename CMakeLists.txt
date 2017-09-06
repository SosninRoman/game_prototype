cmake_minimum_required (VERSION 2.6) 

set (PROJECT intro)

 project (${PROJECT})

#include_directories (${PROJECT_SOURCE_DIR}/ext/)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")
	
set (LIBRARIES
		tinyxml2
		box2d
		)

foreach (LIBRARY ${LIBRARIES})
	add_subdirectory (${PROJECT_SOURCE_DIR}/ext/${LIBRARY} bin/${LIBRARY})
endforeach ()
	
if(NOT CMAKE_BUILD_TYPE) 
    set(CMAKE_BUILD_TYPE DEBUG)
endif(NOT CMAKE_BUILD_TYPE)

IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(CONFIGURATION Debug)
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)

IF(CMAKE_BUILD_TYPE MATCHES RELEASE)
    set(CONFIGURATION Release)
ENDIF(CMAKE_BUILD_TYPE MATCHES RELEASE)
	
add_subdirectory(${PROJECT_SOURCE_DIR}/ext/sfml bin/sfml)
#add_subdirectory(${PROJECT_SOURCE_DIR}/ext/box2d bin/box2d)

file(GLOB_RECURSE HEADER_FILES
	"${PROJECT_SOURCE_DIR}/include/*.h"
)

file(GLOB_RECURSE SOURCE_FILES
	#"${PROJECT_SOURCE_DIR}/ext/box2d/Box2D/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
)
set (CMAKE_CXX_STANDARD 11)
#file(GLOB_RECURSE Box2D_FILES
#	"${PROJECT_SOURCE_DIR}/ext/box2d/Box2D/*.cpp"
#)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
#set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

include_directories(${SFML_INCLUDE_DIR})

add_executable (${PROJECT} ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(intro PRIVATE 
	"${PROJECT_SOURCE_DIR}/ext/box2d"
	"${PROJECT_SOURCE_DIR}/ext/sfml/include"
	"${PROJECT_SOURCE_DIR}/ext/tinyxml2"
	"${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries (${PROJECT} ${LIBRARIES})
target_link_libraries(intro sfml-system sfml-window sfml-graphics sfml-audio)
#target_link_libraries(intro box2d)

if (MSVC_IDE)
    # hack to get around the "Debug" and "Release" directories cmake tries to add on Windows
    #set_target_properties (intro PROPERTIES PREFIX "../")
endif()

#if ( MSVC )	
	set_target_properties( intro PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )
    set_target_properties( tinyxml2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
	set_target_properties( sfml-system PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
	set_target_properties( sfml-window PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
	set_target_properties( sfml-graphics PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
	set_target_properties( sfml-audio PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )	
#endif ( MSVC )

#if (WIN32)
if ( MSVC )
	#set_target_properties( intro PROPERTIES CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin )
	#set_target_properties( intro PROPERTIES CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin )
	#set (source "${CMAKE_SOURCE_DIR}/res")
	#set (destination "${CMAKE_CURRENT_BINARY_DIR}/res")
	#add_custom_command(
	#TARGET ${PROJECT} POST_BUILD
	#COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination} 
	#DEPENDS ${destination}
	#COMMENT "symbolic link resources folder from ${source} => ${destination}"
	#)
	#add_custom_command(TARGET intro POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/ext/sfml/bin/sfml-window-d-2.dll"  $<TARGET_FILE_DIR:intro>)
	#add_custom_command(TARGET intro POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_INSTALL_BINDIR}/tinyxml2/libtinyxml2.dll"  $<TARGET_FILE_DIR:intro>)
endif()