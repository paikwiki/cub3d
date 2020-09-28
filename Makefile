# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paikwiki <paikwiki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/29 01:26:16 by paikwiki          #+#    #+#              #
#    Updated: 2020/09/29 01:26:16 by paikwiki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=	cub3D
LIBFT					=	libft.a
MINILIBX				=	libmlx.a
CC						=	gcc
CFLAGS					=	-Wall -Wextra -Werror -O3 -g -fsanitize=address
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
							./srcs/generate_info.c \
							./srcs/get_info_ceil_floor.c \
							./srcs/handle_key.c \
							./srcs/main.c \
							./srcs/raycasting.c \
							./srcs/utils_info.c \
							./srcs/utils_inits.c \
							./srcs/utils_map.c \
							./srcs/utils_player.c \
							./srcs/utils_raycasting.c \
							./srcs/utils_sprite.c \
							./srcs/utils.c
OBJS					=	${SRCS:.c=.o}
.c.o:
							${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
all: 						$(NAME)
${NAME}:					${OBJS}
							make additional -C ${LIBFT_PATH}
							make -C ${MINILIBX_OPENGL}
							$(CC) $(CFLAGS) ${INCS} ${INCLIB_OPENGL} -o $(NAME) $(OBJS)
clean:
							$(MAKE) -C $(LIBFT_PATH) clean
							#$(MAKE) -C $(MINILIBX_OPENGL) clean
							rm -f $(OBJS)
fclean: 					clean
							$(MAKE) -C $(LIBFT_PATH) fclean
							#rm -f ${MINILIBX_OPENGL}${MINILIBX}
							rm -f $(NAME)
re: 						fclean all
.PHONY: 					all clean fclean re