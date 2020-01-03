/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:37:33 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/03 19:21:35 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** If you want to check the leaks, you can uncomment the token_del() line,
** but don't put redirections operators in the input in this case,
** cause I use the previous token to set IO_NUMBER type, so if its deleted, it segfaults.
*/
int		main(int argc, char **argv, char **envp)
{
	struct s_sh	shell;

	(void)argc;
	(void)argv;
	(void)envp;
	init(&shell);
	while (1)
	{
		parse(&shell.lexer, &shell.env, &shell.term);
		if (shell.input.line->len > 1)
		{
			ft_dstr_remove(shell.input.line, shell.input.line->len - 1, 1);
			ft_lstadd(shell.input.head, ft_lstnew(shell.input.line));
		}
		else
			ft_dstr_del((void **)&shell.input.line, NULL);
	}
	return (0);
}
