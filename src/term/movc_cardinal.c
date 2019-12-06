/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movc_cardinal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:59:55 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 15:01:10 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		movcdown(t_term *term)
{
	if (term->cy == term->sizey - 1)
	{
		tputs(term->caps[C_CR], 1, ft_putc);
		tputs(term->caps[C_SF], 1, ft_putc);
	}
	else
	{
		tputs(term->caps[C_DOWN], 1, ft_putc);
		term->cy++;
	}
	return (0);
}

int		movcup(t_term *term)
{
	if (term->cy == 0)
		tputs(term->caps[C_SR], 1, ft_putc);
	else
	{
		tputs(term->caps[C_UP], 1, ft_putc);
		term->cy--;
	}
	return (0);
}

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
