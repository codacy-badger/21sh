/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 20:33:11 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 00:29:44 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int		prompt(t_input *input)
{
	//a shell in the shell
	printstr(input->termp, "$> ");
	return (0);
}

int		redraw(t_input *input)
{
	tputs(input->termp->caps[C_CL], 1, ft_putc);
	input->termp->cpos = 0;
	prompt(input);
	printstr(input->termp, input->line->str);
	input->pos = input->line->len;
	return (0);
}
