/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:04:10 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 01:05:21 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int		line_del_char(t_line *line)
{
	char	*str;
	size_t	csize;

	if (!line || !(str = line->str))
		return (-1);
	csize = getcsize(str[line->i]);
	ft_strremove(&str[line->i], csize);
	line->len -= csize;
	return (0);
}

int		input_del_char(t_term *term, t_input *input, unsigned long c)
{
	size_t	offset;

	if (input->line->len == 0
		|| (c == input->keys[K_BSP] && input->line->i == 0)
		|| (c == input->keys[K_DEL] && !input->line->str[input->line->i]))
		return (0);
	if (c == input->keys[K_BSP])
		move_curs_left(term, input);
	clear_fromc(term);
	line_del_char(input->line);
	offset = display_str(term, &input->line->str[input->line->i]);
	while (offset--)
		movcleft(term);
	return (0);
}

int		line_del_nchar(t_line *line, int n)
{
	char	*str;

	if (!line || !(str = line->str))
		return (-1);
	ft_strremove(&str[line->i], n);
	line->len -= n;
	return (n);
}

int		input_del_nchar(t_term *term, t_input *input, unsigned long c, int n)
{
	size_t	offset;
	size_t	i;

	i = n;
	if (input->line->len == 0
		|| (c == input->keys[K_BSP] && input->line->i == 0)
		|| (c == input->keys[K_DEL] && !input->line->str[input->line->i]))
		return (0);
	if (c == input->keys[K_BSP])
	{
		while (i--)
			move_curs_left(term, input);
	}
	clear_fromc(term);
	line_del_nchar(input->line, n);
	offset = display_str(term, &input->line->str[input->line->i]);
	while (offset--)
		movcleft(term);
	return (0);
}
