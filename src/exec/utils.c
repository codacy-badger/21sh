/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 09:08:47 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/23 19:18:13 by fratajcz         ###   ########.fr       */
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

char			**get_argv(t_node *cmd, t_env *env)
{
	char	**argv;
	char	*cmd_path;

	cmd_path = NULL;
	if ((argv = words_to_array(cmd)) && argv[0] != NULL)
	{
		if (is_builtin(argv[0]))
			return (argv);
		else if ((cmd_path = get_executable_path(argv[0], env)))
		{
			free(argv[0]);
			argv[0] = cmd_path;
			return (argv);
		}
	}
	free_arr(argv);
	set_redir(cmd, true);
	restore_fds();
	return (NULL);
}
