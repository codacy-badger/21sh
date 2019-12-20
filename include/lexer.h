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
** different states
*/
# define START			1
# define DELIMITED		2
# define LINE_CONT		4
# define END			8

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
** -curr_tok is the current token being delimited, when it is,
**  we set the lexer state to DELIMITED.
** -prev_tok is a pointer to the previous token delimited, it is
**  useful only to set IO_NUMBER token type. IO_NUMBER can be set only
**  when the next token is delimited.
** -oldchar is the last char processed, it is useful when handling
**  an operator, it avoids me to lexer->curr_tok->value->str[lexer->curr_tok->value->len].
** -oldsep is the last separator, it is uselful for IO_NUMBER token.
** -quote is the quote state.
** -quote len is the number of characters affected by quoting, quotes included.
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
int					get_operator_type(char *ope);
size_t  			get_quote_len(char *str, char quote);

#endif 
