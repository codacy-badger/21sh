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

/*
int		tok_word_next(void *lex, char **str)
{
	t_lexer *lexer;

	lexer = (t_lexer *)lex;
	if (**str && !lexer->curr_tok->delimited)
	{
		if (token_add_char(lexer, str) < 0)
			return (ALLOC_ERROR);
		return (1);
	}
	return (0);
}

int		tok_word_start(void *lex, char **str)
{
	t_lexer *lexer;

	lexer = (t_lexer *)lex;
	if (**str && lexer->curr_tok->delimited)
	{
		if (token_add(lexer, WORD) < 0)
			return (ALLOC_ERROR);
		if (token_add_char(lexer, str) < 0)
			return (ALLOC_ERROR);
		return (1);
	}
	return (0);
}
*/