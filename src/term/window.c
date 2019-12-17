/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_setsize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** update term->cpos
** This is weird, it works but cant find general formula for
** wrapping on the same line when we reach 0 or size
*/

void	setcpos(t_term *term, size_t value)
{
	term->cpos = value;
	if (term->cpos > term->size - 1)
		term->cpos = term->size - term->win.ws_col
					+ term->cpos % term->size % term->win.ws_col;
}

void	incrcpos(t_term *term, size_t value)
{
	term->cpos += value;
	if (term->cpos > term->size - 1)
		term->cpos = term->size - term->win.ws_col
					+ term->cpos % term->size % term->win.ws_col;
}

void	decrcpos(t_term *term, size_t value)
{
	if ((int)(term->cpos - value) < 0)
		term->cpos = (size_t)(term->win.ws_col - value) % term->win.ws_col;
	else
		term->cpos -= value;
}

int		getcpos(t_term *term)
{
	char	buf[16];
	char	*p;
	int		x;
	int		y;

	p = buf;
	ft_bzero(buf, 16);
	if (write(STDOUT_FILENO, "\033[6n", 4) != 4)
		return (-1);
	read(STDIN_FILENO, buf, 15);
	y = ft_atoi(p + 2) - 1;
	while (*p && *p != ';')
		p++;
	x = ft_atoi(p + 1) - 1;
	term->cpos = y * term->win.ws_col + x;
	return (0);
}

int		getwinsize(t_term *term)
{
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &term->win) == -1)
		return (-1);
	term->size = term->win.ws_col * term->win.ws_row;
	return (0);
}
