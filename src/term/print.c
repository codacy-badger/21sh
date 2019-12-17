/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 16:53:55 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_putc(int c)
{
	if (write(STDOUT_FILENO, (char *)&c, 1) != 1)
		return (0);
	return (1);
}

/*
** On gnome-terminal, some wide chars like emojis take 2 columns on display
** to avoid overlapping, so cursor position must be increased by 2 instead of one
** in such a case.
*/
int		printstr(t_term *term, char *str)
{
	size_t	nprint;
	size_t	clen;

	clen = 0;
	nprint = 0;
	while (*str)
	{
		clen = ft_charlen(*str);
		write(STDOUT_FILENO, str, clen);
		if (!((term->cpos + 1) % term->win.ws_col))
			tputs(term->caps[C_SF], 1, ft_putc);
		incrcpos(term, 1);
		str += clen;
		nprint++;
	}
	return (nprint);
}