# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbousset <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/12 15:55:49 by nbousset          #+#    #+#              #
#    Updated: 2019/12/08 21:48:10 by fratajcz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh 
CC = gcc
CFLAGS = -Wall -Wextra -glldb# -fsanitize=address#-Werror
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
			term/display.c \
			term/term_setsize.c \
			term/movc_cardinal.c \
			term/clear_fromc.c \
			input/input_init.c \
			input/line.c \
			input/move_curs_cardinal.c \
			input/move_curs_special.c \
			input/add_str.c \
			input/del_char.c \
			input/redraw.c \
			input/read_line.c \
			input/copypaste.c \
			input/history.c \
			input/input_utils.c \
			lexer/lexer_init.c\
			lexer/lexer_utils.c\
			lexer/tok_operator.c\
			lexer/tok_quote.c\
			lexer/tok_special.c\
			lexer/tok_utils.c\
			lexer/tok_word.c\
			lexer/tokenize.c\

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
