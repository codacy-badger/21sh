/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_special.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:37:57 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:42:07 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		tok_blank(t_lexer *lexer, char **str)
{
	if (ft_isblank(**str))
	{
		lexer->curr_tok->is_delim = true;
		while (ft_isblank(**str))
		{
			lexer->prev = **str;
			(*str)++;
		}
		return (1);
	}
	return (0);
}

int		tok_eol(t_lexer *lexer, char **str)
{
	if (**str == '\n')
	{
		lexer->curr_tok->is_delim = true;
		if (add_token(lexer, NEWLINE) < 0)
			return (ALLOC_ERROR);
		if (ft_dstr_add(&lexer->curr_tok->content, **str) < 0) //not neccessary ?
			return (ALLOC_ERROR);
		lexer->curr_tok->is_delim = true;
		lexer->prev = **str;
		(*str)++;
		return (1);
	}
	return (0);
}

int		tok_end(t_lexer *lexer, char **str)
{
	if (**str == '\0')
	{
		lexer->curr_tok->is_delim = true;
		if (add_token(lexer, END) < 0)
			return (ALLOC_ERROR);
		return (1);
	}
	return (0);
}

int		tok_hash(t_lexer *lexer, char **str)
{
	if (**str == '#')
	{
		while (**str != '\n')
		{
			lexer->prev = **str;
			(*str)++;
		}
		return (1);
	}
	return (0);
}
