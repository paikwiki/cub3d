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
        includes/main.h
        libft/ft_lstnew.c
        libft/ft_lstadd_back.c
        libft/ft_lstsize.c
        libft/ft_strchr.c
        libft/ft_strjoin.c
        libft/ft_strlen.c
        libft/ft_strndup.c
        libft/ft_strncmp.c
        libft/ft_itoa.c
        libft/ft_split.c
        libft/ft_atoi.c
        libft/ft_isdigit.c
        libft/libft.h
        gnl/get_next_line.c
        gnl/get_next_line.h
        srcs/main.c
        srcs/utils.c
        srcs/utils_map.c
        srcs/utils_map2.c
        temp_utils.c
        srcs/utils_info.c
        srcs/utils_player.c)

target_link_libraries(cub3D "-framework OpenGL -framework AppKit")