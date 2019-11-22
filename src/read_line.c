/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "input.h"
#include <curses.h>
#include <term.h>

/*
** to fix: tgetstr called every time
** 			isalpha misses a lot of characters
*/
/*
** strinsert assume that there is enough space in str to insert
** need add strinsert && strremove equivalent to dstr struct to simplify code
** "ce" clears the line from cursor position
*/

static void	del_char(t_input *input, t_term *term)
{
	int		shift;

	ft_strremove(&input->line->str[input->pos], 1); //dstr_remove(&input->line, c);
	input->line->str[--input->line->len] = '\0';
	move_curs_left(input, term);
	tputs(term->caps.ce, 1, ft_putc);
	shift = echo_str(input, &input->line->str[input->pos + 1]);
	while (shift--)
		move_curs_left(input, term);
}

static void	add_char(t_input *input, t_term *term, int c)
{
	int		shift;

	echo_char(input, c);
	if (input->line->len == input->line->capacity) // handle this in dstr_insert...
		input->line->str = (char *)ft_memrealloc(input->line->str, input->line->len, input->line->capacity * 2);
	ft_strinsert(&input->line->str[input->pos], (char *)&c, -1);
	input->line->str[++input->line->len] = '\0';
	tputs(term->caps.ce, 1, ft_putc);
	shift = echo_str(input, &input->line->str[input->pos + 1]);
	while (shift--)
		move_curs_left(input, term);
}

static void	process_char(t_input *input, t_term *term, unsigned int c)
{

	if (c == term->keys.left && input->pos > 0)
		move_curs_left(input, term);
	else if (c == term->keys.right && input->pos + 1 < input->line->len)
		move_curs_right(input, term);
	else if (c == term->keys.bsp && input->pos > 0)
		del_char(input, term);
	else if (!ft_isctrl(c)) //isprint
		add_char(input, term, c);
}

int			read_line(t_term *term, t_input *input)
{
	unsigned int	c;

	c = 0;
	while (c != 10)
	{
		c = 0;
		read(STDIN_FILENO, &c, 4);
		process_char(input, term, c);
	}
	write(1, "\n", 1);
	write(1, input->line->str, input->line->len);
	return (0);
}
