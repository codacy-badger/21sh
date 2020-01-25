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

void	movcleft(t_term *term)
{
	decrcpos(term, 1);
	tputs(tgoto(term->caps[C_CM], term->cpos % term->sizex,
				term->cpos / term->sizex), 20, ft_putc);
}

void	movcright(t_term *term)
{
	incrcpos(term, 1);
	tputs(tgoto(term->caps[C_CM], term->cpos % term->sizex,
				term->cpos / term->sizex), 20, ft_putc);
}

void	movcto(t_term *term, size_t pos)
{
	setcpos(term, pos);
	tputs(tgoto(term->caps[C_CM], term->cpos % term->sizex,
				term->cpos / term->sizex), 20, ft_putc);
}

void	movcnl(t_term *term)
{
	incrcpos(term, term->sizex - term->cpos % term->sizex);
	tputs(term->caps[C_SF], 1, ft_putc);
	tputs(term->caps[C_CR], 1, ft_putc);
}
