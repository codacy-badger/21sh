/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_curs_nextw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		move_curs_nextw(t_term *term, t_input *input)
{
	t_line	*line;

	line = input->line;
	while (line->str[line->i] && !ft_iswhitespace(line->str[line->i]))
		move_curs_right(term, input);
	while (line->str[line->i] && ft_iswhitespace(line->str[line->i]))
		move_curs_right(term, input);
	return (0);
}
