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

void	init_input(struct s_input *input)
{
	input->line = new_dstr(0);
	input->pos = 0;
}

/*
** to fix: tgetstr called every time
** 			isalpha misses a lot of characters
*/

void	process_char(t_input *input, unsigned int c, struct s_keys *keys)
{
	if (c == keys->left && input->pos > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_putc);
		input->pos--;
	}
	else if (c == keys->right && input->pos + 1 < input->line->len)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putc);
		input->pos++;
	}
	else if (ft_isalpha(c))
	{
		add_char_to_dstr(&input->line, c);
		input->pos++;
		write(1, &c, 4);
	}
}

int		read_line(t_input *input, struct s_keys *keys)
{
	unsigned int	c;

	c = 0;
	while (c != 10)
	{
		c = 0;
		read(STDIN_FILENO, &c, 4);
		process_char(input, c, keys);
	}
	return (0);
}
