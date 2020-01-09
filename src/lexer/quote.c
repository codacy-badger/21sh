/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:05:06 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/09 19:20:11 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		quote(t_lexer *lexer)
{
	int	is_bslash;

	if (quote_start(lexer->str, lexer->i, &lexer->quote))
	{
		if (lexer->curr_tok == NULL)
			lexer->curr_tok = token_new(WORD);
		ft_dstr_add(lexer->curr_tok->value, lexer->str[lexer->i++]);
		return (1);
	}
	is_bslash = (lexer->quote == BSLASH);
	if (quote_stop(lexer->str, lexer->i, &lexer->quote))
	{
		if (is_bslash && lexer->str[lexer->i] == '\n'
				&& lexer->str[lexer->i + 1] == '\0')
		{
			lexer->state |= LINE_CONT;
			ft_dstr_remove(lexer->curr_tok->value,
					lexer->curr_tok->value->len - 1, 1);
			lexer->i++;
			return (1);
		}
		ft_dstr_add(lexer->curr_tok->value, lexer->str[lexer->i++]);
		return (1);
	}
	return (0);
}
