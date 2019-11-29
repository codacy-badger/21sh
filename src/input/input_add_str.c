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
	int		len;

	len = ft_strlen(s);
	line_add_str(input->line, s);
	offset = display_str(term, &input->line->str[input->line->i]) - len;
	while (offset--)
		movcleft(term);
	input->line->i += len;
	return (0);
}
