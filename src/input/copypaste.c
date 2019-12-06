/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copypaste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:37:34 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 00:41:33 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"

/*
** TODO++: find a key for enter in select mode, set int start & int end,
			highlight the current char (no need to reprint all line),
			increase int end or decrease int start when moving right or left,
			when cut is press, clipboard = strsub(start end)...
*/

int		cp_cut_after(t_term *term, t_input *input)
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
	input_del_nchar(term, input, input->keys[K_DEL], input->line->len - input->line->i);
	line_add_str(input->clipb, cp);
	ft_memdel((void *)&cp);
	return (0);
}

int		cp_cut_before(t_term *term, t_input *input)
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
	input_del_nchar(term, input, input->keys[K_BSP], input->line->i);
	line_add_str(input->clipb, cp);
	ft_memdel((void *)&cp);
	return (0);
}

int		cp_cut_prevw(t_term *term, t_input *input)
{
	char	*cp;
	size_t	size;
	size_t	start;
	size_t	end;

	if (input->prev != input->keys[K_CUTW])
	{
		line_del(&input->clipb);
		if (!(input->clipb = line_new(32)))
			return (-1);
	}
	if (input->line->i == 0)
		return (0);
	end = input->line->i;
	move_curs_prevw(term, input);
	start = input->line->i;
	size = end - start;
	if (!(cp = ft_strsub(input->line->str + start, 0, size)))
		return (-1);
	input_del_nchar(term, input, input->keys[K_DEL], size);
	input->clipb->i = 0;
	line_add_str(input->clipb, cp);
	return (0);
}

int		cp_paste(t_term *term, t_input *input)
{
	if (input->clipb == NULL)
		return (0);
	input_add_str(term, input, input->clipb->str);
	return (0);
}

