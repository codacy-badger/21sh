/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movcright.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:08:30 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		movcright(t_term *term)
{
	if (term->cx == term->sizex - 1)
	{
		term->cx = 0;
		term->cy++;
		tputs(tgoto(term->caps[C_CM], term->cx, term->cy), 20, ft_putc);
	}
	else
	{
		tputs(term->caps[C_RIGHT], 20, ft_putc);
		term->cx++;
	}
	return (0);
}
