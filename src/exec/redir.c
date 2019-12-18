/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:52:04 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/18 16:21:53 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**RIGHTS -> S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
*/
#define RIGHTS 420

char	*redir_output(t_node *op_node)
{
	return (node_token(op_node->child[1])->content->str);
}

int		set_redirections(t_node *cmd)
{
	int		i;
	int		fd;
	char	*str;

	i = 0;
	while (i < cmd->nb_children)
	{
		str = node_token(cmd->child[i])->content->str;
		if (ft_strequ(str, ">"))
		{
			fd = open(redir_output(cmd->child[i]), O_CREAT | O_WRONLY, RIGHTS);
			dup2(fd, 1);
		}
		else if (ft_strequ(str, ">>"))
		{
			fd = open(redir_output(cmd->child[i]), O_CREAT | O_WRONLY | O_APPEND
					, RIGHTS);
			dup2(fd, 1);
		}
		else if (ft_strequ(str, "<"))
		{
			fd = open(redir_output(cmd->child[i]), O_RDONLY, RIGHTS);
			dup2(fd, 0);
		}
		//else if (ft_strequ(str, ""))
		i++;
	}
	return (0);
}
