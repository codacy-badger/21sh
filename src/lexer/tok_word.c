/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:34:05 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:34:35 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		tok_word_next(t_lexer *lexer, char **str)
{
	if (**str && !lexer->curr_tok->is_delim)
	{
		if (ft_dstr_add(&lexer->curr_tok->content, **str) < 0)
			return (ALLOC_ERROR);
		lexer->prev = **str;
		(*str)++;
		return (1);
	}
	return (0);
}

int		tok_word_start(t_lexer *lexer, char **str)
{
	if (**str && lexer->curr_tok->is_delim)
	{
		if (add_token(lexer, WORD) < 0)
			return (ALLOC_ERROR);
		ft_dstr_add(&lexer->curr_tok->content, **str);
		lexer->prev = **str;
		(*str)++;
		return (1);
	}
	return (0);
}
