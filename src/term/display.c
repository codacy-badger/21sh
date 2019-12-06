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

size_t	display_char(t_term *term, char *c)
{
	size_t		ret;

	if (*c == '\n')
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

size_t	display_nl(t_term *term)
{
	size_t		ret;

	if ((ret = ft_putc('\n')) == 1)
	{
		term->cx = 0;
		term->cy++;
	}
	return (ret);
}

size_t	display_str(t_term *term, char *s)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		s += display_char(term, s);
		ret++;
	}
	return (ret);
}
