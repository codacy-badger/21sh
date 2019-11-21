/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:37:33 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/21 20:39:42 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int		g_last_exit_st = 0;

#include <stdio.h>

int		read_line(void)
{
	unsigned int	c;

	c = 0;
	while (c != 10)
	{
		c = 0;
		read(STDIN_FILENO, &c, 4);
		write(1, &c, 4);
	}
	return(0);
}

int		main(void)
{
	struct s_sh		shell;

	init_shell(&shell);
	while (1)
	{
		read_line();
		//parse
		//exec
	}
	return (0);
}
