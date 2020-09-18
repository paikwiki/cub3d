cmake_minimum_required(VERSION 3.17)
project(cub3D C)

set(CMAKE_C_STANDARD 99)

add_executable(
        cub3D
        cub3d.h
        gnl/get_next_line.c
        gnl/get_next_line_utils.c
        gnl/get_next_line.h
        lib/libft/ft_lstnew.c
        lib/libft/ft_lstadd_back.c
        lib/libft/ft_lstsize.c
        lib/libft/ft_strchr.c
        lib/libft/ft_strncmp.c
        lib/libft/ft_itoa.c
        lib/libft/ft_split.c
        lib/libft/ft_atoi.c
        lib/libft/ft_isdigit.c
        lib/libft/libft.h
        cub3d.c
        cub3d_utils.c
        cub3d_utils_map.c
        cub3d_utils_map2.c
        temp_utils.c
        cub3d_utils_info.c
    )
