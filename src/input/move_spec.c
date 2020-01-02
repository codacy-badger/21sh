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
	while (input->pos < input->line->len)
	{
		if (input->line->str[input->pos] == '\n')
			cpos_to_nextline(input);
		else
			incrcpos(input->termp, 1);
		input->pos += ft_charlen(input->line->str[input->pos]);
	}
	movcto(input->termp, input->termp->cpos);
	return (0);
}

int		move_home(t_input *input)
{
	while (input->pos > input->pos_min)
	{
		input->pos -= ft_charlen_rev(&input->line->str[input->pos - 1]);
		if (input->line->str[input->pos] == '\n')
			cpos_to_prevline(input);
		else
			decrcpos(input->termp, 1);
	}
	movcto(input->termp, input->termp->cpos);
	return (0);
}

int		move_nextword(t_input *input)
{
	while (input->pos < input->line->len
	&& !ft_iswhitespace(input->line->str[input->pos]))
	{
		if (input->line->str[input->pos] == '\n')
			cpos_to_nextline(input);
		else
			incrcpos(input->termp, 1);
		input->pos += ft_charlen(input->line->str[input->pos]);
	}
	while (input->pos < input->line->len
	&& ft_iswhitespace(input->line->str[input->pos]))
	{
		if (input->line->str[input->pos] == '\n')
			cpos_to_nextline(input);
		else
			incrcpos(input->termp, 1);
		input->pos += ft_charlen(input->line->str[input->pos]);
	}
	movcto(input->termp, input->termp->cpos);
	return (0);
}

int		move_prevword(t_input *input)
{
	while (input->pos > input->pos_min
	&& ft_iswhitespace(input->line->str[input->pos - 1]))
	{
		input->pos -= ft_charlen_rev(&input->line->str[input->pos - 1]);
		if (input->line->str[input->pos] == '\n')
			cpos_to_prevline(input);
		else
			decrcpos(input->termp, 1);
	}
	while (input->pos > input->pos_min
	&& !ft_iswhitespace(input->line->str[input->pos - 1]))
	{
		input->pos -= ft_charlen_rev(&input->line->str[input->pos - 1]);
		if (input->line->str[input->pos] == '\n')
			cpos_to_prevline(input);
		else
			decrcpos(input->termp, 1);
	}
	movcto(input->termp, input->termp->cpos);
	return (0);
}