set(SDL2_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	if (MINGW)
		set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2.dll")
	else()
		set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2main.lib ${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2.lib")
	endif()
else ()
	if (MINGW)
		set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/x86/SDL2.dll")
	else ()
		set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/x86/SDL2main.lib;${CMAKE_CURRENT_LIST_DIR}/lib/x86/SDL2.lib")
	endif ()
endif ()

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
