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

/*
** Move the cursor in different positions, and update term->cpos
*/
void	movcleft(t_term *term)
{
	decrcpos(term, 1);
	tputs(tgoto(term->caps[C_CM], term->cpos % term->win.ws_col, 
				term->cpos / term->win.ws_col), 20, ft_putc);
}

void	movcright(t_term *term)
{
	incrcpos(term, 1);
	tputs(tgoto(term->caps[C_CM], term->cpos % term->win.ws_col,
				term->cpos / term->win.ws_col), 20, ft_putc);
}

void	movcto(t_term *term, size_t pos)
{
	setcpos(term, pos);
	tputs(tgoto(term->caps[C_CM], term->cpos % term->win.ws_col, 
				term->cpos / term->win.ws_col), 20, ft_putc);
}

void	movcnl(t_term *term)
{
	incrcpos(term, term->win.ws_col - term->cpos % term->win.ws_col);
	tputs(term->caps[C_SF], 1, ft_putc);
	tputs(term->caps[C_CR], 1, ft_putc);
}

/* Useless fonctions cause I have no personal life
void	movctopright(t_term *term)
{
	term->cpos = term->win.ws_col - 1;
	tputs(tgoto(term->caps[C_CM], term->win.ws_col - 1, 0), 20, ft_putc);
}

void	movcbotleft(t_term *term)
{
	term->cpos = term->size - term->win.ws_col;
	tputs(tgoto(term->caps[C_CM], 0, term->win.ws_row - 1), 20, ft_putc);
}

void	movchome(t_term *term)
{
	term->cpos = 0;
	tputs(term->caps[C_HO], 1, ft_putc);
}

void	movchomerow(t_term *term)
{
	term->cpos -= term->cpos % term->win.ws_col;
	tputs(term->caps[C_CR], 1, ft_putc);
}

void	movchomecol(t_term *term)
{
	term->cpos = term->cpos % term->win.ws_col;
	tputs(tgoto(term->caps[C_CM], term->cpos % term->win.ws_col, 
				term->cpos / term->win.ws_col), 20, ft_putc);
}

void	movcend(t_term *term)
{
	term->cpos = term->size - 1;
	tputs(tgoto(term->caps[C_CM], term->win.ws_col - 1,
				term->win.ws_row - 1), 20, ft_putc);
}

void	movcendrow(t_term *term)
{
	term->cpos += term->win.ws_col - term->cpos % term->win.ws_col - 1;
	tputs(tgoto(term->caps[C_CM], term->cpos % term->win.ws_col, 
				term->cpos / term->win.ws_col), 20, ft_putc);
}

void	movcendcol(t_term *term)
{
	term->cpos = term->size - term->win.ws_col
				+ term->cpos % term->win.ws_col;
	tputs(tgoto(term->caps[C_CM], term->cpos % term->win.ws_col, 
				term->cpos / term->win.ws_col), 20, ft_putc);
}

void	movcup(t_term *term)
{
	if ((size_t)(term->win.ws_col - 1) < term->cpos)
	{
		term->cpos -= term->win.ws_col;
		tputs(term->caps[C_UP], 1, ft_putc);
	}
}

void	movcdown(t_term *term)
{
	if (term->cpos < term->size - term->win.ws_col)
	{
		term->cpos += term->win.ws_col;
		tputs(term->caps[C_DO], 1, ft_putc);
	}
}
*/