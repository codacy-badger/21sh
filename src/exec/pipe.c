/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:52:04 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/23 19:47:18 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				g_last_exit_st;

static int		set_pipe_redir(int input_fd, int fildes[2])
{
	if (dup2(fildes[1], 1) == -1 || dup2(input_fd, 0) == -1)
		return (-1);
	close(fildes[1]);
	close(fildes[0]);
	if (input_fd != 0)
		close(input_fd);
	return (0);
}

static int		exec_pipe_cmd(t_node *cmd, t_env *env, int *pid, int input_fd)
{
	char	**argv;
	int		fildes[2];

	argv = get_argv(cmd, env);
	if (pipe(fildes) == -1 || input_fd == -1)
		return (-1);
	*pid = fork();
	if (*pid == -1)
		kill_all_forks();
	if (*pid == 0)
	{
		if (set_pipe_redir(input_fd, fildes) != 0 || set_redir(cmd, false) != 0)
			exit(1);
		if (argv != NULL && is_builtin(argv[0]))
			exec_builtin(argv, env, cmd);
		else if (argv != NULL)
			execve(argv[0], argv, env->env);
		exit(0);
	}
	close(fildes[1]);
	if (input_fd != 0)
		close(input_fd);
	free_arr(argv);
	return (fildes[0]);
}

static void		exec_last_pipe(t_node *cmd, t_env *env, int *pid, int input_fd)
{
	char	**argv;
	int		ret;

	argv = get_argv(cmd, env);
	ret = 0;
	if (input_fd == -1)
		return ;
	*pid = fork();
	if (*pid == -1)
		kill_all_forks();
	if (*pid == 0)
	{
		dup2(input_fd, 0);
		close(input_fd);
		if (set_redir(cmd, false) == 0)
			exit(1);
		if (argv != NULL && is_builtin(argv[0]))
			ret = exec_builtin(argv, env, cmd);
		else if (argv != NULL)
			execve(argv[0], argv, env->env);
	}
	close(input_fd);
	free_arr(argv);
}

static void		exec_pipes(t_node *pipe, t_env *env, int pipe_count)
{
	int			*pid;
	int			*status;
	int			input_fd;
	int			i;

	pid = ft_xmalloc((pipe_count + 1) * sizeof(int *));
	status = ft_xmalloc((pipe_count + 1) * sizeof(int *));
	input_fd = 0;
	i = -1;
	while (++i < pipe_count + 1)
	{
		expand(pipe->child[0], env);
		input_fd = exec_pipe_cmd(pipe->child[0], env, &pid[i], input_fd);
		if (pipe->child[1]->data == NULL)
		{
			expand(pipe->child[1], env);
			exec_last_pipe(pipe->child[1], env, &pid[++i], input_fd);
		}
		pipe = pipe->child[1];
	}
	i = -1;
	while (++i < pipe_count + 1)
		waitpid(pid[i], &status[i], 0);
	exit(WEXITSTATUS(status[i - 1]));
}

int				exec_pipe(t_node *pipe, t_env *env)
{
	int			pid;
	int			pipe_count;
	int			status;
	t_node		*cur;

	pipe_count = 0;
	cur = pipe;
	signal(SIGABRT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGABRT, SIG_DFL);
		while (cur->data != NULL && node_token(cur)->type == PIPE)
		{
			cur = cur->child[1];
			pipe_count++;
		}
		exec_pipes(pipe, env, pipe_count);
	}
	wait(&status);
	signal(SIGABRT, sig_handle);
	if (WIFEXITED(status))
		g_last_exit_st = WEXITSTATUS(status);
	return (g_last_exit_st);
}
