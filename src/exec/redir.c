/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:52:04 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/15 13:41:02 by fratajcz         ###   ########.fr       */
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

static int	set_redir(t_node *op_node, bool backup)
{
	int		flags;
	int		output_fd;
	int		input_fd;
	int		type;

	type = node_token(op_node)->type;
	flags = get_flags(type);
	if (flags == COMMAND)
		return (0);
	output_fd = get_output_fd(op_node, flags);
	if (output_fd == CLOSE)
		return (0);
	if (output_fd == -1)
		return (write(STDERR_FILENO, "21sh: Could not open file\n", 26));
	if ((type == LESSAND || type == GREATAND) && !is_valid_fd(output_fd))
		return (write(STDERR_FILENO, "21sh: Bad file descriptor\n", 26));
	input_fd = get_input_fd(op_node);
	if (input_fd > 255)
		return (write(STDERR_FILENO, "21sh: Bad file descriptor\n", 26));
	dup2_and_backup(output_fd, input_fd, backup);
	if (output_fd != input_fd)
		close(output_fd);
	return (0);
}

int			set_redirections(t_node *cmd, bool backup)
{
	int			i;

	i = 0;
	while (i < cmd->nb_children)
	{
		if (set_redir(cmd->child[i], backup) > 0)
			return (1);
		i++;
	}
	return (0);
}
