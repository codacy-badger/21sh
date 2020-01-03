/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:27:56 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/02 17:38:52 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		operator_next(t_lexer *lexer)
{
	if (lexer->curr_tok && !lexer->quote
	&& is_operator_part(lexer->oldchar) && is_operator_part(*lexer->str)
	&& is_operator_next(lexer->curr_tok->value->str, *lexer->str))
	{
		ft_dstr_add(lexer->curr_tok->value, *lexer->str);
		lexer->oldchar = *lexer->str;
		lexer->str++;
		return (1);
	}
	return (0);
}

int		word_next(t_lexer *lexer)
{
	if (lexer->curr_tok)
	{
		ft_dstr_add(lexer->curr_tok->value, *lexer->str);
		lexer->oldchar = *lexer->str;
		if (lexer->quote && --lexer->quote_len == 0)
			lexer->quote = 0;
		lexer->str++;
		return (1);
	}
	return (0);
}

int		comment(t_lexer *lexer)
{
	if (*lexer->str == '#')
	{
		while (*lexer->str && *lexer->str != '\n')
			lexer->str++;
		return (1);
	}
	return (0);
}

/*
** This is the only case where we create a new token, most of the others
** functions will not enter their if statement if curr_tok is set to NULL.
** If the quote state is set, we decrease the quote_len and reset the state
** to NONE when we reach 0.
*/
int		word_start(t_lexer *lexer)
{
	lexer->curr_tok = token_new(WORD);
	ft_dstr_add(lexer->curr_tok->value, *lexer->str);
	lexer->oldchar = *lexer->str;
	if (lexer->quote && --lexer->quote_len == 0)
		lexer->quote = 0;
	lexer->str++;
	return (1);
}
