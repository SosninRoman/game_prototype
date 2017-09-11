cmake_minimum_required (VERSION 2.6) 

set (PROJECT game_prototype)

 project (${PROJECT})

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

file(GLOB_RECURSE HEADER_FILES
	"${PROJECT_SOURCE_DIR}/include/*.h"
)

file(GLOB_RECURSE SOURCE_FILES
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
)
set (CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories(${SFML_INCLUDE_DIR})

add_executable (${PROJECT} ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT} PRIVATE 
	"${PROJECT_SOURCE_DIR}/ext/box2d"
	"${PROJECT_SOURCE_DIR}/ext/sfml/include"
	"${PROJECT_SOURCE_DIR}/ext/tinyxml2"
	"${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries (${PROJECT} ${LIBRARIES})
target_link_libraries(${PROJECT} sfml-system sfml-window sfml-graphics sfml-audio)

	
set_target_properties( ${PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )
set_target_properties( tinyxml2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
set_target_properties( sfml-system PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
set_target_properties( sfml-window PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
set_target_properties( sfml-graphics PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
set_target_properties( sfml-audio PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )	