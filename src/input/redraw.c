/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 20:33:11 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 20:40:33 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	redraw(t_term *term, t_input *input)
{
	int		i;

	tputs(tgetstr("cl", NULL), 1, ft_putc);
	display_str(term, *(input->pmpt));
	display_str(term, input->line->str);
	i = input->line->len - input->line->i;
	while (i--)
		movcleft(term);
}
