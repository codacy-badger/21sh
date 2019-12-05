/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_add_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 15:38:19 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		input_add_str(t_term *term, t_input *input, char *s)
{
	size_t	offset;
	size_t	new_i;
	int		len;

	len = ft_strlen(s);
	new_i = input->line->i + len;
	line_add_str(input->line, s);
	offset = display_str(term, &input->line->str[input->line->i]);
	while (offset--)
		movcleft(term);
	while (input->line->i < new_i)
		move_curs_right(term, input);
	return (0);
}
