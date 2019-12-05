/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_del_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 15:38:19 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		input_del_char(t_term *term, t_input *input, int c)
{
	size_t	offset;

	if (input->line->len == 0
		|| (c == (int)term->keys[K_BSP] && input->line->i == 0)
		|| (c == (int)term->keys[K_DEL] && !input->line->str[input->line->i]))
		return (0);
	if (c == (int)term->keys[K_BSP])
		move_curs_left(term, input);
	clear_fromc(term);
	line_del_char(input->line);
	offset = display_str(term, &input->line->str[input->line->i]);
	while (offset--)
		movcleft(term);
	return (0);
}
