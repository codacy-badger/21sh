/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:32:58 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** init_lexer is called each time we read a line.
** We unset END_OF_INPUT and LINE_CONT
** Then, if the quote status was not reset during
** previous tokenization (because the string wasnt correctly quoted),
** we call get_quote_len to set the number of chars affected by quoting.
*/
int			init_lexer(t_lexer *lexer, t_dstr *line)
{
	lexer->str = line->str;
	lexer->state &= ~(LINE_CONT | END_OF_INPUT);
	if (lexer->quote)
		lexer->quote_len = get_quote_len(lexer->str, lexer->quote);
	return (0);
}