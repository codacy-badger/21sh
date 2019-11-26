/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_curs_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:46:27 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		move_curs_left(t_term *term, t_input *input)
{
	int		shift;

	if (input->line->i > 0)
	{
		if (term->cx == 0)
		{
			tputs(term->caps.up, 1, ft_putc);
			shift = term->win.ws_col - 2;
			while (shift--)
				tputs(term->caps.nd, 1, ft_putc);
			term->cx = term->win.ws_col - 2;
			term->cy--;
		}
		else
		{
			tputs(term->caps.le, 1, ft_putc);
			term->cx--;
		}
		input->line->i--;
	}
	return (0);
}
