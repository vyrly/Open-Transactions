# Find OT lib and include directories
message(STATUS "Looking for OT locally.")
find_path(OTLocal_INCLUDE_DIR_otapi
	NAMES OTAPI.hpp
	HINTS "${CMAKE_PREFIX_PATH}/include" "${CMAKE_PREFIX_PATH}/include/otapi"
	)

find_path(OTLocal_INCLUDE_DIR_otlib
	NAMES OTLib.hpp
	HINTS "${CMAKE_PREFIX_PATH}/include" "${CMAKE_PREFIX_PATH}/include/otlib"
	)

find_library(OTLocal_LIBRARY_otapi
	NAMES otapi
	HINTS "${CMAKE_PREFIX_PATH}/lib" "${CMAKE_PREFIX_PATH}/lib/x64/Release"
	)

if (WIN32)
	find_library(OTLocal_LIBRARY_otlib
		NAMES otlib
		HINTS "${CMAKE_PREFIX_PATH}/lib/x64/Release"
		)
else ()
	find_library(OTLocal_LIBRARY_otlib
		NAMES ot
		HINTS "${CMAKE_PREFIX_PATH}/lib"
		)
endif ()

if (OTLocal_LIBRARY_otapi AND OTLocal_LIBRARY_otlib AND OTLocal_INCLUDE_DIR_otapi AND OTLocal_INCLUDE_DIR_otlib)
	set(OTLocal_LIBRARIES ${OTLocal_LIBRARY_otapi} ${OTLocal_LIBRARY_otlib})
	set(OTLocal_INCLUDE_DIR ${OTLocal_INCLUDE_DIR_otapi} ${OTLocal_INCLUDE_DIR_otlib})
	set(OTLocal_FOUND "YES")
else ()
	set(OTLocal_FOUND "NO")
endif ()

if (OTLocal_FOUND)
	if (NOT OTLocal_FIND_QUIETLY)
		message(STATUS "OT include directory: ${OTLocal_INCLUDE_DIR}")
		message(STATUS "OT libraries found: ${OTLocal_LIBRARIES}")
	endif ()
else ()
	if (OTLocal_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find required OT libraries")
	endif ()
endif ()

mark_as_advanced(
	OTLocal_INCLUDE_DIR
	OTLocal_LIBRARY
	)
