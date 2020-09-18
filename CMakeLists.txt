cmake_minimum_required(VERSION 3.17)
project(cub3D C)

set(CMAKE_C_STANDARD 99)

add_executable(
        cub3D
        cub3d.h
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
        cub3d.c
        cub3d_utils.c
        cub3d_utils_map.c
        cub3d_utils_map2.c
        temp_utils.c
        cub3d_utils_info.c
    )
