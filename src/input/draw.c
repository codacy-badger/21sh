/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 20:33:11 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/09 13:59:33 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int		draw_prompt(t_input *input)
{
	getcpos(input->termp);
	if (input->line_cont)
		printstr(input->termp, "> ");
	else
		printstr(input->termp, "$> ");
	return (0);
}

int		redraw(t_input *input)
{
	tputs(input->termp->caps[C_CL], 1, ft_putc);
	input->termp->cpos = 0;
	draw_prompt(input);
	printstr(input->termp, input->line->str);
	input->pos = input->line->len;
	return (0);
}
