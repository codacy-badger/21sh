/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movcex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:46:27 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	movcex(t_term *term)
{
	tputs(tgoto(term->caps[C_CM], term->sizex - 1, term->cy), 1, ft_putc);
	term->cx = term->sizex - 1;
}
