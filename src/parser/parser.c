/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:46:45 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/15 04:02:53 by fratajcz         ###   ########.fr       */
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

t_node	*pipe_list(t_list_head **token_list, t_node *left_command)
{
	t_node	*left_pipe;
	t_node	*right_command;
	t_node	*right_pipe;

	left_pipe = NULL;
	if (token(*token_list)->type == PIPE)
	{
		left_pipe = ft_node_new(token(*token_list));
		(*token_list) = (*token_list)->next;
		ft_node_add_child(left_pipe, left_command);
		right_command = command(token_list);
		right_pipe = pipe_list(token_list, right_command);
		if (right_pipe != NULL)
			ft_node_add_child(left_pipe, right_pipe);
		else 
			ft_node_add_child(left_pipe, right_command);
	}
	return (left_pipe);
}

t_node	*pipeline(t_list_head **token_list)
{
	t_node *left_command;
	t_node *pipe;

	left_command = command(token_list);
	pipe = pipe_list(token_list, left_command);
	if (pipe != NULL)
		return (pipe);
	return (left_command);
}

t_node	*and_or(t_list_head **token_list)
{
	return (pipeline(token_list));
}

t_node	*list_next(t_list_head **token_list)
{
	t_node	*node;
	t_node	*tmp;

	node = NULL;
	if (token(*token_list)->type == SEMI)
	{
		node = ft_node_new(token(*token_list));
		(*token_list) = (*token_list)->next;
		ft_node_add_child(node, and_or(token_list));
		tmp = list_next(token_list);
		if (tmp != NULL)
		ft_node_add_child(node->child[0], tmp);
	}
	return (node);
}

t_node	*list(t_list_head **token_list)
{
	t_node *node;
	t_node *tmp;

	node = and_or(token_list);
	tmp = list_next(token_list);
	if (tmp != NULL)
		ft_node_add_child(node, tmp);
	return (node);
}

t_node	*complete_command(t_list_head **token_list)
{
	t_node *node;
	t_node *tmp;

	node = list(token_list);
	if (token(*token_list)->type == SEMI)
	{
		tmp = ft_node_new(token(*token_list));
		ft_node_add_child(node, tmp);
		(*token_list) = (*token_list)->next;
	}
	return (node);
}

void	traverse_ast(t_node *ast)
{
	if (ast == NULL)
		return ;
	printf("children:%d str:%s \n", ast->nb_children, (((t_token *)ast->data)->content->str));
	if (ast->nb_children > 0)
	{
		for (int i = 0; i < ast->nb_children; ++i) {
			
		traverse_ast(ast->child[i]);
		}
	}
}

int		parse(t_list_head *token_list)
{
	t_node *ast;

	ast = complete_command(&token_list);
	if (ast == NULL)
		return (PARSE_ERROR);
//	ast = ast->child[0];
//	printf("%s", (((t_token *)ast->data)->content->str));
	traverse_ast(ast);
	return (0);
}
