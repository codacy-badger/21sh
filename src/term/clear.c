/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_fromc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 20:48:08 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clearfromc(t_term *term)
{
	tputs(term->caps[C_SC], 1, ft_putc);
	tputs(term->caps[C_CE], 1, ft_putc);
	if (term->cpos < term->size - term->sizex)
	{
		tputs(term->caps[C_DO], 1, ft_putc);
		tputs(term->caps[C_CR], 1, ft_putc);
		tputs(term->caps[C_CD], 1, ft_putc);
	}
	tputs(term->caps[C_RC], 1, ft_putc);
}