/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:46:27 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	move_curs_left(t_input *input, t_term *term)
{
	tputs(term->caps.le, 1, ft_putc);
	input->pos--;
}

void	move_curs_right(t_input *input, t_term *term)
{
	tputs(term->caps.ri, 1, ft_putc);
	input->pos++;
}

int		echo_char(t_input *input, int c)
{
	int		ret;

	ret = write(STDOUT_FILENO, &c, sizeof(c));
	input->pos++;
	return (ret);
}

int		echo_str(t_input *input, char *s)
{
	size_t	len;
	int		ret;

	len = ft_strlen(s);
	ret = write(STDOUT_FILENO, s, len);
	input->pos += len;
	return (ret);
}
