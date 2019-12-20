/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:45:49 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:46:23 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		get_token_type(t_lexer *lexer)
{
	if (!lexer->curr_tok)
		return (END);
	if (is_operator_start(*lexer->curr_tok->value->str))
	{
		lexer->curr_tok->type = get_operator_type(lexer->curr_tok->value->str);
		if (is_redir(lexer->curr_tok) && !ft_iswhitespace(lexer->oldsep)
		&& ft_strisnbr(lexer->prev_tok->value->str))
			lexer->prev_tok->type = IO_NUMBER;
	}
	return (lexer->curr_tok->type);
}