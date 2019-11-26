/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_curs_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:46:27 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		move_curs_up(t_term *term, t_input *input)
{
	size_t	shifty;
	size_t	plen;
	int		i;

	if (input->line->prev)
	{
		i = input->line->i;
		input->line->i = 0;
		input->line = input->line->prev;
		plen = ft_strlen(input->line->prompt);
		shifty = (input->line->len + plen) / (size_t)term->win.ws_col + 1;
		while (shifty--)
		{
			tputs(term->caps.up, 1, ft_putc);
			term->cy--;
		}
		input->line->i = i;
		while (input->line->i > input->line->len)
			move_curs_left(term, input);
	}
	return (0);
}
