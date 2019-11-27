/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_curs_prevw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		move_curs_prevw(t_term *term, t_input *input)
{
	t_line *line;

	line = input->line;
	while (line->i > 0 && ft_iswhitespace(line->str[line->i - 1]))
		move_curs_left(term, input);
	while (line->i > 0 && !ft_iswhitespace(line->str[line->i - 1]))
		move_curs_left(term, input);
	return (0);
}
