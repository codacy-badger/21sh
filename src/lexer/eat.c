/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:32:58 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** I need to find more elegant way to handle operators, but for the moment,
** it works. I will think about it...
*/
static int	set_operator_type(t_lexer *lexer)
{
	lexer->curr_tok->type = get_operator_type(lexer->curr_tok->value->str);
	if (is_redir(lexer->curr_tok) && !ft_iswhitespace(lexer->oldsep)
	&& ft_strisnbr(lexer->prev_tok->value->str))
		lexer->prev_tok->type = IO_NUMBER;
	return (0);
}

/*
** Each time the function is called, we reset the state:
**  -if the current token was delimited on previous call, we set prev_tok
**  and reset current to NULL, then reset DELIMITED.
** We tokenize until DELIMITED or END_OF_INPUT is set:
** -If no token has been found, in case of a blank string for example,
**  curr_tok is NULL. We return END. (or NULL if we decide to return token).
** -If a token has been found but is not DELIMITED (because of quotes or backslash),
**  we also return END, we don t want the parser to process the token.
**  The parser will stop parsing and in main(), we ll check lexer state. If
**  LINE_CONTINUATION or quote is set, we can read a new line.
**  On next_call, curr_tok will remain so the tokenization will continue from 
**  the same point.
** -If a token has been found and is DELIMITED, we set its type and return the
**  type (or the token).
*/
int			eat(t_lexer *lexer)
{
	if (lexer->state & DELIMITED)
	{
		lexer->prev_tok = lexer->curr_tok;
		lexer->curr_tok = NULL;
		lexer->state &= ~DELIMITED;
	}
	while (!(lexer->state & (DELIMITED | END_OF_INPUT)))
	{
		if (end(lexer)
		|| operator_next(lexer)
		|| operator_end(lexer)
		|| quote(lexer)
		|| operator_new(lexer)
		|| blank(lexer)
		|| word_next(lexer)
		|| comment(lexer)
		|| word_start(lexer))
			continue ;
	}
	if (lexer->curr_tok && (lexer->state & DELIMITED))
	{
		if (is_operator_start(*lexer->curr_tok->value->str))
			set_operator_type(lexer);
		return (lexer->curr_tok->type);
	}
	return (END);
}
