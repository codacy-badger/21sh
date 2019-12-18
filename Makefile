# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbousset <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/12 15:55:49 by nbousset          #+#    #+#              #
#    Updated: 2019/12/18 19:19:06 by fratajcz         ###   ########.fr        #
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
			shell/_init.c \
			shell/del.c \
			signal/_init.c \
			shell/utils.c\
			shell/env_utils.c\
			shell/path_utils.c\
			signal/sig_action.c \
			signal/sig_handle.c \
			term/_init.c \
			term/print.c \
			term/cursor.c \
			term/clear.c \
			term/window.c \
			input/_init.c \
			input/move_basic.c \
			input/move_spec.c \
			input/delchar.c \
			input/enter.c \
			input/draw.c \
			input/readline.c \
			input/copypaste.c \
			input/history.c \
			lexer/lexer_utils.c\
			lexer/lexer_init.c\
			lexer/token_add_char.c \
			lexer/token_add.c \
			lexer/token_delim.c \
			lexer/token_new.c \
			lexer/token_del.c \
			lexer/tok_operator.c\
			lexer/tok_quote.c\
			lexer/tok_special.c\
			lexer/tok_word.c\
			lexer/tokenize.c\
			parser/parser.c\
			parser/pipeline.c\
			parser/redirect.c\
			parser/utils.c\
			exec/get_argv.c\
			exec/exec.c\
			exec/redir.c\
			exec/pipe.c

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
