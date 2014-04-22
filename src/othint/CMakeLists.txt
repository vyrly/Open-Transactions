cmake_minimum_required (VERSION 2.6)
project (othint)

# Options

option(LOCAL_EDITLINE "Use local Editline library ($HOME/.local)" ON) # Always ON because of bugs in Debian libedit package!
option(WITH_WRAPPER "Build with wrapper" OFF)
option(LOCAL_OT "Build with locally installed ot" ON)

# Set variables


set(CMAKE_SKIP_BUILD_RPATH  FALSE) # Always include RPATH to the binary

if (WITH_WRAPPER)
	set(CMAKE_CXX_COMPILER "$ENV{HOME}/.local/bin/compile-cxx")
	set(CMAKE_CC_COMPILER "$ENV{HOME}/.local/bin/compile-cc")
	message(STATUS "Option was set to use WRAPPER. Using CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
else ()
	message(STATUS "Option was NOT set for wrapper. Using CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
endif (WITH_WRAPPER)

set(CMAKE_CXX_FLAGS "-std=c++11 -g3 -O0 ")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/") # Add folder with cmake modules

# Add executable

file(GLOB othint_SRC # All files in directory:
	"*.h"
	"*.hpp"
	"*.cpp"
)

add_executable(othint ${othint_SRC})

# Find libraries and headers for Editline

if (LOCAL_EDITLINE)
	find_package(EditlineLocal REQUIRED)
	if (EDITLINE_FOUND)
		include_directories(${EDITLINE_INCLUDE_DIR})
		target_link_libraries (othint ${EDITLINE_LIBRARIES})
	endif (EDITLINE_FOUND)
else ()
	find_package(Editline REQUIRED)
	if (EDITLINE_FOUND)
		include_directories(${EDITLINE_INCLUDE_DIR})
		target_link_libraries (othint ${EDITLINE_LIBRARIES})
	endif (EDITLINE_FOUND)
endif(LOCAL_EDITLINE)

# Find libraries and headers for OT

if (LOCAL_OT)
	find_package(OTLocal REQUIRED)
	if (OTLocal_FOUND)
		include_directories(${OTLocal_INCLUDE_DIR})
		target_link_libraries (othint ${OTLocal_LIBRARIES})
	endif (OTLocal_FOUND)
endif(LOCAL_OT)

# make run
add_custom_target(run
		COMMAND bash run-devel.sh
    DEPENDS othint
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
