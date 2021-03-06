/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:14:22 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/13 18:51:42 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_last_exit_st;
extern int	g_parse_error;

int		ctrl_c(t_input *input)
{
	write(1, "^C\n", 3);
	input->pos = 0;
	input->pos_min = 0;
	free(input->line->str);
	input->line->str = NULL;
	input->multiline = false;
	input->curr = input->head;
	g_parse_error = SILENT_ABORT;
	reset_lexer(NULL);
	return (EOL);
}

int		ctrl_d(t_input *input)
{
	if (input->line->str[0] == '\0' && input->first_line)
	{
		write(1, "exit\n", 5);
		reset_term(NULL);
		exit(g_last_exit_st);
	}
	else
		return (delete(input));
}
