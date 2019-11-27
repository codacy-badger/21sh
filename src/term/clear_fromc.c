/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_fromc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 16:53:55 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clear_fromc(t_term *term)
{
	tputs(term->caps[C_SC], 1, ft_putc);
	tputs(term->caps[C_CL], 1, ft_putc);
	if (term->cy < term->sizey - 1)
	{
		tputs(term->caps[C_DOWN], 1, ft_putc);
		tputs(term->caps[C_CR], 1, ft_putc);
		tputs(term->caps[C_CD], 1, ft_putc);
	}
	tputs(term->caps[C_RC], 1, ft_putc);
}
