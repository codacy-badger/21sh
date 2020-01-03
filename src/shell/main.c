/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:37:33 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/17 15:36:15 by fratajcz         ###   ########.fr       */
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
		//parsing
		while (eat(&shell.lexer) != 0)
		{
			;
			printf("[%d: %s] -> ", shell.lexer.curr_tok->type,
			shell.lexer.curr_tok->value->str);
			//token_del((void **)&shell.lexer.curr_tok, NULL);
		}
		printf(" END\n");
		
		//store in history
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
