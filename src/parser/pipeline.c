/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 04:37:16 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/15 15:05:30 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_node	*command(t_list_head **tok_list)
{
	t_node		*command;
	t_node		*redirect;
	t_node		*word;

	command = ft_node_new(NULL);
	while ((redirect = io_redirect(tok_list)) || token(*tok_list)->type == WORD)
	{
		if (redirect != NULL)
			ft_node_add_child(command, redirect);
		else if (token(*tok_list)->type == WORD)
		{
			word = ft_node_new(token(*tok_list));
			ft_node_add_child(command, word);
			(*tok_list) = (*tok_list)->next;
		}
	}
	if (command->nb_children == 0)
		ft_memdel((void *)&command);
	return (command);
}

static t_node	*pipe_list(t_list_head **tok_list, t_node *left_command)
{
	t_node	*left_pipe;
	t_node	*right_command;
	t_node	*right_pipe;

	left_pipe = NULL;
	if (token(*tok_list)->type == PIPE)
	{
		left_pipe = ft_node_new(token(*tok_list));
		(*tok_list) = (*tok_list)->next;
		ft_node_add_child(left_pipe, left_command);
		right_command = command(tok_list);
		right_pipe = pipe_list(tok_list, right_command);
		if (right_pipe != NULL)
			ft_node_add_child(left_pipe, right_pipe);
		else
			ft_node_add_child(left_pipe, right_command);
	}
	return (left_pipe);
}

t_node			*pipeline(t_list_head **tok_list)
{
	t_node *left_command;
	t_node *pipe;

	left_command = command(tok_list);
	pipe = pipe_list(tok_list, left_command);
	if (pipe != NULL)
		return (pipe);
	return (left_command);
}
