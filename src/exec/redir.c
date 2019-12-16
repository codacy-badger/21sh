/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:52:04 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/16 21:07:51 by fratajcz         ###   ########.fr       */
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

int		exec_pipe_cmd(t_node *cmd, t_env *env, int *pid, int input_fd)
{
	char	**argv;
	int		fildes[2];

	argv = get_argv(cmd, env);
	pipe(fildes);
	*pid = fork();
	if (*pid == 0)
	{
		dup2(fildes[1], 1);
		dup2(input_fd, 0);
		close(fildes[1]);
		close(fildes[0]);
		if (input_fd != 0)
			close(input_fd);
		execve(argv[0], argv, env->env);
	}
	close(fildes[1]);
	if (input_fd != 0)
		close(input_fd);
	free_arr(argv);
	return (fildes[0]);
}

int			exec_last_pipe(t_node *cmd, t_env *env, int *pid, int input_fd)
{
	char **argv;

	argv = get_argv(cmd, env);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		dup2(input_fd, 0);
		close(input_fd);
		execve(argv[0], argv, env->env);
	}
	close(input_fd);
	free_arr(argv);
}

int			exec_pipes(t_node *pipe, t_env *env, int pipe_count)
{
	int			*pid;
	int			*status;
	int			i;
	int			input_fd;

	pid = malloc((pipe_count + 1) * sizeof(int *));
	status = malloc((pipe_count + 1) * sizeof(int *));
	i = -1;
	input_fd = 0;
	while (+=i < pipe_count + 1)
	{
		if (pipe->child[1]->data == NULL)
		{
			input_fd = exec_pipe_cmd(pipe->child[0], env, &pid[i++], input_fd);
			exec_last_pipe(pipe->child[1], env, &pid[i], input_fd);
		}
		else
			input_fd = exec_pipe_cmd(pipe->child[0], env, &pid[i], input_fd);
		pipe = pipe->child[1];
	}
	i = -1;
	while (++i < pipe_count + 1)
		waitpid(pid[i], &status[i], 0);
	free(pid);
	free(status);
}

int		get_pipe_count(t_node *pipe)
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

int				exec_pipe(t_node *pipe, t_env *env, int input_fd)
{
	int			pid;
	int			pipe_count;

	pid = fork();
	if (pid == 0)
	{
		pipe_count = get_pipe_count(pipe);
		exec_pipes(pipe, env, pipe_count);
	}
	wait(NULL);
}
