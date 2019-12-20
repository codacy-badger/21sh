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

int		end(t_lexer *lexer)
{
	if (*lexer->str == '\0')
	{
		if (lexer->curr_tok && !lexer->quote && !(lexer->state & LINE_CONT))
			lexer->state |= DELIMITED;
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