/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:20:41 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 01:21:39 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		move_end(t_input *input)
{
	size_t	offset;

	offset = 0;
	while (input->pos < input->line->len)
	{
		input->pos += ft_charlen(input->line->str[input->pos]);
		offset++;
	}
	movcto(input->termp, input->termp->cpos + offset);
	return (0);
}

int		move_home(t_input *input)
{
	size_t	offset;

	offset = 0;
	while (input->pos > input->pos_min)
	{
		input->pos -= ft_charlen_rev(&input->line->str[input->pos - 1]);
		offset++;
	}
	movcto(input->termp, input->termp->cpos - offset);
	return (0);
}

int		move_nextword(t_input *input)
{
	size_t	offset;

	offset = 0;
	while (input->pos < input->line->len
	&& !ft_iswhitespace(input->line->str[input->pos]))
	{
		input->pos += ft_charlen(input->line->str[input->pos]);
		offset++;
	}
	while (input->pos < input->line->len
	&& ft_iswhitespace(input->line->str[input->pos]))
	{
		input->pos += ft_charlen(input->line->str[input->pos]);
		offset++;
	}
	movcto(input->termp, input->termp->cpos + offset);
	return (0);
}

int		move_prevword(t_input *input)
{
	size_t	offset;

	offset = 0;
	while (input->pos > input->pos_min
	&& ft_iswhitespace(input->line->str[input->pos - 1]))
	{
		input->pos -= ft_charlen_rev(&input->line->str[input->pos - 1]);
		offset++;
	}
	while (input->pos > input->pos_min
	&& !ft_iswhitespace(input->line->str[input->pos - 1]))
	{
		input->pos -= ft_charlen_rev(&input->line->str[input->pos - 1]);
		offset++;
	}
	movcto(input->termp, input->termp->cpos - offset);
	return (0);
}