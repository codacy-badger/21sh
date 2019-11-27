/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movcright.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:46:27 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		movcright(t_term *term)
{
	if (term->cx == term->sizex - 2)
	{
		movcdown(term);
		movchx(term);
	}
	else
	{
		tputs(term->caps[C_RIGHT], 1, ft_putc);
		term->cx++;
	}
	return (0);
}
