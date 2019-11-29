/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copypaste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 19:30:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 16:38:29 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** TODO: not add word if cursor has been moved

** TODO++: find a key for enter in select mode, set int start & int end,
			highlight the current char (no need to reprint all line),
			increase int end or decrease int start when moving right or left,
			when cut is press, clipboard = strsub(start end)...
*/

int		paste(t_term *term, t_input *input)
{
	t_line	*cb;

	cb = input->clipb;
	if (input->clipb == NULL)
		return (0);
	while (cb)
	{
		input_add_str(term, input, cb->str);
		cb = cb->next;
	}
	return (0);
}

int		cut_nextw(t_term *term, t_input *input)
{
	char	*cp;
	size_t	size;
	size_t	start;
	size_t	end;
	t_line	*new;

	if (input->line->i == 0)
		return (0);
	start = input->line->i;
	move_curs_nextw(term, input);
	end = input->line->i;
	size = end - start;
	if (!(new = line_new(32)))
		return (-1);
	if (!(cp = ft_strsub(input->line->str + start, 0, size)))
		return (-1);
	input_del_nchar(term, input, term->keys[K_BSP], size);
	line_add_str(new, cp);
	line_add(&input->clipb, new, 1);
	return (0);
}

int		cut_prevw(t_term *term, t_input *input)
{
	char	*cp;
	size_t	size;
	size_t	start;
	size_t	end;
	t_line	*new;

	if (input->line->i == 0)
		return (0);
	end = input->line->i;
	move_curs_prevw(term, input);
	start = input->line->i;
	size = end - start;
	if (!(new = line_new(32)))
		return (-1);
	if (!(cp = ft_strsub(input->line->str + start, 0, size)))
		return (-1);
	input_del_nchar(term, input, term->keys[K_DEL], size);
	line_add_str(new, cp);
	line_add(&input->clipb, new, 1);
	return (0);
}

int		cut_after(t_term *term, t_input *input)
{
	char	*cp;

	if (input->line->str[input->line->i] == '\0')
		return (0);
	if (input->clipb != NULL)
	{
		line_del(&input->clipb);
		if (!(input->clipb = line_new(32)))
			return (-1);
	}
	if (!(cp = ft_strdup(input->line->str + input->line->i)))
		return (-1);
	input_del_nchar(term, input, term->keys[K_DEL], input->line->len - input->line->i);
	line_add_str(input->clipb, cp);
	ft_memdel((void *)&cp);
	return (0);
}

int		cut_before(t_term *term, t_input *input)
{
	char	*cp;

	if (input->line->i == 0)
		return (0);
	if (input->clipb != NULL)
	{
		line_del(&input->clipb);
		if (!(input->clipb = line_new(32)))
			return (-1);
	}
	if (!(cp = ft_strsub(input->line->str, 0, input->line->i)))
		return (-1);
	input_del_nchar(term, input, term->keys[K_BSP], input->line->i);
	line_add_str(input->clipb, cp);
	ft_memdel((void *)&cp);
	return (0);
}
