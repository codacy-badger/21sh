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
	NONE,
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
	enum e_tok_type	type;
}					t_token;

typedef struct		s_lexer
{
	t_list_head		*tokens;
	t_token			*curr_tok;
	t_token			*prev_tok;
}					t_lexer;

int     			lexer_init(t_lexer *lexer);
int					tokenize(t_lexer *lexer, t_input *input);
int    				add_token(t_lexer *lexer, int type);

/*
** Tokenization functions
*/
int					tok_end(t_lexer *lexer, char **str);
int					tok_ope(t_lexer *lexer, char **str);
int					tok_eol(t_lexer *lexer, char **str);
int					tok_spc(t_lexer *lexer, char **str);
int					tok_wrd(t_lexer *lexer, char **str);

/*
** T_token struct
*/
t_token 			*token_new(int type);

#endif 
