cmake_minimum_required (VERSION 2.6)

set (PROJECT box2d)

project (${PROJECT})
set (CMAKE_CXX_STANDARD 11)
file(GLOB_RECURSE HEADERS
	"Box2D/*.h"
)
file(GLOB_RECURSE SOURCES
	"Box2D/*.cpp"
)

include_directories("./")

add_library(${PROJECT} SHARED ${HEADERS} ${SOURCES})
