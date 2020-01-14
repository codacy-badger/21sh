/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:52:04 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/14 17:51:07 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**RIGHTS -> S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
*/

#define RIGHTS 420
#define CLOSE  -2
#define COMMAND INT32_MAX

static int	get_flags(int node_type)
{
	if (node_type == GREAT || node_type == GREATAND)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	if (node_type == DGREAT)
		return (O_CREAT | O_WRONLY | O_APPEND);
	if (node_type == LESS || node_type == LESSAND)
		return (O_RDONLY);
	if (node_type == DLESS)
		return (O_RDWR | O_CREAT);
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

static int	get_output_fd(t_node *op_node, int flags)
{
	int		type;
	int		fd;
	char	*tmp_file;

	type = node_token(op_node)->type;
	if (ft_strequ(node_token(op_node->child[1])->value->str, "-"))
	{
		close(get_input_fd(op_node));
		return (CLOSE);
	}
	if (type == DLESS)
	{
		tmp_file = ft_mktemp(ft_strdup("/tmp/21sh_XXXXXX"));
		fd = open(tmp_file, O_WRONLY);
		ft_putstr_fd(node_token(op_node->child[1])->value->str, fd);
		close(fd);
		fd = open(tmp_file, O_RDONLY);
		return (fd);
	}
	if (type == GREATAND || type == LESSAND)
	{
		if (str_is_nbr(node_token(op_node->child[1])->value->str))
			return (ft_atoi(node_token(op_node->child[1])->value->str));
	}
	return (open(node_token(op_node->child[1])->value->str, flags, RIGHTS));
}

int			set_redirections(t_node *cmd, bool backup)
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
		output_fd = get_output_fd(cmd->child[i], flags);
		if (output_fd == CLOSE)
			continue;
		if (output_fd == -1)
		{
			write(STDERR_FILENO, "21sh: Could not open file.\n", 27);
			return (1);
		}
		if (node_token(cmd->child[i])->type == LESSAND
				&& fstat(output_fd, &buf) == -1)
		{
			write(STDERR_FILENO, "21sh: Bad file descriptor.\n", 27);
			return (1);
		}
		dup2_and_backup(output_fd, get_input_fd(cmd->child[i]), backup);
	}
	return (0);
}
