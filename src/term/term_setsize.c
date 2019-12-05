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

static int	setcpos(t_term *term)
{
	char	buff[32];
	int		i;

	i = 0;
	if (write(STDOUT_FILENO, "\033[6n", 4) != 4)
		return (-1);
	while (read(STDIN_FILENO, &buff[i], 1) == 1 && buff[i] != 'R')
		i++;
	i = 2;
	term->cy = ft_atoi(&buff[i]) - 1;
	while (buff[i] != ';')
		i++;
	term->cx = ft_atoi(&buff[++i]) - 1;
	return (0);
}

int			term_setsize(t_term *term)
{
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &term->win) == -1)
		return (-1);
	if (setcpos(term) == -1)
		return (-1);
	term->sizex = term->win.ws_col;
	term->sizey = term->win.ws_row;
	return (0);
}
