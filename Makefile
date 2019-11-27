# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbousset <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/12 15:55:49 by nbousset          #+#    #+#              #
#    Updated: 2019/11/27 15:23:39 by fratajcz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh 
CC = gcc
CFLAGS = -Wall -Wextra #-fsanitize=address #-Werror
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
			reset/reset_input.c \
			signal/sig_action.c \
			signal/sig_handle.c \
			term/display_char.c \
			term/display_str.c \
			term/display_nl.c \
			term/set_termsize.c \
			term/movcup.c \
			term/movcdown.c \
			term/movcleft.c \
			term/movcright.c \
			term/movchx.c \
			term/movchy.c \
			term/movch.c \
			input/line_new.c \
			input/line_del.c \
			input/line_add_char.c \
			input/line_del_char.c \
			input/move_curs_left.c \
			input/move_curs_right.c \
			input/move_curs_home.c \
			input/move_curs_end.c \
			input/move_curs_nextw.c \
			input/move_curs_prevw.c \
			input/read_line.c \
			input/copypaste.c \
			input/clear_line.c \
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
