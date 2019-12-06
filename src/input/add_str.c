/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:00:01 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 01:02:14 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		line_add_char(t_line *line, unsigned int c)
{
	size_t	olds;
	size_t	news;
	size_t	csize;

	if (!line)
		return (-1);
	csize = getcsize(c);
	if (line->len + csize >= line->size - 1)
	{
		olds = line->len;
		news = line->size * 2;
		if (!(ft_memrealloc((void **)&line->str, olds, news)))
			return (-1);
		line->size = news;
	}
	ft_strinsert(&line->str[line->i], (char *)&c, csize);
	line->len += csize;
	return (0);
}

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

int		line_add_str(t_line *line, char *s)
{
	size_t	olds;
	size_t	news;
	size_t	len;

	if (!line)
		return (-1);
	len = ft_strlen(s);
	while (line->len + len > line->size - 1)
	{
		olds = line->len;
		news = line->size * 2;
		if (!(ft_memrealloc((void **)&line->str, olds, news)))
			return (-1);
		line->size = news;
	}
	ft_strinsert(&line->str[line->i], s, len);
	line->len += len;
	return (0);
}

int		input_add_str(t_term *term, t_input *input, char *s)
{
	size_t	offset;
	size_t	new_i;
	int		len;

	len = ft_strlen(s);
	new_i = input->line->i + len;
	line_add_str(input->line, s);
	offset = display_str(term, &input->line->str[input->line->i]);
	while (offset--)
		movcleft(term);
	while (input->line->i < new_i)
		move_curs_right(term, input);
	return (0);
}

