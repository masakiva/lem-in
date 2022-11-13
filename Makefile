# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvidal-a <mvidal-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 10:22:25 by mvidal-a          #+#    #+#              #
#    Updated: 2022/11/13 14:22:47 by tkodai           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-----------------------------------------------#
################# PROG_NAME #####################
#-----------------------------------------------#
NAME = lem-in

#-----------------------------------------------#
################## COMPILO ######################
#-----------------------------------------------#
CC = clang

#-----------------------------------------------#
################### PATHS #######################
#-----------------------------------------------#
LIBFT_PATH	+= ./libft/
HDRS_PATH	+= ./headers/
SRCS_PATH	+= ./sources/
OBJS_PATH	+= ./objects/

#-----------------------------------------------#
################## SOURCES ######################
#-----------------------------------------------#
SRCS		+= main.c
SRCS		+= error.c
SRCS		+= parse.c
SRCS		+= parse_states.c
SRCS		+= parse_utils.c
SRCS		+= arg_options.c
SRCS		+= solve.c
SRCS		+= generate_graph.c
SRCS		+= find_max_flow.c
SRCS		+= ft_queue.c
SRCS		+= select_path_set.c
SRCS		+= flow_ants.c
SRCS		+= visualizar.c
SRCS		+= vis_pixel_put.c
SRCS		+= vis_draw_shape.c
SRCS		+= vis_put_info.c

vpath %.c $(SRCS_PATH)

#-----------------------------------------------#
################## HEADERS ######################
#-----------------------------------------------#
HDRS		+= error.h
HDRS		+= parse.h
HDRS		+= solve.h
HDRS		+= ft_queue.h
HDRS		+= ft_vector_int.h
HDRS		+= visualizar.h

vpath %.h $(HDRS_PATH)

#-----------------------------------------------#
################## OBJECTS ######################
#-----------------------------------------------#
OBJS		+= $(addprefix $(OBJS_PATH), $(SRCS:.c=.o))

#-----------------------------------------------#
################### FLAGS #######################
#-----------------------------------------------#
CFLAGS		+= -Wall
CFLAGS		+= -Werror
CFLAGS		+= -Wextra

CPPFLAGS	+= -I $(LIBFT_PATH)
CPPFLAGS	+= -I $(HDRS_PATH)					\

# Multiple header directories
#CPPFLAGS	+= $(foreach DIR, $(HDRS_DIRS), $(addprefix -I , $(DIR)))

#-----------------------------------------------#
################# LIBRARIES #####################
#-----------------------------------------------#
LIBFT_NAME	+= libft.a

LDFLAGS		+= -L $(LIBFT_PATH)

LDLIBS		+= -lft

MINILIB	= minilibx_mms_20200219

MLXFLAG	= libmlx.dylib -framework OpenGL -framework AppKit

MLX		= libmlx.dylib

#-----------------------------------------------#
################### DEBUG #######################
#-----------------------------------------------#
ifeq ($(d), 0)
	CFLAGS	+= -g3
	CFLAGS	+= -Wpadded
	CFLAGS	+= -fsanitize=address,undefined
	LDFLAGS	+= -fsanitize=address,undefined
endif


#-----------------------------------------------#
################### RULES #######################
#-----------------------------------------------#
all:				$(NAME)

$(MLX) :
					cd 	"$(PWD)/$(MINILIB)" && make
					cd 	"$(PWD)/$(MINILIB)" && cp mlx.h ../
					cd 	"$(PWD)/$(MINILIB)" && cp $(MLX) ../$(MLX)

$(NAME):			$(LIBFT_PATH)$(LIBFT_NAME) $(OBJS) $(MLX)
					$(CC) $(LDFLAGS) $(OBJS) $(MLXFLAG) $(LDLIBS) -o $@

$(OBJS_PATH)%.o:	%.c
					$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJS):			Makefile $(HDRS) | $(OBJS_PATH)

$(OBJS_PATH):
					mkdir -p $@

$(LIBFT_PATH)$(LIBFT_NAME):
					$(MAKE) -C $(LIBFT_PATH) bonus custom

lib:
					$(MAKE) -C $(LIBFT_PATH) bonus custom
					$(MAKE) $(NAME)

clean:
					$(MAKE) -C $(LIBFT_PATH) fclean
					$(RM) -r $(OBJS_PATH)

fclean:				clean
					$(RM) $(NAME)
					cd 	"$(PWD)/$(MINILIB)" && $(RM) $(MLX)
					$(RM) libmlx.dylib
					$(RM) mlx.h

re:					fclean all

.PHONY:				all clean fclean re libft
