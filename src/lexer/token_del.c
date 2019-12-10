/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:45:49 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:46:23 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	token_del(void *tok, void *priv)
{
	t_token	*token;

	(void)priv;
	token = (t_token *)tok;
	ft_memdel((void *)&token->content->str);
	ft_memdel((void *)&token->content);
	ft_memdel((void *)&tok);
}