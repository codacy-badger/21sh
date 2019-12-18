/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:37:33 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/18 11:30:04 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		main(void)
{
	struct s_sh	shell;

	init(&shell);
	while (1)
	{
		draw_prompt(&shell.input);
		readline(&shell.input);
		tokenize(&shell.lexer, &shell.input);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell.term.oldterm);
		parse((&shell.lexer)->tokens->next->next, &shell.env);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell.term.newterm);
		//printf("|%s|\nlen: %zu, i: %zu\n\r", shell->input.line->str, shell->input.line->len, shell->input.line->i);
	}
	return (0);
}
