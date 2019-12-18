/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 09:52:31 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/18 18:01:50 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <errno.h>

extern int		g_last_exit_st;

#define ERROR "21sh: an error has occured\n"

void	interrupt_fork(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	g_last_exit_st = 130;
}

int		exec_command(t_node *cmd, t_env *env)
{
	pid_t		pid;
	int			status;
	char		**argv;

	if ((argv = get_argv(cmd, env)) == NULL)
		return (1);
	pid = fork();
	signal(SIGINT, interrupt_fork);
	if (pid == 0)
	{
		set_redirections(cmd);
		if ((execve(argv[0], argv, env->env) == -1))
		{
			perror("21sh");
			exit(g_last_exit_st);
		}
		exit(0);
	}
	free_arr(argv);
	wait(&status);
	g_last_exit_st = WIFEXITED(status) ? WEXITSTATUS(status)
		: g_last_exit_st;
	return (0);
}
