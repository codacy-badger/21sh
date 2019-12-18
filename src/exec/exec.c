/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 09:52:31 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/18 11:38:33 by fratajcz         ###   ########.fr       */
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
				perror("21sh");
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
