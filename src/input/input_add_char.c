/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_add_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 15:38:19 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		input_add_char(t_term *term, t_input *input, unsigned int c)
{
	size_t		offset;

	line_add_char(input->line, c);
	offset = display_str(term, &input->line->str[input->line->i]);
	while (offset--)
		movcleft(term);
	move_curs_right(term, input);
	return (0);
}
