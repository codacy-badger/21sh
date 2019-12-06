/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_curs_special.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:20:41 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 01:21:39 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		move_curs_end(t_term *term, t_input *input)
{
	while (input->line->i < input->line->len)
		move_curs_right(term, input);
	return (0);
}

int		move_curs_home(t_term *term, t_input *input)
{
	while (input->line->i > 0)
		move_curs_left(term, input);
	return (0);
}

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
