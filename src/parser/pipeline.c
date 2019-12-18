/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 04:37:16 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/18 18:37:55 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	returns commands in this format:	
**	
**	ls -l 2 > test -a -f
**
**                                 NULL
**                          /   /   |   \   \
**                         ls  -l   >   -a  -f
**                                 / \
**                                2   test
*/

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

/*
** pipe_list        : '|' command pipe_list
**                  | EMPTY
**                  ;
*/

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

/*
**	pipeline         : command pipe_list
**	returns pipes in this format :
**	ex:           ls | cat | wc:
**	
**
**						"|"
**                     /   \
**                    ls   "|"
**                        /   \
**                      cat    wc
**	(commands are actually stored with a NULL node whose children contain the 
**	words, see above)
*/

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
