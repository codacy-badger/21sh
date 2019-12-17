/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:45:49 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:46:23 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
int		token_add(t_lexer *lexer, int type)
{
	lexer->prev_tok = lexer->curr_tok;
	if (!(lexer->curr_tok = token_new(type)))
		return (ALLOC_ERROR); 
	if (type == START || type == END || type == NEWLINE)
		lexer->curr_tok->delimited = true;
	if (!lexer->tokens && !(lexer->tokens = ft_list_first_head(lexer->curr_tok)))
        return (ALLOC_ERROR);
	else
		ft_list_add_tail(lexer->curr_tok, lexer->tokens);
	return (0);
}
*/