/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_curs_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:46:27 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		move_curs_right(t_term *term, t_input *input)
{
	if (input->line->i < input->line->len)
	{
		movcright(term);
		input->line->i++;
	}
	return (0);
}
