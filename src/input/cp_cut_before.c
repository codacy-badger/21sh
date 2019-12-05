/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_cut_before.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 19:30:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 16:38:29 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	input_del_nchar(term, input, term->keys[K_BSP], input->line->i);
	line_add_str(input->clipb, cp);
	ft_memdel((void *)&cp);
	return (0);
}