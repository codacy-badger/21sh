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

int		tok_ope_next(void *lex, char **str)
{
	t_lexer *lexer;

	lexer = (t_lexer *)lex;
	if (lexer->qstatus)
		return (0);
	if (!lexer->curr_tok->delimited && is_operator_part(lexer->prev)
			&& is_operator_next(lexer->curr_tok->content->str, **str))
	{
		if (token_add_char(lexer, str) < 0)
			return (ALLOC_ERROR);
		return (0);
	}
	return (0);
}

int		tok_ope_end(void *lex, char **str)
{
	t_lexer *lexer;

	lexer = (t_lexer *)lex;
	if (lexer->qstatus)
		return (0);
	if (!lexer->curr_tok->delimited && is_operator_part(lexer->prev)
			&& !is_operator_next(lexer->curr_tok->content->str, **str))
	{
		token_delim(lexer, str);
		return (1);
	}
	return (0);
}

int		tok_ope_start(void *lex, char **str)
{
	t_lexer *lexer;

	lexer = (t_lexer *)lex;
	if (lexer->qstatus)
		return (0);
	if (!lexer->curr_tok->delimited && is_operator_start(**str))
	{
		token_delim(lexer, str);
		return (1);
	}
	return (0);
}