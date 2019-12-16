/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:37:33 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/17 18:40:11 by fratajcz         ###   ########.fr       */
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
		//tokenize(&shell->lexer, &shell->input)) != 0)
		//parse((&shell->lexer)->tokens->next->next);
		//tcsetattr(STDIN_FILENO, TCSAFLUSH, &(shell->term).new_term);

		//printf("|%s|\nlen: %zu, i: %zu\n\r", shell->input.line->str, shell->input.line->len, shell->input.line->i);
	}
	return (0);
}
