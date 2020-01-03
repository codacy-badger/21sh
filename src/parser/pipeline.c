/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 04:37:16 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/03 15:39:25 by fratajcz         ###   ########.fr       */
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

static t_node	*command(t_lexer *lexer)
{
	t_node		*command;
	t_node		*redirect;
	t_node		*word;

	if (lexer->curr_tok == NULL)
		return (NULL);
	command = ft_node_new(NULL);
	while ((redirect = io_redirect(lexer)) || (lexer->curr_tok && lexer->curr_tok->type == WORD))
	{
		if (redirect != NULL)
			ft_node_add_child(command, redirect);
		else if (lexer->curr_tok->type == WORD)
		{
			word = ft_node_new(lexer->curr_tok);
			ft_node_add_child(command, word);
			eat(lexer);
			//(*tok_list) = (*tok_list)->next;
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

static t_node	*pipe_list(t_lexer *lexer, t_node *left_command)
{
	t_node	*left_pipe;
	t_node	*right_command;
	t_node	*right_pipe;

	if (lexer->curr_tok == NULL)
		return (NULL);
	left_pipe = NULL;
	if (lexer->curr_tok->type == PIPE)
	{
		left_pipe = ft_node_new(lexer->curr_tok);
		//(*tok_list) = (*tok_list)->next;
		eat(lexer);
		ft_node_add_child(left_pipe, left_command);
		right_command = command(lexer);
		right_pipe = pipe_list(lexer, right_command);
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

t_node			*pipeline(t_lexer *lexer)
{
	t_node *left_command;
	t_node *pipe;

	left_command = command(lexer);
	pipe = pipe_list(lexer, left_command);
	if (pipe != NULL)
		return (pipe);
	return (left_command);
}
