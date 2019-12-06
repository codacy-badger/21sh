# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbousset <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/12 15:55:49 by nbousset          #+#    #+#              #
#    Updated: 2019/12/06 01:25:13 by fratajcz         ###   ########.fr        #
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
SRC =		shell/main.c \
			shell/shell_init.c \
			shell/shell_del.c \
			signal/sig_init.c \
			signal/sig_action.c \
			signal/sig_handle.c \
			term/term_init.c \
			term/term_reset.c \
			term/display_char.c \
			term/display_str.c \
			term/display_nl.c \
			term/term_setsize.c \
			term/movcup.c \
			term/movcdown.c \
			term/movcleft.c \
			term/movcright.c \
			term/movchx.c \
			term/movchy.c \
			term/movch.c \
			term/movcex.c \
			term/movcey.c \
			term/movce.c \
			term/clear_fromc.c \
			input/init_reset.c \
			input/multiline_list.c\
			input/move_curs_cardinal.c \
			input/move_curs_special.c \
			input/add_str.c\
			input/del_char.c\
			input/redraw.c\
			input/input_read_line.c \
			input/copypaste.c \
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
