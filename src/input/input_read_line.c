/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 15:38:19 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/* 
** To add :
**			-handle str reallocation directly in ft_strinsert,
**				which is not protected btw...
**			-history (lexer)
*/

static int	handle_eol(t_term *term, t_input *input, unsigned int c)
{
	input->prev = c;
	move_curs_end(term, input);
	ft_strinsert(&input->line->str[input->line->len++], (char *)&c, 1);
	move_curs_left(term, input);
	display_nl(term);
	return (K_EOL);
}

static int	process_char(t_term *term, t_input *input, unsigned int c)
{
	/*
	** make function table
	*/
	if (!isctrl(term, c) && c != 0) //cant use ft_isprint because of wchar, care about weird codes
		return (input_add_char(term, input, c));
	else if (c == term->keys[K_EOL] || c == term->keys[K_EOF])
		return (handle_eol(term, input, c));
	else if (c == term->keys[K_BSP] || c == term->keys[K_DEL])
		return (input_del_char(term, input, c));
	else if (c == term->keys[K_LEFT])
		return (move_curs_left(term, input));
	else if (c == term->keys[K_RIGHT])
		return (move_curs_right(term, input));
	else if (c == term->keys[K_UP])
		return (move_curs_up(term, input));
	else if (c == term->keys[K_DOWN])
		return (move_curs_down(term, input));
	else if (c == term->keys[K_HOME])
		return (move_curs_home(term, input));
	else if (c == term->keys[K_END])
		return (move_curs_end(term, input));
	else if (c == term->keys[K_NXTW])
		return (move_curs_nextw(term, input));
	else if (c == term->keys[K_PRVW])
		return (move_curs_prevw(term, input));
	else if (c == term->keys[K_CUTW])
		return (cut_prevw(term, input));
	else if (c == term->keys[K_CUTA])
		return (cut_after(term, input));
	else if (c == term->keys[K_CUTB])
		return (cut_before(term, input));
	else if (c == term->keys[K_PAST])
		return (paste(term, input));
	return (0);
}

int			input_read_line(t_term *term, t_input *input)
{
	int				ret;
	unsigned int	c;

	c = 0;
	display_str(term, *(input->pmpt));
	while ((ret = read(STDIN_FILENO, &c, sizeof(c))) != -1)
	{
		if ((ret = process_char(term, input, c)) == K_EOL)
			return (0);
		else if (ret < 0)
			break ; //error
		input->prev = c;
		c = 0;
	}
	return (ret);
}
