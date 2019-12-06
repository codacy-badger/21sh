/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 20:33:11 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 00:29:44 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int		redraw(t_term *term, t_input *input)
{
	int		i;

	tputs(term->caps[C_CL], 1, ft_putc);
	display_str(term, input->prompt);
	display_str(term, input->line->str);
	i = input->line->len - input->line->i;
	while (i--)
		movcleft(term);
	return (1);
}
