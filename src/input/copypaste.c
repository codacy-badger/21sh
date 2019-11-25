/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copypaste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 19:30:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/25 23:52:05 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "libft.h"
#include "shell.h"
#include <curses.h>
#include <term.h>

/*
** TODO: cutting multiple words in a row should add them at the beginning of
** the clipboard
*/

int		cut_previous_word(t_input *input, t_term *term)
{
	int		start;
	int		i;

	if (input->i == 0)
		return (12);
	start = input->i - 1;
	while (start > 0 && ft_iswhitespace(input->line->str[start]))
		start--;
	while (start > 0 && !ft_iswhitespace(input->line->str[start - 1]))
		start--;
	if (input->clipboard != NULL)
		free(input->clipboard);
	input->clipboard = ft_strsub(input->line->str, start, input->i - start);
	input->line->len -= input->i - start;
	ft_strcpy(input->line->str + start, input->line->str + input->i);
	i = input->i - start;
	while (i--)
	{
		move_curs_left(input, term);
		tputs(tgetstr("dc", NULL), 1, ft_putc);
	}
	return (12);
}

int		cut_after(t_input *input)
{
	if (input->line->str[input->i] == '\0')
		return (0);
	if (input->clipboard != NULL)
		free(input->clipboard);
	input->clipboard = ft_strdup(input->line->str + input->i);
	input->line->str[input->i] = '\0';
	input->line->len -= ft_strlen(input->clipboard);
	tputs(tgetstr("ce", NULL), 1, ft_putc);
	return (13);
}

int		cut_before(t_input *input, t_term *term)
{
	int i;

	if (input->i == 0)
		return (13);
	if (input->clipboard != NULL)
		free(input->clipboard);
	input->clipboard = ft_strsub(input->line->str, 0, input->i);
	ft_memmove(input->line->str, input->line->str + input->i,
			input->line->len - input->i);
	input->line->len -= input->i;
	i = input->i;
	while (i--)
	{
		move_curs_left(input, term);
		tputs(tgetstr("dc", NULL), 1, ft_putc);
	}
	input->line->str[input->i] = '\0';
	return (13);
}

int		paste(t_input *input)
{
	unsigned int	new_len;
	unsigned int	new_size;
	unsigned int	clipboard_len;
	char			*line;
	int				i;

	if (input->clipboard == NULL)
		return (14);
	clipboard_len = ft_strlen(input->clipboard);
	new_len = clipboard_len + input->line->len;
	if (new_len > input->line->capacity)
	{
		new_size = ft_next_power_of_two(new_len);
		input->line->str = ft_memrealloc(input->line->str,
				input->line->capacity, new_size);
		input->line->capacity = new_size;
	}
	line = input->line->str;
	ft_memmove(line + input->i + clipboard_len, line + input->i,
			ft_strlen(line + input->i));
	ft_memcpy(line + input->i, input->clipboard, clipboard_len);
	tputs(line + input->i, 1, ft_putc);
	i = input->line->len - input->i;
	input->line->len += clipboard_len;
	input->i += clipboard_len;
	input->x += clipboard_len;
	while (i--)
		tputs(tgetstr("le", NULL), 1, ft_putc);
	return (14);
}
