/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 04:05:12 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/15 05:52:01 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_node	*filename(t_list_head **token_list)
{
	t_node *node;

	node = NULL;
	//expand filename here ?
	if (token(*token_list)->type == WORD)
	{
		node = ft_node_new(token(*token_list));
		(*token_list) = (*token_list)->next;
	}
	return (node);
}

static t_node	*io_file(t_list_head **token_list, t_token *io_number)
{
	t_node		*node;
	t_node		*tmp;

	node = NULL;
	if (is_operator_redir(token(*token_list)))
	{
		node = ft_node_new(token(*token_list));
		(*token_list) = (*token_list)->next;
		tmp = ft_node_new(io_number);
		ft_node_add_child(node, tmp);
		ft_node_add_child(node, filename(token_list));
	}
	return (node);
}

t_node			*io_redirect(t_list_head **token_list)
{
	if (token(*token_list)->type == IO_NUMBER)
	{
		(*token_list) = (*token_list)->next;
		return (io_file(token_list, token((*token_list)->prev)));
	}
	return (io_file(token_list, NULL));
}
