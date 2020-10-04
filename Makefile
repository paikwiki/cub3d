# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/29 01:26:16 by cbaek             #+#    #+#              #
#    Updated: 2020/10/02 23:21:44 by cbaek            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=	cub3D
LIBFT					=	libft.a
MINILIBX				=	libmlx.a
CC						=	gcc
CFLAGS					=	-Wall -Wextra -Werror
RM						=	rm -f
INCLUDES_PATH			=	./includes/
LIBFT_PATH				=	./libft/
GET_NEXT_LINE_PATH		=	./gnl/
MINILIBX_OPENGL			=	./mlx/
INCS					=	-I${INCLUDES_PATH} -I${LIBFT_PATH} -I${MINILIBX_OPENGL}
INCLIB_OPENGL			=	-L${MINILIBX_OPENGL} -lmlx -framework OpenGL -framework Appkit \
							-L${LIBFT_PATH} -lft
SRCS					=	./gnl/get_next_line.c \
							./srcs/calc_sprite.c \
							./srcs/check_map.c \
							./srcs/get_info_ceil_floor.c \
							./srcs/get_sprite.c \
							./srcs/handle_key.c \
							./srcs/init_game.c \
							./srcs/main.c \
							./srcs/process_map.c \
							./srcs/process_screenshot.c \
							./srcs/raycasting.c \
							./srcs/read_cub_file.c \
							./srcs/set_info.c \
							./srcs/set_map.c \
							./srcs/utils.c \
							./srcs/utils_info.c \
							./srcs/utils_map.c \
							./srcs/utils_raycasting.c \
							./srcs/utils_texture.c
SRCS_BONUS				=	./gnl/get_next_line.c \
							./srcs_bonus/calc_sprite_bonus.c \
							./srcs_bonus/check_map_bonus.c \
							./srcs_bonus/get_info_ceil_floor_bonus.c \
							./srcs_bonus/get_sprite_bonus.c \
							./srcs_bonus/handle_key_bonus.c \
							./srcs_bonus/init_game_bonus.c \
							./srcs_bonus/main_bonus.c \
							./srcs_bonus/process_map_bonus.c \
							./srcs_bonus/process_screenshot_bonus.c \
							./srcs_bonus/raycasting_bonus.c \
							./srcs_bonus/read_cub_file_bonus.c \
							./srcs_bonus/set_info_bonus.c \
							./srcs_bonus/set_map_bonus.c \
							./srcs_bonus/utils_bonus.c \
							./srcs_bonus/utils_info_bonus.c \
							./srcs_bonus/utils_map_bonus.c \
							./srcs_bonus/utils_raycasting_bonus.c \
							./srcs_bonus/utils_texture_bonus.c
OBJS					=	${SRCS:.c=.o}
OBJS_BONUS				=	${SRCS_BONUS:.c=.o}
.c.o:
							${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
${NAME}:					${OBJS}
							make additional -C ${LIBFT_PATH}
							make -C ${MINILIBX_OPENGL}
							$(CC) $(CFLAGS) ${INCS} ${INCLIB_OPENGL} -o $(NAME) $(OBJS)
all: 						$(NAME)
clean:
							$(MAKE) -C $(LIBFT_PATH) clean
							#$(MAKE) -C $(MINILIBX_OPENGL) clean
							rm -f $(OBJS)
							rm -f $(OBJS_BONUS)
fclean: 					clean
							$(MAKE) -C $(LIBFT_PATH) fclean
							#rm -f ${MINILIBX_OPENGL}${MINILIBX}
							rm -f $(NAME)
re: 						fclean all
bonus:						${OBJS_BONUS}
							make additional -C ${LIBFT_PATH}
							make -C ${MINILIBX_OPENGL}
							$(CC) $(CFLAGS) ${INCS} ${INCLIB_OPENGL} -o $(NAME) $(OBJS_BONUS)
.PHONY: 					all clean fclean re
