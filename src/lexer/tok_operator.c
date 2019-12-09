/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:27:56 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:31:12 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			tok_ope_end(t_lexer *lexer, char **str)
{
	if (!lexer->curr_tok->is_delim && is_operator_part(lexer->prev)
			&& !is_operator_next(lexer->curr_tok->content->str, **str))
	{
		delim_token(lexer, str);
		return (1);
	}
	return (0);
}

int			tok_ope_start(t_lexer *lexer, char **str)
{
	if (!lexer->curr_tok->is_delim && is_operator_start(**str))
	{
		delim_token(lexer, str);
		return (1);
	}
	return (0);
}

int			tok_ope_next(t_lexer *lexer, char **str)
{
	if (!lexer->curr_tok->is_delim && is_operator_part(lexer->prev)
			&& is_operator_next(lexer->curr_tok->content->str, **str))
	{
		if (ft_dstr_add(&lexer->curr_tok->content, **str) < 0)
			return (ALLOC_ERROR);
		lexer->prev = **str;
		(*str)++;
		return (1);
	}
	return (0);
}
