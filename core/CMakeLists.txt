cmake_minimum_required (VERSION 2.6)

set (PROJECT core)

project (${PROJECT})

set (CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE HEADERS
        "../ext/sfml/include/*.h"
        #"../ext/tinyxml2/"
        "../ext/box2d/Box2D/*.h"
        "./scenegraph/include/*.h"
        "./worldsystem/include/*h"
        "./commandsystem/include/*h"
        "./statesystem/include/*h"
        "./common/include/*h"
        "./graphicsystem/include/*h"
)
file(GLOB_RECURSE SOURCES
        "./scenegraph/src/*.cpp"
        "./worldsystem/src/*.cpp"
        "./commandsystem/src/*.cpp"
        "./statesystem/src/*.cpp"
        "./common/src/*.cpp"
        "./graphicsystem/src/*.cpp"
)

#include block
include_directories("./include/")
include_directories("./scenegraph/include/")
include_directories("./worldsystem/include/")
include_directories("./commandsystem/include/")
include_directories("./statesystem/include/")
include_directories("./common/include/")
include_directories("./graphicsystem/include/")
include_directories("../ext/sfml/include/")
#include_directories("../ext/tinyxml2/")
include_directories("../ext/box2d/")
#include_directories(./new_gs/)
include_directories(${SFML_INCLUDE_DIR})

#build ext libs
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

set (LIBRARIES
        tinyxml2
        box2d
        )

foreach (LIBRARY ${LIBRARIES})
    add_subdirectory (${PROJECT_SOURCE_DIR}/../ext/${LIBRARY} bin/${LIBRARY})
endforeach ()

add_subdirectory(${PROJECT_SOURCE_DIR}/../ext/sfml bin/sfml)

add_library(${PROJECT} SHARED ${HEADERS} ${SOURCES} scenegraph/include/SBTAnimation.h scenegraph/src/SBTAnimation.cpp new_gs/SBTFrame.h new_gs/SBTAnimation2.h new_gs/SBTAnimator2.h new_gs/SBTSpriteSequence.h new_gs/SBTSpriteAtlas.h new_gs/SBTSpriteAtlas.cpp)

target_link_libraries(${PROJECT} sfml-system sfml-window sfml-graphics sfml-audio tinyxml2 box2d)

