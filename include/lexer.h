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

# define LEX_OK		0
# define LEX_NO_EOL	1

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
	NEWLINE,
	PIPE
};

enum 				e_quote_type
{
	NONE,
	BACKSLASH = '\\',
	SQUOTE = '\'',
	DQUOTE = '\"'
};

typedef struct		s_token
{
	t_dstr			*content;
	enum e_tok_type	type;
}					t_token;

typedef struct		s_lexer
{
	;
}					t_lexer;

int     			lexer_init(t_lexer *lexer);
int					tokenize(t_lexer *lexer, t_input *input);

#endif 
