/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/* ***************************LIBFT*************************************** */

int			ft_quotes(char *str)
{
	(void)str;
	return (0);
}

/* ************************************************************************** */

static int	handle_eol(t_input *input, char c)
{
	char	quote;

	ft_putc(EOL);
	if (c == EOL && input->line->str[input->line->len - 1] == '\\')
	{
		input->y++;
		input->x = 0;
		ft_strremove(&input->line->str[input->line->len - 1], 1);
		input->line->len--;
		input->i--;
		tputs(PS2, 1, ft_putc);
		return (0);
	}
	else if ((quote = ft_quotes(input->line->str)) != 0)
	{
		input->y++;
		input->x = 0;
		if (quote == '\'')
			tputs(PSQ, 1, ft_putc);
		else if (quote == '"')
			tputs(PSDQ, 1, ft_putc);
		return (0);
	}
	return (EOL);
}

static int	del_char(t_input *input, t_term *term)
{
	if (input->x > 0)
	{
		move_curs_left(input, term);
		str_del_char(input);
		display_del_char(input, term);
	}
	return (0);
}

static int	add_char(t_input *input, t_term *term, char c)
{
	str_add_char(input, c);
	display_add_char(input, term);
	move_curs_right(input, term);
	return (0);
}

static int	process_char(t_input *input, t_term *term, unsigned int c)
{
	if (c == term->keys.left)
		return (move_curs_left(input, term));
	else if (c == term->keys.right)
		return (move_curs_right(input, term));
	else if (c == term->keys.bsp)
		return (del_char(input, term));
	else if (c == term->keys.home)
		return (move_curs_home(input, term));
	else if (c == term->keys.nextw)
		return (move_curs_nextw(input, term));
	else if (c == term->keys.prevw)
		return (move_curs_prevw(input, term));
	else if (ft_isprint(c))
		return (add_char(input, term, (char)c));
	else if (c == EOL || c == 4)
		return (handle_eol(input, (char)c));
	return (0);
}

int			read_line(t_term *term, t_input *input)
{
	unsigned int	c;

	c = 0;
	tputs(PS1, 1, ft_putc);
	while (process_char(input, term, c) != EOL)
	{
		c = 0;
		read(STDIN_FILENO, &c, sizeof(c));
		//printf("%u\n", c);
	}
	printf("\nline_cap: %d, line_len: %d\n%s\n", input->line->capacity, input->line->len, input->line->str);
	return (0);
}
