cmake_minimum_required(VERSION 3.13)
project(lem_in C)

set(CMAKE_C_STANDARD 99)
find_library(OPEN_GL OpenGl)
find_library(APP_KIT AppKit)

add_compile_options(-Wall -Wextra -Werror) # flags
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake") # CMAKE_CURRENT_LIST_DIR is the directory holding the CMakeLists.txt we are currently using
include_directories(libft/includes/ ./) # directory with headers
link_directories(/usr/local/lib libft/lib)
link_libraries(mlx)
FILE(GLOB LIBFT_SRCS ./libft/std_lib/*.c ./libft/std_lib/printf/*.c)  # ADD LIBFT as sources

AUX_SOURCE_DIRECTORY(libft/std_lib/liblist/ TMP)


add_executable(lem_in main.c lem_in.h parse_input.c check_line_type.c get_room.c
				get_link.c test.c get_paths.c suurballe.c set_weights.c
				priority_queue.c ultimate_exit.c)

add_executable(vizu_hex vizu_hex/vizu_hex_main.c vizu_hex/vizu_hex.h parse_input.c
		check_line_type.c vizu_hex/vh_parse_input.c vizu_hex/prepare_farm.c vizu_hex/vh_get_room.c)

add_executable(htab_test hash_test.c libft/includes/htable.h libft/std_lib/libhtable/ft_htab_init.c
		libft/std_lib/libvector/ft_vec_put.c libft/std_lib/libhtable/ft_htab_get.c)

include(FindPkgConfig)
find_package(ft REQUIRED)
include_directories(${ft_INCLUDE_DIR})
target_link_libraries (lem_in ft ${OPEN_GL} ${APP_KIT})
target_link_libraries(htab_test ft)
