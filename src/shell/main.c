/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:37:33 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/16 14:19:15 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** If you want to check the leaks, you can uncomment the token_del() line,
** but don't put redirections operators in the input in this case,
** cause I use the previous token to set IO_NUMBER type, so if its deleted, it segfaults.
*/

t_env *g_env;

int		main(int argc, char **argv)
{
	struct s_sh	shell;


  init(&shell, --argc, ++argv);
  g_env = &shell.env;
	while (1)
	{
		parse(&shell.lexer, &shell.env, &shell.term);
	}
	return (0);
}
