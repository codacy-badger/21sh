/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:52:04 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/16 21:10:05 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**RIGHTS -> S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
*/
#define RIGHTS 420

int		set_redirections(t_node *cmd, int stdin_fd, int stdout_fd)
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
