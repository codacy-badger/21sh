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

typedef struct		s_token
{
	t_dstr			*content;
	bool			is_delim;
	enum e_tok_type	type;
}					t_token;

typedef struct		s_lexer
{
	t_list_head		*tokens;
	t_token			*curr_tok;
	t_token			*prev_tok;
	char			prev;
}					t_lexer;

int     			lexer_init(t_lexer *lexer);
int					tokenize(t_lexer *lexer, t_input *input);
int    				add_token(t_lexer *lexer, int type);
void				delim_token(t_lexer *lexer, char **str);

/*
** Tokenization functions
*/
int					tok_end(t_lexer *lexer, char **str);
int     			tok_ope_next(t_lexer *lexer, char **str);
int     			tok_ope_end(t_lexer *lexer, char **str);
int         		tok_quote(t_lexer *lexer, char **str);
//					tok_$
int     			tok_ope_start(t_lexer *lexer, char **str);
int					tok_eol(t_lexer *lexer, char **str);
int     			tok_blank(t_lexer *lexer, char **str);
int     			tok_word_next(t_lexer *lexer, char **str);
int         		tok_hash(t_lexer *lexer, char **str);
int					tok_word_start(t_lexer *lexer, char **str);

/*
** T_token struct
*/
t_token 			*token_new(int type);

/*
** Utils
*/
bool    			is_operator_start(char c);
bool    			is_operator_part(char c);
bool    			is_operator_next(char *ope, char c);
bool   				is_operator_redir(t_token *token);
int     			get_operator_type(char *ope);

#endif 
