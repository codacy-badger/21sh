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

/*
** -On resize we'll lose cursor position
** -Newlines and backslashes are stored in the string
**
** To add : -move end line with 'end'
**			-copy paste
**			-history
**			-eventually move up and down on multiline...
*/

/* ***************************LIBFT*************************************** */

int		ft_quotes(char *str)
{
	while (*str)
	{
		if (*str == 34)
		{
			str++;
			while (*str && *str != 34)
				str++;
			if (!*str)
				return (34);
		}
		else if (*str == 39)
		{
			str++;
			while (*str && *str != 39)
				str++;
			if (!*str)
				return (39);
		}
		str++;
	}
	return (0);
}

/* ************************************************************************** */

/*
static int	del_char(t_input *input, t_term *term)
{
	int		i;

	i = 0;
	if (input->x > 0 || input->y > 0)
	{
		if (input->x == 0)
		{
			tputs(term->caps.up, 1, ft_putc);
			input->x = term->win.ws_col - 2;
			while (i++ < term->win.ws_col - 2)
				tputs(term->caps.nd, 1, ft_putc);
			input->y--;
		}
		move_curs_left(input, term);
		str_del_char(input);
		display_del_char(input, term);
	}
	return (0);
}
*/

static int	add_char(t_term *term, t_input *input, char c)
{
	size_t	oldx;
	size_t	oldy;

	oldx = term->cx;
	oldy = term->cy;
	line_add_char(input->line, c);
	display_str(term, &input->line->str[input->line->i - 1]);
	if (input->line->i < input->line->len)
	{
		input->line->i = input->line->len;
		while (term->cy > oldy || term->cx > oldx + 1)
			move_curs_left(term, input);
	}
	return (0);
}

static int	handle_eol(t_term *term, t_input *input, char c)
{
	t_line	*line;
	int		y;
	//int		quote;
	c = 0;

	display_nl(term);
	/*
	if ((quote = ft_quotes(input->line->str)) != 0)
	{
		if (quote == '\'')
			tputs(PSQ, 1, ft_putc);
		else if (quote == '"')
			tputs(PSDQ, 1, ft_putc);
		return (0);
	}
	*/
	if (input->line->str[input->line->len - 1] == '\\')
	{
		display_str(term, PS2);
		if (!(line = line_new(32, PS2)))
			return (-1);
		line_add(&input->line, line);
		input->line = input->line->next;
		if (input->line->next)
		{
			y = 0;
			tputs(term->caps.ce, 1, ft_putc);
			while (input->line->next)
			{
				display_nl(term);
				display_line(term, input->line->next);
				input->line = input->line->next;
				y++;
			}
			while (y--)
				move_curs_up(term, input);
		}
		return (0);
	}
	// remove backslashes;
	return (EOL);
}

static int	process_char(t_term *term, t_input *input, unsigned int c)
{
	if (c == term->keys.left)
		return (move_curs_left(term, input));
	else if (c == term->keys.right)
		return (move_curs_right(term, input));
	else if (c == term->keys.up)
		return (move_curs_up(term, input));
	/*
	else if (c == term->keys.bsp)
		return (del_char(input, term));
	else if (c == term->keys.home)
		return (move_curs_home(input, term));
	else if (c == term->keys.nextw)
		return (move_curs_nextw(input, term));
	else if (c == term->keys.prevw)
		return (move_curs_prevw(input, term));
	*/
	else if (ft_isprint(c))
		return (add_char(term, input, (char)c));
	else if (c == EOL)
		return (handle_eol(term, input, (char)c));
	return (0);
}

int			read_line(t_term *term, t_input *input)
{
	unsigned int	c;

	c = 0;
	display_str(term, PS1);
	//input->line->prompt = ft_strdup(PS1);
	while (process_char(term, input, c) != EOL)
	{
		c = 0;
		read(STDIN_FILENO, &c, sizeof(c));
		//printf("%u\n", c);
	}
	printf("\nline_cap: %zu, line_len: %zu\n%s", input->line->size, input->line->len, input->line->str);
	return (0);
}
