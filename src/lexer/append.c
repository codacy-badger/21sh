/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:27:56 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/09 12:41:12 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		operator_next(t_lexer *lexer)
{
	if (lexer->curr_tok && !lexer->quote
	&& (lexer->i != 0 ? is_operator_part(lexer->str[lexer->i - 1]) : 0)
	&& is_operator_part(lexer->str[lexer->i])
	&& is_operator_next(lexer->curr_tok->value->str, lexer->str[lexer->i]))
	{
		ft_dstr_add(lexer->curr_tok->value, lexer->str[lexer->i]);
		lexer->i++;
		return (1);
	}
	return (0);
}

int		word_next(t_lexer *lexer)
{
	if (lexer->curr_tok)
	{
		ft_dstr_add(lexer->curr_tok->value, lexer->str[lexer->i]);
		lexer->i++;
		return (1);
	}
	return (0);
}

int		comment(t_lexer *lexer)
{
	if (*lexer->str == '#')
	{
		while (lexer->str[lexer->i] && lexer->str[lexer->i] != '\n')
			lexer->i++;
		return (1);
	}
	return (0);
}

/*
** This is the only case where we create a new token, most of the others
** functions will not enter their if statement if curr_tok is set to NULL.
*/

int		word_start(t_lexer *lexer)
{
	lexer->curr_tok = token_new(WORD);
	ft_dstr_add(lexer->curr_tok->value, lexer->str[lexer->i]);
	lexer->i++;
	return (1);
}
