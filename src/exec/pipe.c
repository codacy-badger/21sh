/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:52:04 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/19 14:26:28 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				g_last_exit_st;

static int		exec_pipe_cmd(t_node *cmd, t_env *env, int *pid,
		int input_fd)
{
	char	**argv;
	int		fildes[2];

	argv = get_argv(cmd, env);
	if (pipe(fildes) == -1)
	{
		write(STDERR_FILENO, "21sh: Failed to create pipe.\n", 29); //
		return (-1);
	}
	*pid = (argv != NULL) ? fork() : -1;
	if (*pid == 0)
	{
		dup2(fildes[1], 1);
		dup2(input_fd, 0);
		close(fildes[1]);
		close(fildes[0]);
		if (input_fd != 0)
			close(input_fd);
		if (set_redirections(cmd, false) == 0)
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
	char **argv;

	argv = get_argv(cmd, env);
	if (argv != NULL)
		*pid = fork();
	else
		*pid = -1;
	if (*pid == 0)
	{
		dup2(input_fd, 0);
		close(input_fd);
		if (set_redirections(cmd, false) == 0)
			execve(argv[0], argv, env->env);
		exit(0);
	}
	close(input_fd);
	free_arr(argv);
}

static void		exec_pipes(t_node *pipe, t_env *env, int pipe_count)
{
	int			*pid;
	int			*status;
	int			i;
	int			input_fd;

	pid = ft_xmalloc((pipe_count + 1) * sizeof(int *));
	status = ft_xmalloc((pipe_count + 1) * sizeof(int *));
	i = -1;
	input_fd = 0;
	while (++i < pipe_count + 1)
	{
		if (pipe->child[1]->data == NULL
		&& (input_fd = exec_pipe_cmd(pipe->child[0], env, &pid[i++], input_fd)) != -1)
			exec_last_pipe(pipe->child[1], env, &pid[i], input_fd);
		else
			input_fd = exec_pipe_cmd(pipe->child[0], env, &pid[i], input_fd);
		pipe = pipe->child[1];
	}
	i = -1;
	while (++i < pipe_count + 1)
		waitpid(pid[i], &status[i], 0);
	exit(WEXITSTATUS(status[i - 1]));
}

static int		get_pipe_count(t_node *pipe)
{
	int			pipe_count;
	t_node		*cur;

	pipe_count = 0;
	cur = pipe;
	while (cur->data != NULL && node_token(cur)->type == PIPE)
	{
		cur = cur->child[1];
		pipe_count++;
	}
	return (pipe_count);
}

int				exec_pipe(t_node *pipe, t_env *env)
{
	int			pid;
	int			pipe_count;
	int			status;

	pid = fork();
	if (pid == 0)
	{
		pipe_count = get_pipe_count(pipe);
		exec_pipes(pipe, env, pipe_count);
	}
	wait(&status);
	if (WIFEXITED(status))
		g_last_exit_st = WEXITSTATUS(status);
	return (g_last_exit_st);
}
