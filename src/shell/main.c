/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:37:33 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:15:03 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		g_last_exit_st = 0;

static int	main_loop(t_sh *shell)
{
	int		ret;

	while (1)
	{
		//reset input, lexer, parser somewhere, but not on first loop
		if ((ret = input_read_line(&shell->term, &shell->input)))
			;//if fatal error break else if line !correct continue
		//if (parse == NO NL)
			//input->pmpt = ps2 continue ;
		//exec
		break ;
	}
	shell_del(shell);
	return (ret);
}

int			main(void)
{
	struct s_sh	shell;

	shell_init(&shell);
	return (main_loop(&shell));
}
