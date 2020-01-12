/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 09:08:47 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/03 15:52:42 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				get_argc(t_node *cmd)
{
	int		argc;
	int		i;

	i = 0;
	argc = 0;
	while (i < cmd->nb_children)
	{
		if (node_token(cmd->child[i])->type == WORD)
			argc++;
		i++;
	}
	return (argc);
}

char			**get_argv(t_node *cmd, t_env *env)
{
	char	**argv;
	char	*cmd_path;
	int		i;
	int		j;

	argv = ft_xmalloc((get_argc(cmd) + 1) * sizeof(char *));
	i = -1;
	j = 0;
	while (++i < cmd->nb_children)
	{
		if (node_token(cmd->child[i])->type == WORD)
			argv[j++] = ft_strdup(node_token(cmd->child[i])->value->str);
	}
	argv[j] = NULL;
	cmd_path = get_executable_path(argv[0], env);
	if (cmd_path == NULL)
	{
		free_arr(argv);
		return (NULL);
	}
	free(argv[0]);
	argv[0] = cmd_path;
	return (argv);
}
