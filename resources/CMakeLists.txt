cmake_minimum_required(VERSION 3.17)
project(cub3D C)

SET(CMAKE_C_STANDARD 11)
SET(CMAKE_C_COMPILER gcc)
ADD_COMPILE_OPTIONS(-Wall -Wextra -Werror)

LINK_DIRECTORIES(mlx)
LINK_LIBRARIES(mlx)

add_executable(cub3D
        mlx/mlx.h
        mlx/mlx_int.h
        mlx/mlx_new_window.h
        mlx/mlx_opengl.h
        mlx/mlx_png.h
        includes/cub3d.h
        includes/cub3d_keys.h
        includes/cub3d_structs.h
        libft/ft_lstnew.c
        libft/ft_lstadd_back.c
        libft/ft_lstsize.c
        libft/ft_strchr.c
        libft/ft_strjoin.c
        libft/ft_strlen.c
        libft/ft_strdup.c
        libft/ft_strdup.c
        libft/ft_strndup.c
        libft/ft_strncmp.c
        libft/ft_itoa.c
        libft/ft_split.c
        libft/ft_atoi.c
        libft/ft_uitoa_base.c
        libft/ft_isdigit.c
        libft/ft_calloc.c
        libft/ft_memset.c
        libft/libft.h
        gnl/get_next_line.c
        gnl/get_next_line.h
        srcs/main.c
        srcs/utils.c
        srcs/check_map.c
        srcs/utils_map.c
        srcs/set_info.c
        srcs/get_info_ceil_floor.c
        srcs/utils_info.c
        srcs/handle_key.c
        srcs/init_game.c
        srcs/raycasting.c
        srcs/utils_raycasting.c
        srcs/get_sprite.c
        srcs/set_map.c
        srcs/calc_sprite.c
        srcs/read_cub_file.c
        srcs/process_map.c
        srcs/utils_texture.c
        srcs/process_screenshot.c)

target_link_libraries(cub3D "-framework OpenGL -framework AppKit")