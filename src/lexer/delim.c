/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/13 19:15:17 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	delim_token(t_lexer *lexer)
{
	if (lexer->curr_tok)
	{
		if (is_operator_start(*lexer->curr_tok->value->str))
			lexer->curr_tok->type =
			get_operator_type(lexer->curr_tok->value->str);
		else if ((lexer->str[lexer->i] == '<' || lexer->str[lexer->i] == '>')
		&& ft_strisnbr(lexer->curr_tok->value->str))
			lexer->curr_tok->type = IO_NUMBER;
		lexer->state |= DELIMITED;
	}
	return (0);
}

int			end(t_lexer *lexer)
{
	if (lexer->str[lexer->i] == '\0' || lexer->i == lexer->len - 1)
	{
		if (lexer->curr_tok && !lexer->quote)
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
	&& (lexer->i > 0 ? is_operator_part(lexer->str[lexer->i - 1]) : 0))
	&& (!is_operator_part(lexer->str[lexer->i])
	|| !is_operator_next(lexer->curr_tok->value->str, lexer->str[lexer->i])))
	{
		delim_token(lexer);
		return (1);
	}
	return (0);
}

int			operator_new(t_lexer *lexer)
{
	if (lexer->curr_tok && !lexer->quote
	&& is_operator_start(lexer->str[lexer->i]))
	{
		if ((lexer->str[lexer->i] == '<' || lexer->str[lexer->i] == '>')
		&& ft_strisnbr(lexer->curr_tok->value->str))
			lexer->curr_tok->type = IO_NUMBER;
		delim_token(lexer);
		return (1);
	}
	return (0);
}

int			blank(t_lexer *lexer)
{
	if (!lexer->quote && ft_iswhitespace(lexer->str[lexer->i]))
	{
		if (lexer->curr_tok)
			delim_token(lexer);
		while (ft_iswhitespace(lexer->str[lexer->i]))
			lexer->i++;
		return (1);
	}
	return (0);
}
