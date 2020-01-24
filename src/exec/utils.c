/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 09:08:47 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/24 15:53:32 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			kill_all_forks(void)
{
	write(2, "21sh: too many processes, aborting\n", 35);
	kill(0, SIGABRT);
}

bool			str_is_nbr(const char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

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

static char		**words_to_array(t_node *cmd)
{
	char	**array;
	int		i;
	int		j;

	i = -1;
	j = 0;
	array = ft_xmalloc((get_argc(cmd) + 1) * sizeof(char *));
	while (++i < cmd->nb_children)
	{
		if (node_token(cmd->child[i])->type == WORD)
			array[j++] = ft_strdup(node_token(cmd->child[i])->value->str);
	}
	array[j] = NULL;
	return (array);
}

t_argv			*get_argv(t_node *cmd, t_env *env)
{
	t_argv	*argv;

	argv = ft_xmalloc(sizeof(t_argv));
	argv->cmd_path = NULL;
	if ((argv->argv = words_to_array(cmd)) && argv->argv[0] != NULL)
	{
		if (is_builtin(argv->argv[0]))
			return (argv);
		if ((argv->cmd_path = get_executable_path(argv->argv[0], env)))
			return (argv);
	}
	free_argv(argv);
	set_redir(cmd, true);
	restore_fds();
	return (NULL);
}
