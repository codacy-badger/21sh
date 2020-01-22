/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:18:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 01:18:56 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		move_left(t_input *input)
{
	if (input->pos > input->pos_min)
	{
		input->pos -= ft_charlen_rev(&input->line->str[input->pos - 1]);
		if (input->line->str[input->pos] == '\n')
			cpos_to_prevline(input);
		else
			decrcpos(input->termp, 1);
		movcto(input->termp, input->termp->cpos);
	}
	return (0);
}

int		move_right(t_input *input)
{
	if (input->pos < input->line->len)
	{
		if (input->line->str[input->pos] == '\n')
			cpos_to_nextline(input);
		else
			incrcpos(input->termp, 1);
		input->pos += ft_charlen(input->line->str[input->pos]);
		movcto(input->termp, input->termp->cpos);
	}
	return (0);
}
