/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delchar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 16:53:55 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		delete(t_input *input)
{
	size_t	offset;

	if (input->line->str[input->pos])
	{
		clearfromc(input->termp);
		ft_dstr_remove(input->line, input->pos,
							ft_charlen(input->line->str[input->pos]));
		offset = printstr(input->termp, &input->line->str[input->pos]);
		movcto(input->termp, input->termp->cpos - offset);
	}
	else
		tputs(input->termp->caps[C_BL], 1, ft_putc);
	return (0);
}

int		backspace(t_input *input)
{
	size_t	offset;

	if (input->pos > input->pos_min)
	{
		move_left(input);
		clearfromc(input->termp);
		ft_dstr_remove(input->line, input->pos,
							ft_charlen(input->line->str[input->pos]));
		offset = printstr(input->termp, &input->line->str[input->pos]);
		movcto(input->termp, input->termp->cpos - offset);
	}
	else
		tputs(input->termp->caps[C_BL], 1, ft_putc);
	return (0);
}
