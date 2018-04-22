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

#cmake_policy(SET CMP0037 OLD)

# add executables
add_custom_target(makedirs)
add_custom_command(TARGET makedirs
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/misc_examples
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/network_examples
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/cgi_examples
)

# cflags
set(CMAKE_C_FLAGS "-std=c89 -Wall -Wno-unused-function")
set(CMAKE_C_FLAGS_DEBUG "-std=c89 -Wall -Wno-unused-function")
set(CMAKE_C_FLAGS_RELEASE "-std=c89 -Wall -Wno-unused-function")

# misc folder
add_executable(misc_examples/test1 misc_examples/test1.c)
add_dependencies(misc_examples/test1 makedirs)
add_executable(misc_examples/test2 misc_examples/test2.c)
add_dependencies(misc_examples/test2 makedirs)
add_executable(misc_examples/test3 misc_examples/test3.c)
add_dependencies(misc_examples/test3 makedirs)
add_executable(misc_examples/test4 misc_examples/test4.c)
add_dependencies(misc_examples/test4 makedirs)
add_executable(misc_examples/test5 misc_examples/test5.c)
add_dependencies(misc_examples/test5 makedirs)
add_executable(misc_examples/test6 misc_examples/test6.c)
add_dependencies(misc_examples/test6 makedirs)
add_executable(misc_examples/test7 misc_examples/test7.c)
add_dependencies(misc_examples/test7 makedirs)
add_executable(misc_examples/test8 misc_examples/test8.c)
add_dependencies(misc_examples/test8 makedirs)
add_executable(misc_examples/test9 misc_examples/test9.c)
add_dependencies(misc_examples/test9 makedirs)
add_executable(misc_examples/test10 misc_examples/test10.c)
add_dependencies(misc_examples/test10 makedirs)
add_executable(misc_examples/test11 misc_examples/test11.c)
add_dependencies(misc_examples/test11 makedirs)
add_executable(misc_examples/test12 misc_examples/test12.c)
add_dependencies(misc_examples/test12 makedirs)
add_executable(misc_examples/test13 misc_examples/test13.c)
add_dependencies(misc_examples/test13 makedirs)
add_executable(misc_examples/p1 misc_examples/p1.c)
add_dependencies(misc_examples/p1 makedirs)
add_executable(misc_examples/p2 misc_examples/p2.c)
add_dependencies(misc_examples/p2 makedirs)
add_executable(misc_examples/p3 misc_examples/p3.c)
add_dependencies(misc_examples/p3 makedirs)
add_executable(misc_examples/p4 misc_examples/p4.c)
add_dependencies(misc_examples/p4 makedirs)
add_executable(misc_examples/p5 misc_examples/p5.c)
add_dependencies(misc_examples/p5 makedirs)
add_executable(misc_examples/p6 misc_examples/p6.c)
add_dependencies(misc_examples/p6 makedirs)
add_executable(misc_examples/p7 misc_examples/p7.c)
add_dependencies(misc_examples/p7 makedirs)
add_executable(misc_examples/p8 misc_examples/p8.c)
add_dependencies(misc_examples/p8 makedirs)
add_executable(misc_examples/p9 misc_examples/p9.c)
add_dependencies(misc_examples/p9 makedirs)
add_executable(misc_examples/p10 misc_examples/p10.c)
add_dependencies(misc_examples/p10 makedirs)
add_executable(misc_examples/p11 misc_examples/p11.c)
add_dependencies(misc_examples/p11 makedirs)
add_executable(misc_examples/p12 misc_examples/p12.c)
add_dependencies(misc_examples/p12 makedirs)
add_executable(misc_examples/p13 misc_examples/p13.c)
add_dependencies(misc_examples/p13 makedirs)
add_executable(misc_examples/p14 misc_examples/p14.c)
add_dependencies(misc_examples/p14 makedirs)
add_executable(misc_examples/p15 misc_examples/p15.c)
add_dependencies(misc_examples/p15 makedirs)
add_executable(misc_examples/t1 misc_examples/t1.c)
add_dependencies(misc_examples/t1 makedirs)
add_executable(misc_examples/t2 misc_examples/t2.c)
add_dependencies(misc_examples/t2 makedirs)
add_executable(misc_examples/t3 misc_examples/t3.c)
add_dependencies(misc_examples/t3 makedirs)
add_executable(misc_examples/t4 misc_examples/t4.c)
add_dependencies(misc_examples/t4 makedirs)
add_executable(misc_examples/t5 misc_examples/t5.c)
add_dependencies(misc_examples/t5 makedirs)
add_executable(misc_examples/calc misc_examples/calc.c)
add_dependencies(misc_examples/calc makedirs)
add_executable(misc_examples/calc2 misc_examples/calc2.c misc_examples/stack.c misc_examples/getop.c)
add_dependencies(misc_examples/calc2 makedirs)
add_executable(misc_examples/tree misc_examples/tree.c)
add_dependencies(misc_examples/tree makedirs)
add_executable(misc_examples/t6 misc_examples/t6.c)
add_dependencies(misc_examples/t6 makedirs)
add_executable(misc_examples/t7 misc_examples/t7.c)
add_dependencies(misc_examples/t7 makedirs)

# add cgi example targets
add_executable(cgi_examples/test1 cgi_examples/test1.c)
add_dependencies(cgi_examples/test1 makedirs)

# add network example targets
add_executable(network_examples/test1 network_examples/test1.c)
add_dependencies(network_examples/test1 makedirs)
if (WIN32)
	target_link_libraries(network_examples/test1 ws2_32 kernel32 user32)
endif (WIN32)
