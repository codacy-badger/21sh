/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:00 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "shell.h"

/* -------------------------------------------------------
**   The grammar symbols
** -------------------------------------------------------
**
**
**
**
**
**
**%token  DLESS  DGREAT  LESSAND  GREATAND  LESSGREAT  DLESSDASH  AMPERSAND
**         '<<'   '>>'    '<&'     '>&'      '<>'         <<-        '&'
**		  SEMI    PIPE
**		   ';'	   '|'
*/

/*
** different states:
** START is when eat is called normally, with no quotes or
** line continuation problems.
** DELIMITED is the status when a token has been delimited.
** it is reset on next call, cause we want to know if the
** previous token has been delimited or not, to know if we must
** create a new one or append to the current one.
** LINE_CONT is the state where line continuation is required,
** it is set in preprocess(), at the beginning of eat() call.
** END is set when we reach the end of input line.
** -DELIMITED will return the token_type.
** -END and (LINE_CONT or quote) will recall eat()
** -END only will reset lexer and return 0
** it is set in end()
*/
# define START			1
# define DELIMITED		2
# define LINE_CONT		4
# define END			8

//0110

enum 				e_toktype
{
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	TOKEN,
	IO_NUMBER,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	LESSAND,
	GREATAND,
	LESSGREAT,
	DLESSDASH,
	AMPERSAND,
	SEMI,
	PIPE,
	AND_IF,
	OR_IF,
};

enum				e_qstate
{
	NONE = 0,
	BSLASH = '\\',
	SQUOTE = '\'',
	DQUOTE = '"'
};

typedef struct		s_token
{
	t_dstr			*value;
	int				type;
}					t_token;

/*
** -str is a pointer to the current pos in the input string.
** -curr_tok is the current token being delimited.
** -prev_tok is a pointer to the previous token delimited.
** -oldchar is the last char processed.
** -oldsep is the last separator.
** -quote is the quote state.
** -quote len is the number of characters affected by quoting.
** -state is the lexer state. 
*/
typedef struct		s_lexer
{
	struct s_input	*inputp;
	char			*str;
	t_token			*curr_tok;
	t_token			*prev_tok;
	char			oldchar;
	char			oldsep;
	char			quote;
	size_t			quote_len;
	char			state;
}					t_lexer;

int					init_lexer(t_lexer *lexer, t_input *input);
int					eat(t_lexer *lexer);

int					end(t_lexer *lexer);
int					operator_next(t_lexer *lexer);
int					operator_end(t_lexer *lexer);
int     			quote(t_lexer *lexer);
int					operator_new(t_lexer *lexer);
int					blank(t_lexer *lexer);
int					word_next(t_lexer *lexer);
int					comment(t_lexer *lexer);
int					word_start(t_lexer *lexer);

t_token				*token_new(int type);
void				token_del(void **tok, void *priv);
bool    			is_operator_start(char c);
bool    			is_operator_part(char c);
bool    			is_operator_next(char *ope, char c);
bool				is_redir(t_token *token);
int					get_token_type(t_lexer *lexer);
int					get_operator_type(char *ope);
size_t  			get_quote_len(char *str, char quote);

#endif 
