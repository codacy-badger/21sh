/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clear_line(t_term *term, t_input *input)
{
	size_t	plen;

	plen = ft_strlen(*(input->pmpt));
	while (input->line->i)
		move_curs_left(term, input);
	while (plen--)
		movcleft(term);
	tputs(term->caps[C_CD], 1, ft_putc);
	display_str(term, *(input->pmpt));
}
