/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movcleft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 16:58:26 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		movcleft(t_term *term)
{
	if (term->cx == 0)
	{
		term->cx = term->sizex - 1;
		if (term->cy > 0)
			term->cy--;
		tputs(tgoto(term->caps[C_CM], term->cx, term->cy), 20, ft_putc);
	}
	else
	{
		tputs(term->caps[C_LEFT], 20, ft_putc);
		term->cx--;
	}
	return (0);
}
