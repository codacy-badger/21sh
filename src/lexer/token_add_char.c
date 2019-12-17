/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:45:49 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:46:23 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** when we arrive here with **str == '\\',
** the BSLASH status is set, we need to add the backslash to the token,
** keep the BSLASH status set for the next char to be escaped, then
** when the next char is added we know we must reset qstatus
*/

int		token_add_char(t_lexer *lexer, char **str)
{
	static bool	esc_reset = false;

	if (esc_reset)
		lexer->qstatus = NONE;
	if (ft_dstr_add(lexer->curr_tok->content, **str) < 0)
		return (-1);
	if (**str == BSLASH)
		esc_reset = true;
	lexer->prev = *(*str)++;
	return (0);
}
