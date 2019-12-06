/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_curs_cardinal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:18:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 01:18:56 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		move_curs_down(t_term *term, t_input *input)
{
	int		i;

	i = term->sizex;
	if (input->line->len - input->line->i <= term->sizex - term->cx)
		return (0);
	while (input->line->i < input->line->len && i--)
		move_curs_right(term, input);
	return (0);
}

int		move_curs_left(t_term *term, t_input *input)
{
	ssize_t	csize;
	t_line	*line;

	line = input->line;
	if (line->i > 0)
	{
		csize = getcsize_rev(&line->str[line->i - 1], line->i - 1);
		line->i -= csize;
		movcleft(term);
	}
	return (0);
}

int		move_curs_right(t_term *term, t_input *input)
{
	size_t	csize;

	csize = getcsize(*(int *)&input->line->str[input->line->i]);
	if (input->line->i < input->line->len)
	{
		movcright(term);
		input->line->i += csize;
	}
	return (0);
}

int		move_curs_up(t_term *term, t_input *input)
{
	int		i;

	i = term->sizex;
	if (input->line->i + ft_strlen(input->prompt) < term->sizex)
		return (0);
	while (input->line->i > 0 && i--)
		move_curs_left(term, input);
	return (0);
}
