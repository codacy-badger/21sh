/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 16:53:55 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t	display_char(t_term *term, int c)
{
	size_t		ret;

	if (c == '\n')
		return (display_nl(term));
	if ((ret = ft_putwc(c)) > 0)
	{
		if (term->cx == term->sizex - 1)
		{
			term->cx = 0;
			if (term->cy == term->sizey - 1)
			{
				tputs(term->caps[C_CR], 1, ft_putc);
				tputs(term->caps[C_SF], 1, ft_putc);
			}
			else
				term->cy++;
		}
		else
			term->cx++;
	}
	return (ret);
}
