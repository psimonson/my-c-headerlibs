cmake_minimum_required (VERSION 2.8)
project (EXAMPLES)
# version number
set (EXAMPLES_VERSION_MAJOR 1)
set (EXAMPLES_VERSION_MINOR 0)

# config files
configure_file (
	"${PROJECT_SOURCE_DIR}/examples_config.h.in"
	"${PROJECT_BINARY_DIR}/examples_config.h"
)

# include binary directory for config file
include_directories("${PROJECT_BINARY_DIR}")

cmake_policy(SET CMP0037 OLD)

# add executables
add_custom_target(makedirs)
add_custom_command(TARGET makedirs
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/misc
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/network
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/cgi
)

# cflags
set(CMAKE_C_FLAGS "-std=c89 -Wall -Wno-unused-function")
set(CMAKE_C_FLAGS_DEBUG "-std=c89 -Wall -Wno-unused-function")
set(CMAKE_C_FLAGS_RELEASE "-std=c89 -Wall -Wno-unused-function")
set(CMAKE_CXX_FLAGS "-std=c++89 -Wall -Wno-unused-function")
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++89 -Wall -Wno-unused-function")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++89 -Wall -Wno-unused-function")

# misc folder
add_executable(misc/test1 misc/test1.c)
add_dependencies(misc/test1 makedirs)
add_executable(misc/test2 misc/test2.c)
add_dependencies(misc/test2 makedirs)
add_executable(misc/test3 misc/test3.c)
add_dependencies(misc/test3 makedirs)
add_executable(misc/test4 misc/test4.c)
add_dependencies(misc/test4 makedirs)
add_executable(misc/test5 misc/test5.c)
add_dependencies(misc/test5 makedirs)
add_executable(misc/test6 misc/test6.c)
add_dependencies(misc/test6 makedirs)
add_executable(misc/test7 misc/test7.c)
add_dependencies(misc/test7 makedirs)
add_executable(misc/test8 misc/test8.c)
add_dependencies(misc/test8 makedirs)
add_executable(misc/test9 misc/test9.c)
add_dependencies(misc/test9 makedirs)
add_executable(misc/test10 misc/test10.c)
add_dependencies(misc/test10 makedirs)
add_executable(misc/test11 misc/test11.c)
add_dependencies(misc/test11 makedirs)
add_executable(misc/test12 misc/test12.c)
add_dependencies(misc/test12 makedirs)
add_executable(misc/test13 misc/test13.c)
add_dependencies(misc/test13 makedirs)
add_executable(misc/p1 misc/p1.c)
add_dependencies(misc/p1 makedirs)
add_executable(misc/p2 misc/p2.c)
add_dependencies(misc/p2 makedirs)
add_executable(misc/p3 misc/p3.c)
add_dependencies(misc/p3 makedirs)
add_executable(misc/p4 misc/p4.c)
add_dependencies(misc/p4 makedirs)
add_executable(misc/p5 misc/p5.c)
add_dependencies(misc/p5 makedirs)
add_executable(misc/p6 misc/p6.c)
add_dependencies(misc/p6 makedirs)
add_executable(misc/p7 misc/p7.c)
add_dependencies(misc/p7 makedirs)
add_executable(misc/p8 misc/p8.c)
add_dependencies(misc/p8 makedirs)
add_executable(misc/p9 misc/p9.c)
add_dependencies(misc/p9 makedirs)
add_executable(misc/p10 misc/p10.c)
add_dependencies(misc/p10 makedirs)
add_executable(misc/p11 misc/p11.c)
add_dependencies(misc/p11 makedirs)
add_executable(misc/p12 misc/p12.c)
add_dependencies(misc/p12 makedirs)
add_executable(misc/p13 misc/p13.c)
add_dependencies(misc/p13 makedirs)
add_executable(misc/p14 misc/p14.c)
add_dependencies(misc/p14 makedirs)
add_executable(misc/p15 misc/p15.c)
add_dependencies(misc/p15 makedirs)
add_executable(misc/t1 misc/t1.c)
add_dependencies(misc/t1 makedirs)
add_executable(misc/t2 misc/t2.c)
add_dependencies(misc/t2 makedirs)
add_executable(misc/t3 misc/t3.c)
add_dependencies(misc/t3 makedirs)
add_executable(misc/t4 misc/t4.c)
add_dependencies(misc/t4 makedirs)
add_executable(misc/t5 misc/t5.c)
add_dependencies(misc/t5 makedirs)
add_executable(misc/calc misc/calc.c)
add_dependencies(misc/calc makedirs)

# add cgi example targets
add_executable(cgi/test1 cgi/test1.c)
add_dependencies(cgi/test1 makedirs)

# add network example targets
add_executable(network/test1 network/test1.c)
add_dependencies(network/test1 makedirs)
