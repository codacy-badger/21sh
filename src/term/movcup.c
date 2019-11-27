/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movcup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:46:27 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		movcup(t_term *term)
{
	if (term->cy == 0)
	{
		tputs(term->caps[C_CR], 1, ft_putc);
		tputs(term->caps[C_SR], 1, ft_putc);
	}
	else
	{
		tputs(term->caps[C_UP], 1, ft_putc);
		term->cy--;
	}
	return (0);
}
