NAME = 21sh 
CC = gcc
CFLAGS = -Wall -Wextra #-glldb# -fsanitize=address#-Werror
LFLAGS = -ltermcap
DIR_SRC = src/
DIR_OBJ = obj/
DIR_INC = include/
DIR_LIB = libft/
SRC =		shell/main.c \
			shell/_init.c \
			shell/del.c \
			signal/_init.c \
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
			lexer/_init.c \
			lexer/token.c \
			lexer/type.c \
			lexer/append.c\
			lexer/delim.c \
			lexer/quote.c \
			lexer/eat.c \
			lexer/utils.c
			parser/parser.c
			parser/pipeline.c\
			parser/redirect.c\
			parser/utils.c

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
