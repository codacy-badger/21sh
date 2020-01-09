/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:05:06 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/09 13:14:27 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		backslash(t_lexer *lexer)
{
	if (lexer->quote != SQUOTE && lexer->str[lexer->i] == '\\'
			&& lexer->str[lexer->i + 1] == '\n')
	{
		lexer->i += 2;
		return (1);
	}
	return (0);
}

int		quote(t_lexer *lexer)
{
	if (is_quote_start(lexer->str, lexer->i, lexer->quote))
	{
		lexer->quote = lexer->str[lexer->i];
		lexer->i++;
		return (1);
	}
	if (is_quote_stop(lexer->str, lexer->i, lexer->quote))
	{
		lexer->quote = NONE;
		lexer->i++;
		return (1);
	}
	return (0);
}
