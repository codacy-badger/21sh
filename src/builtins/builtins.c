/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:07:29 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/14 13:21:26 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int g_last_exit_st;

void	builtin_exit(char **argv)
{
	int i;

	if (argv[1] == NULL)
	{
		free_arr(argv);
		exit(g_last_exit_st);
	}
	i = 0;
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i++]))
		{
			write(2, "21sh: exit: numeric argument required\n", 38);
			return (free_arr(argv));
		}
	}
	if (argv[2] != NULL)
	{
		write(2, "21sh: exit: too many arguments\n", 31);
		return (free_arr(argv));
	}
	i = ft_atoi(argv[1]);
	exit(i);
}
