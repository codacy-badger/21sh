/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 09:08:47 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/15 14:53:24 by fratajcz         ###   ########.fr       */
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

	argv = malloc((get_argc(cmd) + 1) * sizeof(char *));
	if (argv == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < cmd->nb_children)
	{
		if (node_token(cmd->child[i])->type == WORD)
			argv[j++] = ft_strdup(node_token(cmd->child[i])->content->str);
	}
	argv[j] = NULL;
	cmd_path = get_executable_path(argv[0], env);
	free(argv[0]);
	argv[0] = cmd_path;
	return (argv);
}
