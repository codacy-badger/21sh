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

t_token		*token_new(int type)
{
	t_token *token;

	if (!(token = (t_token *)ft_memalloc(sizeof(*token))))
		return (NULL);
	if (!(token->content = ft_dstr_new(1)))
	{
		ft_memdel((void *)&token);
		return (NULL);
	}
	token->delimited = false;
	token->type = type;
	return (token);
}