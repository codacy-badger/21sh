/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 09:52:31 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/24 15:32:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <errno.h>

extern int		g_last_exit_st;

#define ERROR "21sh: an error has occured\n"

static void	interrupt_fork(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	g_last_exit_st = 130;
}

int			exec_builtin(char **argv, t_env *env, t_node *cmd, bool free_argv)
{
	if (set_redir(cmd, true) > 0)
	{
		free_arr(argv);
		restore_fds();
		return (1);
	}
	if (ft_strequ(argv[0], "env"))
		builtin_env(argv, env);
	else if (ft_strequ(argv[0], "exit"))
		builtin_exit(argv);
	else if (ft_strequ(argv[0], "unsetenv"))
		builtin_unsetenv(argv, env);
	else if (ft_strequ(argv[0], "setenv"))
		builtin_setenv(argv, env);
	else if (ft_strequ(argv[0], "echo"))
		builtin_echo(argv);
	else if (ft_strequ(argv[0], "cd"))
		builtin_cd(argv, env);
	restore_fds();
	if (free_argv)
		free_arr(argv);
	return (0);
}

int			exec_command_argv(char **argv, t_env *env)
{
	pid_t		pid;
	int			status;

	pid = fork();
	signal(SIGINT, interrupt_fork);
	if (pid == 0)
	{
		if ((execve(argv[0], argv, env->env) == -1))
		{
			perror("21sh");
			exit(g_last_exit_st);
		}
		exit(0);
	}
	wait(&status);
	g_last_exit_st = WIFEXITED(status) ? WEXITSTATUS(status)
		: g_last_exit_st;
	return (g_last_exit_st);
}

int			exec_command(t_node *cmd, t_env *env)
{
	pid_t		pid;
	int			status;
	char		**argv;

	if ((argv = get_argv(cmd, env)) == NULL)
		return (1);
	if (is_builtin(argv[0]))
		return (exec_builtin(argv, env, cmd, true));
	pid = fork();
	signal(SIGINT, interrupt_fork);
	if (pid == 0)
	{
		if (set_redir(cmd, false) > 0)
			exit(1);
		if (execve(argv[0], argv, env->env) == -1)
		{
			perror("21sh");
			exit(g_last_exit_st);
		}
		exit(0);
	}
	free_arr(argv);
	wait(&status);
	g_last_exit_st = WIFEXITED(status) ? WEXITSTATUS(status) : g_last_exit_st;
	return (g_last_exit_st);
}

int			execute(t_node *node, t_env *env)
{
	int			i;

	i = 0;
	if (node == NULL)
		return (1);
	else if (node->data == NULL && expand(node, env) == 0)
		return (exec_command(node, env));
	else if (((t_token *)node->data)->type == PIPE)
		return (exec_pipe(node, env));
	else if (((t_token *)node->data)->type == AND_IF)
	{
		if (execute(node->child[0], env) == 0)
			return (execute(node->child[1], env));
		return (1);
	}
	else if (((t_token *)node->data)->type == OR_IF)
	{
		if (execute(node->child[0], env) != 0)
			return (execute(node->child[1], env));
		return (0);
	}
	while (i < node->nb_children)
		execute(node->child[i++], env);
	return (1);
}
