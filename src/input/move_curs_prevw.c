/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_curs_prevw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		move_curs_prevw(t_input *input, t_term *term)
{
	while (input->x > 0 && ft_iswhitespace(input->line->str[input->i - 1]))
		move_curs_left(input, term);
	while (input->x > 0 && !ft_iswhitespace(input->line->str[input->i - 1]))
		move_curs_left(input, term);
	return (0);
}
