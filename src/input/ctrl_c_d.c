/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:14:22 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/04 16:18:01 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_last_exit_st;

int		ctrl_c(t_input *input)
{
	write(1, "^C\n", 3);
	input->pos = 0;
	ft_dstr_del((void **)&input->line, NULL);
	input->line = ft_dstr_new("", 0, 32);
	return (EOL);
}

int		ctrl_d(t_input *input)
{
	if (input->line->str[0] == '\0')
	{
		write(1, "exit\n", 5);
		exit(g_last_exit_st);
	}
	else
		return (delete(input));
}
