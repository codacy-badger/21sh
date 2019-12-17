/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delchar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 16:53:55 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		delete(t_input *input)
{
	ssize_t	charlen;
	size_t 	nprint;

	if (input->line->str[input->pos])
	{
		charlen = ft_charlen(input->line->str[input->pos]);
		ft_dstr_remove(input->line, input->pos, charlen);
		nprint = printstr(input->termp, &input->line->str[input->pos]);
		nprint += printstr(input->termp, " ");
		movcto(input->termp, input->termp->cpos - nprint);
	}
	else
		tputs(input->termp->caps[C_BL], 1, ft_putc);
	return (0);
}

int		backspace(t_input *input)
{
	ssize_t	charlen;
	size_t 	nprint;

	if (input->pos > 0)
	{
		charlen = ft_charlen_rev(&input->line->str[input->pos - 1]);
		input->pos -= charlen;
		ft_dstr_remove(input->line, input->pos, charlen);
		movcleft(input->termp);
		nprint = printstr(input->termp, &input->line->str[input->pos]);
		nprint += printstr(input->termp, " ");
		movcto(input->termp, input->termp->cpos - nprint);
	}
	else
		tputs(input->termp->caps[C_BL], 1, ft_putc);
	return (0);
}