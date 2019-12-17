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

/*
int		tok_eol(void *lex, char **str)
{
	t_lexer *lexer;

	lexer = (t_lexer *)lex;
	if (lexer->qstatus)
		return (0);
	if (**str == '\n')
	{
		token_delim(lexer, str);
		if (token_add(lexer, NEWLINE) < 0)
			return (ALLOC_ERROR);
		if (token_add(lexer, END) < 0)
			return (ALLOC_ERROR);
		lexer->prev = *(*str)++;
		return (1);
	}
	return (0);
}

int		tok_blank(void *lex, char **str)
{
	t_lexer *lexer;

	lexer = (t_lexer *)lex;
	if (lexer->qstatus)
		return (0);
	if (ft_isblank(**str))
	{
		token_delim(lexer, str);
		while (ft_isblank(**str))
			lexer->prev = *(*str)++;
		return (1);
	}
	return (0);
}

int		tok_hash(void *lex, char **str)
{
	(void)lex;
	if (**str == '#')
	{
		while (**str != '\n')
			(*str)++;
		return (1);
	}
	return (0);
}
*/