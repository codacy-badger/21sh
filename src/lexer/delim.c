/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:32:58 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** END_OF_INPUT is set to tell the main while loop to stop.
** -if the quote state is \, this is LINE_CONTINUATION. In the grammar, it
**  is handled before tokenization, the problem is that backslash must not be
**  quoted, so it is more processing, to check all the quotes to see if the
**  last backslash is quoted or not... So I handle this directly here for
**  the moment. It is possible because we dont handle NEWLINE tokens. 
** -if the quote state is set, we don't delim the current token.
*/
int		end(t_lexer *lexer)
{
	if (*lexer->str == '\0')
	{
		if (!lexer->quote)
			lexer->state |= DELIMITED;
		else if (lexer->quote == BSLASH)
		{
			lexer->quote_len--;
			lexer->quote = NONE;
			ft_dstr_remove(lexer->curr_tok->value,
			lexer->curr_tok->value->len - 1, 1);
			if (lexer->curr_tok->value->len == 0)
				token_del((void **)&lexer->curr_tok, NULL);
			lexer->state |= LINE_CONT;
		}
		lexer->state |= END;
		return (1);
	}
	return (0);
}

int		operator_end(t_lexer *lexer)
{
	if (lexer->curr_tok && !lexer->quote
	&& (is_operator_start(*lexer->curr_tok->value->str)
	&& is_operator_part(lexer->oldchar))
	&& (!is_operator_part(*lexer->str)
	|| !is_operator_next(lexer->curr_tok->value->str, *lexer->str)))
	{
		lexer->oldsep = *lexer->str;
		lexer->state |= DELIMITED;
		return (1);
	}
	return (0);
}

int		operator_new(t_lexer *lexer)
{
	if (lexer->curr_tok && !lexer->quote
	&& is_operator_start(*lexer->str))
	{
		lexer->oldsep = *lexer->str;
		lexer->state |= DELIMITED;
		return (1);
	}
	return (0);
}

int		blank(t_lexer *lexer)
{
	if (!lexer->quote && ft_iswhitespace(*lexer->str))
	{
		lexer->oldsep = *lexer->str;
		if (lexer->curr_tok)
			lexer->state |= DELIMITED;
		while (ft_iswhitespace(*lexer->str))
		{
			lexer->oldchar = *lexer->str;
			lexer->str++;
		}
		return (1);
	}
	return (0);
}