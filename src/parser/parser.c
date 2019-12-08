/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:46:45 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 23:35:06 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#define PARSE_ERROR 20

t_token	*token(t_list_head *token_list)
{
	return (token_list->data);
}

t_node	*cmd_name(t_list_head **token_list)
{
	t_node *node;

	node = NULL;
	if (token(*token_list)->type == WORD)
	{
		node = ft_node_new((*token_list)->data);
		(*token_list) = (*token_list)->next;
	}
	return (node);
}

t_node	*command(t_list_head **token_list)
{
	t_node *node;

	node = NULL;
	node = cmd_name(token_list);
	return (node);
}

t_node	*complete_command(t_list_head **token_list)
{
	t_node	*tmp;
	t_node	*node;

	//tmp = list(token_list);
	node = command(token_list);
	if (token(*token_list)->type == SEMI || token(*token_list)->type == AMPERSAND)
	{
		tmp = ft_node_new(token(*token_list));
		ft_node_add_child(node, tmp);
	}
	return (node);
}

int		parse(t_list_head *token_list)
{
	t_node *ast;

	ast = command(&token_list);
	if (ast == NULL)
		return (PARSE_ERROR);
	return (0);
}

int		main(int argc, char *argv[])
{
	t_list_head *token_list;
	t_token		*token;

	token_list = ft_list_first_head(NULL);
	token = malloc(sizeof(t_token));
	token->type = WORD;
	ft_list_add(token, token_list);
	return (0);
}
