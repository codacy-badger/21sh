/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movcleft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:37:47 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		movcleft(t_term *term)
{
	int offset;

	if (term->cx == 0)
	{
		term->cx = term->sizex - 1;
		term->cy--;
		tputs(tgoto(term->caps[C_CM], term->cx, term->cy), 1, ft_putc);
	}
	else
	{
		tputs(term->caps[C_LEFT], 1, ft_putc);
		term->cx--;
	}
	return (0);
}
