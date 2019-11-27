/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movcleft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:46:27 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		movcleft(t_term *term)
{
	size_t	offset;

	if (term->cx == 0)
	{
		movcup(term);
		offset = term->sizex - 2;
		while (offset--)
			movcright(term);
	}
	else
	{
		tputs(term->caps[C_LEFT], 1, ft_putc);
		term->cx--;
	}
	return (0);
}
