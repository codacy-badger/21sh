# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbousset <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/12 15:55:49 by nbousset          #+#    #+#              #
#    Updated: 2019/11/22 00:35:27 by fratajcz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh 
CC = gcc
CFLAGS = -Wall -Wextra #-Werror
LFLAGS = -ltermcap
DIR_SRC = src/
DIR_OBJ = obj/
DIR_INC = include/
DIR_LIB = libft/
SRC =		main.c \
			init/init_shell.c \
			init/init_term.c \
			init/init_input.c \
			init/init_sig.c \
			del/del_shell.c \
			reset/reset_term.c \
			signal/sig_action.c \
			signal/sig_handle.c \
			input/line_new.c \
			input/line_add.c \
			input/line_del.c \
			input/line_add_char.c \
			input/display_char.c \
			input/display_str.c \
			input/display_line.c \
			input/display_nl.c \
			input/move_curs_left.c \
			input/move_curs_right.c \
			input/move_curs_up.c \
			input/move_curs_home.c \
			input/move_curs_nextw.c \
			input/move_curs_prevw.c \
			input/read_line.c \
			utils/utils.c

OBJ = $(addprefix $(DIR_OBJ), $(SRC:.c=.o))
LIB = $(addprefix $(DIR_LIB), libft.a)

all : $(NAME)

$(NAME) : $(OBJ)
	@$(MAKE) -C $(DIR_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(LIB) $(LFLAGS)

$(DIR_OBJ)%.o : $(DIR_SRC)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(DIR_INC)

clean :
	@$(MAKE) clean -C $(DIR_LIB)
	rm -rf $(DIR_OBJ)

fclean : clean
	@$(MAKE) fclean -C $(DIR_LIB)
	rm -rf $(NAME)

re : fclean $(NAME)
