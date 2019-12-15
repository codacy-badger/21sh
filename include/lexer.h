/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/15 11:00:15 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "shell.h"

/* -------------------------------------------------------
**   The grammar symbols
**   -------------------------------------------------------
**
**
**
**
**
**
**%token  DLESS  DGREAT  LESSAND  GREATAND  LESSGREAT  DLESSDASH  AMPERSAND
**         '<<'   '>>'    '<&'     '>&'      '<>'       '<<-'        '&'
**		  SEMI    PIPE
**		   ';'	   '|'
*/
struct	s_token;
struct s_lexer;

# define FUNC_NB	9

enum 				e_tok_type
{
	START,
	END,
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	IO_NUMBER,
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
	NEWLINE
};

enum				e_qstatus
{
	NONE = 0,
	BSLASH = '\\',
	SQUOTE = '\'',
	DQUOTE = '"'
};

typedef struct		s_token
{
	t_dstr			*content;
	bool			delimited;
	enum e_tok_type	type;
}					t_token;

/*
** qstatus is the current quote status of the lexer:
** backslash, quote, dquote.
**
** In tok_quote, we set qstatus and we return 0
** so the while loop will not "continue" (it would cause 
** an infinite loop because the pointer is still on the quote).
** Like this tok_word_next() || tok_word_start() will do their jobs
** adding the chars to current token.
** The functions like tok_ope_start will not enter in their
** if statements if is the qstatus is != 0;
**
** dont need tok_end() anymore, maybe to handle eof, removed it.
*/

/*
** Need void * to avoid chicken and egg problems
*/
typedef int			(*t_lex_func)(void *, char **);

typedef struct		s_lexer
{
	t_list_head		*tokens;
	t_lex_func		ftable[FUNC_NB];
	t_token			*curr_tok;
	t_token			*prev_tok;
	char			prev_sep;
	enum e_qstatus	qstatus;
	char			prev;
}					t_lexer;

int     			lexer_init(t_lexer *lexer);
int					tokenize(t_lexer *lexer, t_input *input);
int					token_add_char(t_lexer *lexer, char **str);
int    				token_add(t_lexer *lexer, int type);
void				token_delim(t_lexer *lexer, char **str);
t_token 			*token_new(int type);
void				token_del(void *tok, void *priv);

/*
** Tokenization functions
*/
int     			tok_ope_next(void *lex, char **str);
int     			tok_ope_end(void *lex, char **str);
int         		tok_quote(void *lex, char **str);
//					tok_$
int     			tok_ope_start(void *lex, char **str);
int					tok_eol(void *lex, char **str);
int     			tok_blank(void *lex, char **str);
int     			tok_word_next(void *lex, char **str);
int         		tok_hash(void *lex, char **str);
int					tok_word_start(void *lex, char **str);

/*
** Utils
*/
bool    			is_operator_start(char c);
bool    			is_operator_part(char c);
bool    			is_operator_next(char *ope, char c);
bool   				is_operator_redir(t_token *token);
int     			get_operator_type(char *ope);

#endif 
