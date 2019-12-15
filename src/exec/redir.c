/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:52:04 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/15 15:25:25 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**#define RIGHTS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
*/
#define RIGHTS 420


int				set_redirections(t_node *cmd, int stdin_fd, int stdout_fd)
{
	int i;
	int	fd;

	i = 0;
	dup2(stdin_fd, 0);
	dup2(stdout_fd, 1);
	while (i < cmd->nb_children)
	{
		if (ft_strequ(node_token(cmd->child[i])->content->str, ">"))
		{
			fd = open(node_token(cmd->child[i]->child[1])->content->str,
					O_CREAT | O_WRONLY, RIGHTS);
			dup2(fd, 1);
		}
		else if (ft_strequ(node_token(cmd->child[i])->content->str, ">>"))
		{
			fd = open(node_token(cmd->child[i]->child[1])->content->str,
					O_CREAT | O_WRONLY | O_APPEND, RIGHTS);
			dup2(fd, 1);
		}
		else if (ft_strequ(node_token(cmd->child[i])->content->str, "<"))
		{
			fd = open(node_token(cmd->child[i]->child[1])->content->str,
					 O_RDONLY, RIGHTS);
			dup2(fd, 0);
		}
		i++;
	}
	return (0);
}

int				exec_pipe(t_node *ast, t_env *env, int input_fd)
{
	int		fildes[2];

	pipe(fildes);
	exec_with_io(ast->child[0], env, input_fd, fildes[1]);
	close(fildes[1]);
	if (ast->child[1]->data == NULL)
		exec_with_io(ast->child[1], env, fildes[0], 1);
	else
		exec_pipe(ast->child[1], env, fildes[0]);
	close(fildes[0]);
	return (0);
}
