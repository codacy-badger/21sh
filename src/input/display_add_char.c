/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_add_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	display_add_char(t_input *input, t_term *term)
{
	tputs(term->caps.sc, 1, ft_putc);
	tputs(&input->line->str[input->i], 1, ft_putc);
	tputs(term->caps.rc, 1, ft_putc);
}
