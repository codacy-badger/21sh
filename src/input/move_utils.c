/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:20:41 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/19 16:53:40 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		cpos_to_prevline(t_input *input)
{
	size_t	pos;
	size_t	offset;

	pos = input->pos;
	offset = 0;
	while (pos && input->line->str[pos - 1] != '\n')
	{
		pos -= ft_charlen_rev(&input->line->str[pos - 1]);
		offset++;
	}
	if (!pos)
		offset += ft_strlen(input->last_prompt);
	decrcpos(input->termp,
	input->termp->sizex - (offset % input->termp->sizex));
	return (0);
}

int		cpos_to_nextline(t_input *input)
{
	size_t	pos;
	size_t	offset;

	pos = input->pos;
	offset = 0;
	while (pos && input->line->str[pos - 1] != '\n')
	{
		pos -= ft_charlen_rev(&input->line->str[pos - 1]);
		offset++;
	}
	if (!pos)
		offset += ft_strlen(input->last_prompt);
	incrcpos(input->termp,
	input->termp->sizex - (offset % input->termp->sizex));
	return (0);
}
