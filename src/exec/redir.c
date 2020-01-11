/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:52:04 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/07 20:27:57 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**RIGHTS -> S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
*/

#define RIGHTS 420
#define CLOSE  -2
#define HEREDOC -2
#define COMMAND INT32_MAX

static bool	str_is_nbr(const char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

static int	get_flags(int node_type)
{
	if (node_type == GREAT || node_type == GREATAND)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	if (node_type == DGREAT)
		return (O_CREAT | O_WRONLY | O_APPEND);
	if (node_type == LESS || node_type == LESSAND || node_type == DLESS)
		return (O_RDONLY);
	return (COMMAND);
}

static int	get_input_fd(t_node *op_node)
{
	if (op_node->child[0]->data == NULL)
	{
		if (node_token(op_node)->type == LESS
				|| node_token(op_node)->type == LESSAND
				|| node_token(op_node)->type == DLESS)
			return (0);
		else
			return (1);
	}
	else
		return (ft_atoi(node_token(op_node->child[0])->value->str));
}

static int	get_output_fd(t_node *op_node, int flags, t_lexer *lexer)
{
	int	type;

	type = node_token(op_node)->type;
	if (ft_strequ(node_token(op_node->child[1])->value->str, "-"))
	{
		close(get_input_fd(op_node));
		return (CLOSE);
	}
	if (type == DLESS)
	{
		get_and_output_heredoc(lexer, op_node);
		return (HEREDOC);
	}
	if (type == GREATAND || type == LESSAND)
	{
		if (str_is_nbr(node_token(op_node->child[1])->value->str))
			return (ft_atoi(node_token(op_node->child[1])->value->str));
	}
	return (open(node_token(op_node->child[1])->value->str, flags, RIGHTS));
}

int			set_redirections(t_node *cmd, t_lexer *lexer)
{
	int			i;
	int			output_fd;
	int			flags;
	struct stat	buf;

	i = -1;
	while (++i < cmd->nb_children)
	{
		flags = get_flags(node_token(cmd->child[i])->type);
		if (flags == COMMAND)
			continue;
		output_fd = get_output_fd(cmd->child[i], flags, lexer);
		if (output_fd == CLOSE || output_fd == HEREDOC)
			continue;
		if (output_fd == -1)
			return (1);
		if (node_token(cmd->child[i])->type == LESSAND
				&& fstat(output_fd, &buf) == -1)
			return (1);
		dup2(output_fd, get_input_fd(cmd->child[i]));
	}
	return (0);
}
