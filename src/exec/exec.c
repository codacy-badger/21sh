/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 09:52:31 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/15 15:01:48 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int		g_last_exit_st;

#define ERROR "21sh: an error has occured\n"

void	interrupt_fork(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	g_last_exit_st = 130;
}

void	exec_in_shell(char **argv, t_env *env)
{
	pid_t	pid;
	int		status;
	char	**new_argv;
	int		i;

	i = 0;
	while (argv[i])
		i++;
	new_argv = malloc((i + 2) * sizeof(char *));
	new_argv[0] = ft_strdup("/bin/sh");
	i = 0;
	while (argv[++i - 1])
		new_argv[i] = argv[i - 1];
	new_argv[i] = NULL;
	pid = fork();
	if (pid == 0)
	{
		if (execve(new_argv[0], new_argv, env->env) == -1)
			write(2, ERROR, 28);
		exit(0);
	}
	wait(&status);
	g_last_exit_st = WIFEXITED(status) ? WEXITSTATUS(status) : g_last_exit_st;
	free(new_argv[0]);
	free(new_argv);
}

int		exec_command(char **argv, t_env *env)
{
	pid_t		pid;
	int			status;

	if (argv && argv[0] != NULL)
	{
		pid = fork();
		signal(SIGINT, interrupt_fork);
		if (pid == 0)
		{
			if ((execve(argv[0], argv, env->env) == -1))
			{
				exec_in_shell(argv, env);
				exit(g_last_exit_st);
			}
			exit(0);
		}
		free(argv[0]);
		wait(&status);
		g_last_exit_st = WIFEXITED(status) ? WEXITSTATUS(status)
		: g_last_exit_st;
	}
	return (0);
}

int		exec_with_io(t_node *cmd, t_env *env, int stdin_fd, int stdout_fd)
{
	pid_t		pid;
	int			status;
	char		**argv;

	argv = get_argv(cmd, env);
	if (argv && argv[0] != NULL)
	{
		pid = fork();
		signal(SIGINT, interrupt_fork);
		if (pid == 0)
		{
			set_redirections(cmd, stdin_fd, stdout_fd);
			if ((execve(argv[0], argv, env->env) == -1))
			{
				exec_in_shell(argv, env);
				exit(g_last_exit_st);
			}
			exit(0);
		}
		free(argv[0]);
		wait(&status);
		g_last_exit_st = WIFEXITED(status) ? WEXITSTATUS(status)
		: g_last_exit_st;
	}
	return (0);
}
