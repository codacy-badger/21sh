/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 20:47:56 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Removed list of lines, useless... could be useful if we handle window resize,
** which is not in the subject...
** 
** To add :
**			//-copy paste
**          -we could add y movement on line if line is larger than window
**			-history
** read prompts from conf file...?? 
*/

static int	handle_eol(t_term *term, t_input *input)
{
	if (input->line->i == input->line->len)
		move_curs_left(term, input);
	while (input->line->i < input->line->len - 1)
		move_curs_right(term, input);
	ft_strinsert(&input->line->str[input->line->i + 1], "\n", 1);
	input->line->len++;
	display_nl(term);
	return (EOL);
}

static int	del_char(t_term *term, t_input *input, int c)
{
	size_t	offset;

	if (c == (int)term->keys[K_DEL] && input->line->str[input->line->i])
	{
		line_del_char(input->line);
		offset = display_str(term, &input->line->str[input->line->i]);
		tputs(term->caps[C_CE], 1, ft_putc);
		while (offset--)
			movcleft(term);
	}
	else if (input->line->i > 0)
	{
		move_curs_left(term, input);
		line_del_char(input->line);
		clrfromc(term);
		offset = display_str(term, &input->line->str[input->line->i]);
		while (offset--)
			movcleft(term);
	}
	return (0);
}

static int	add_char(t_term *term, t_input *input, char c)
{
	size_t		offset;

	line_add_char(input->line, c);
	offset = display_str(term, &input->line->str[input->line->i]);
	while (offset--)
		movcleft(term);
	move_curs_right(term, input);
	return (0);
}

static int	process_char(t_term *term, t_input *input, unsigned int c)
{
	if (c == term->keys[K_LEFT])
		return (move_curs_left(term, input));
	else if (c == term->keys[K_RIGHT])
		return (move_curs_right(term, input));
	else if (c == term->keys[K_BSP] || c == term->keys[K_DEL])
		return (del_char(term, input, c));
	else if (c == term->keys[K_HOME])
		return (move_curs_home(term, input));
	else if (c == term->keys[K_END])
		return (move_curs_end(term, input));
	else if (c == term->keys[K_NXTW])
		return (move_curs_nextw(term, input));
	else if (c == term->keys[K_PRVW])
		return (move_curs_prevw(term, input));
	else if (ft_isprint(c))
		return (add_char(term, input, (char)c));
	else if (c == term->keys[K_CUTWORD])
		return (cut_previous_word(term, input));
	else if (c == term->keys[K_CUTAFTER])
		return (cut_after(input));
	else if (c == term->keys[K_CUTBEFORE])
		return (cut_before(term, input));
	else if (c == term->keys[K_PASTE])
		return (paste(term, input));
	else if (c == term->keys[K_REDRAW])
		redraw(term, input);
	else if (c == EOL || c == 4)
		return (handle_eol(term, input));
	return (0);
}

int			read_line(t_term *term, t_input *input)
{
	unsigned int	c;

	c = 0;
	//input->line = line_new(32);
	display_str(term, *(input->pmpt));
	while (process_char(term, input, c) != EOL)
	{
		c = 0;
		if (read(STDIN_FILENO, &c, sizeof(c)) == -1)
			return (-1);
		//printf("%u\n", c);
	}
	/*
	** on tokenization, process backslashes, if line ends with backslash
	** or is ! correctly quoted, update input->prompt ptr and return read_line
	*/
	printf("\nline_cap: %zu, line_len: %zu, \n'%s'", input->line->size, input->line->len, input->line->str);
	return (0);
}
