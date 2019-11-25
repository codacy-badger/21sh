/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/25 23:39:24 by fratajcz         ###   ########.fr       */
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

static int	handle_eol(t_input *input, char c)
{
	int		quote;

	ft_putc(EOL);
	if (c == 4)
		return (EOL);
	input->i = input->line->len;
	str_add_char(input, EOL);
	input->x = 0;
	input->y++;
	input->i++;
	if ((quote = ft_quotes(input->line->str)) != 0)
	{
		if (quote == '\'')
			tputs(PSQ, 1, ft_putc);
		else if (quote == '"')
			tputs(PSDQ, 1, ft_putc);
		return (0);
	}
	else if (input->line->str[input->line->len - 2] == '\\')
	{
		tputs(PS2, 1, ft_putc);
		return (0);
	}
	/*
	remove_nl & backslashes;
	*/
	return (EOL);
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
	else if (c == term->keys.cutword)
		return (cut_previous_word(input, term));
	else if (c == term->keys.cutafter)
		return (cut_after(input));
	else if (c == term->keys.cutbefore)
		return (cut_before(input, term));
	else if (c == term->keys.paste)
		return (paste(input));
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
	}
	printf("\n'%s'\nline_cap: %d, line_len: %d\n", input->line->str, input->line->capacity, input->line->len);
	return (0);
}
