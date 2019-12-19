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
		draw_prompt(&shell.input);
		readline(&shell.input);
		if (!shell.input.line)
			continue ;
		init_lexer(&shell.lexer, shell.input.line);

		//parsing
		while (eat(&shell.lexer) != END)
		{
			printf("[%d: %s] ->", shell.lexer.curr_tok->type,
			shell.lexer.curr_tok->value->str);
			//token_del((void **)&shell.lexer.curr_tok, NULL);
		}

		//go to readline if needed
		if (shell.lexer.state & LINE_CONT || shell.lexer.quote)
			continue ;

		printf(" END\n");
		//execution
		printf("\nIt will be done, master.\n");
	}
	return (0);
}
