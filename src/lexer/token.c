/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:45:49 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:46:23 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	token_del(void **tok, void *priv)
{
	t_token **token;

	(void)priv;
	token = (t_token **)tok;
	ft_dstr_del((void **)&(*token)->value, NULL);
	ft_memdel((void **)token);
}

t_token	*token_new(int type)
{
	t_token	*token;

	if (!(token = (t_token *)ft_memalloc(sizeof(*token))))
		return (NULL);
	token->value = ft_dstr_new("", 0, 16);
	token->type = type;
	return (token);
}