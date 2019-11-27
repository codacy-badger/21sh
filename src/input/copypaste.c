/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copypaste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 19:30:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 15:40:30 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** TODO: cutting multiple words in a row should add them at the beginning of
** the clipboard
*/

int		cut_previous_word(t_term *term, t_input *input)
{
	int		start;
	int		i;

	if (input->line->i == 0)
		return (12);
	start = input->line->i - 1;
	while (start > 0 && ft_iswhitespace(input->line->str[start]))
		start--;
	while (start > 0 && !ft_iswhitespace(input->line->str[start - 1]))
		start--;
	if (input->clipboard != NULL)
		free(input->clipboard);
	input->clipboard = ft_strsub(input->line->str, start,
			input->line->i - start);
	input->line->len -= input->line->i - start;
	ft_strcpy(input->line->str + start, input->line->str + input->line->i);
	i = input->line->i - start;
	while (i--)
	{
		move_curs_left(term, input);
		tputs(tgetstr("dc", NULL), 1, ft_putc);
	}
	return (12);
}

int		cut_after(t_input *input)
{
	if (input->line->str[input->line->i] == '\0')
		return (0);
	if (input->clipboard != NULL)
		free(input->clipboard);
	input->clipboard = ft_strdup(input->line->str + input->line->i);
	input->line->str[input->line->i] = '\0';
	input->line->len -= ft_strlen(input->clipboard);
	tputs(tgetstr("ce", NULL), 1, ft_putc);
	return (13);
}

int		cut_before(t_term *term, t_input *input)
{
	int i;

	if (input->line->i == 0)
		return (13);
	if (input->clipboard != NULL)
		free(input->clipboard);
	input->clipboard = ft_strsub(input->line->str, 0, input->line->i);
	ft_memmove(input->line->str, input->line->str + input->line->i,
			input->line->len - input->line->i);
	input->line->len -= input->line->i;
	i = input->line->i;
	while (i--)
	{
		move_curs_left(term, input);
		tputs(tgetstr("dc", NULL), 1, ft_putc);
	}
	input->line->str[input->line->i] = '\0';
	return (13);
}

int		paste(t_term *term, t_input *input)
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
	if (new_len > input->line->size)
	{
		new_size = ft_next_power_of_two(new_len);
		input->line->str = ft_memrealloc(input->line->str,
				input->line->size, new_size);
		input->line->size = new_size;
	}
	line = input->line->str;
	ft_memmove(line + input->line->i + clipboard_len, line + input->line->i,
			ft_strlen(line + input->line->i));
	ft_memcpy(line + input->line->i, input->clipboard, clipboard_len);
	display_str(term, line + input->line->i);
	input->line->len += clipboard_len;
	input->line->i += clipboard_len;
	return (14);
}
