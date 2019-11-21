/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:37:33 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:28:21 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int		g_last_exit_st = 0;

int		read_line(t_input *input)
{
	unsigned int	c;

	c = 0;
	while (c != 10)
	{
		c = 0;
		read(STDIN_FILENO, &c, 4);
		add_char_to_dstr(&input->line, c);
		write(1, &c, 4); //echo char
	}
	return(0);
}

int		main(void)
{
	struct s_sh		shell;

	init_shell(&shell);
	while (1)
	{
		read_line(&shell.input);
		//parse
		//exec
	}
	return (0);
}
