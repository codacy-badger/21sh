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

static int	delim_token(t_lexer *lexer)
{
	if (lexer->curr_tok)
	{
		if (is_operator_start(*lexer->curr_tok->value->str))
			lexer->curr_tok->type = get_operator_type(lexer->curr_tok->value->str);
		else if ((*lexer->str == '<' || *lexer->str == '>')
		&& ft_strisnbr(lexer->curr_tok->value->str))
			lexer->curr_tok->type = IO_NUMBER;
		lexer->state |= DELIMITED;
	}
	return (0);
}

int			end(t_lexer *lexer)
{
	if (*lexer->str == '\0')
	{
		if (lexer->curr_tok && !lexer->quote && !(lexer->state & LINE_CONT))
			delim_token(lexer);
		lexer->state |= END;
		return (1);
	}
	return (0);
}

int			operator_end(t_lexer *lexer)
{
	if (lexer->curr_tok && !lexer->quote
	&& (is_operator_start(*lexer->curr_tok->value->str)
	&& is_operator_part(lexer->oldchar))
	&& (!is_operator_part(*lexer->str)
	|| !is_operator_next(lexer->curr_tok->value->str, *lexer->str)))
	{
		delim_token(lexer);
		return (1);
	}
	return (0);
}

int			operator_new(t_lexer *lexer)
{
	if (lexer->curr_tok && !lexer->quote
	&& is_operator_start(*lexer->str))
	{
		if ((*lexer->str == '<' || *lexer->str == '>')
		&& ft_strisnbr(lexer->curr_tok->value->str))
			lexer->curr_tok->type = IO_NUMBER;
		delim_token(lexer);
		return (1);
	}
	return (0);
}

int			blank(t_lexer *lexer)
{
	if (!lexer->quote && ft_iswhitespace(*lexer->str))
	{
		if (lexer->curr_tok)
			delim_token(lexer);
		while (ft_iswhitespace(*lexer->str))
		{
			lexer->oldchar = *lexer->str;
			lexer->str++;
		}
		return (1);
	}
	return (0);
}