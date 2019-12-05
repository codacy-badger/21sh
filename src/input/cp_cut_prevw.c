/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_cut_prevw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 19:30:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 16:38:29 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		cp_cut_prevw(t_term *term, t_input *input)
{
	char	*cp;
	size_t	size;
	size_t	start;
	size_t	end;
	t_line	*new;

	if (input->prev != term->keys[K_CUTW])
		line_del(&input->clipb);
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