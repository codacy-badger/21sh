/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:45:49 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:46:23 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		add_token(t_lexer *lexer, int type)
{
	lexer->prev_tok = lexer->curr_tok;
	if (!(lexer->curr_tok = token_new(type)))
		return (ALLOC_ERROR);
	ft_list_add_tail(lexer->curr_tok, lexer->tokens);
	return (0);
}

t_token	*token_new(int type)
{
	t_token *token;

	if (!(token = (t_token *)ft_memalloc(sizeof(*token))))
		return (NULL);
	if (!(token->content = ft_dstr_new(1)))
	{
		ft_memdel((void *)&token);
		return (NULL);
	}
	token->is_delim = 0;
	token->type = type;
	return (token);
}
