# Find Editline/Ncurses lib and include directories
message(STATUS "Looking for Editline locally.")
find_path(EDITLINE_INCLUDE_DIR 
	NAMES "editline/readline.h"
	HINTS "${CMAKE_PREFIX_PATH}/include"
	)

find_library(EDITLINE_LIBRARY
	NAMES edit_static
	HINTS "${CMAKE_PREFIX_PATH}/lib" "${CMAKE_PREFIX_PATH}/lib/x64/Release"
	)
if (UNIX)
	find_library(NCURSES_LIBRARY
		NAMES ncurses
		PATHS /opt/local/lib /usr/local/lib /usr/lib
		)

	if (EDITLINE_LIBRARY AND EDITLINE_INCLUDE_DIR AND NCURSES_LIBRARY)
		set(EDITLINE_LIBRARIES ${EDITLINE_LIBRARY} ${NCURSES_LIBRARY})
		set(EDITLINE_FOUND "YES")
	else ()
		set(EDITLINE_FOUND "NO")
	endif ()
endif ()

if (WIN32)
	if (EDITLINE_LIBRARY AND EDITLINE_INCLUDE_DIR)
		set(EDITLINE_LIBRARIES ${EDITLINE_LIBRARY})
		set(EDITLINE_FOUND "YES")
	else ()
		set(EDITLINE_FOUND "NO")
	endif ()
endif ()

if (EDITLINE_FOUND)
	#if (NOT EDITLINE_FIND_QUIETLY)
		message(STATUS "Editline include directory: ${EDITLINE_INCLUDE_DIR}")
		message(STATUS "Editline libraries found: ${EDITLINE_LIBRARIES}")
	#endif ()
else ()
	if (EditlineLocal_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find required Editline libraries")
	endif ()
endif ()

mark_as_advanced(
	NCURSES_LIBRARY
	EDITLINE_INCLUDE_DIR
	EDITLINE_LIBRARY
	)
