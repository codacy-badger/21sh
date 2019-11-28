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
** read prompts from conf file...?? 
*/

static int	handle_eol(t_term *term, t_input *input)
{
	move_curs_end(term, input);
	move_curs_left(term, input);
	display_nl(term);
	printf("\nline_cap: %zu, line_len: %zu, \n'%s'", input->line->size, input->line->len + 1, input->line->str);
	ft_strinsert(&input->line->str[input->line->len++], "\n", 1);
	return (EOL);
}

static int	process_char(t_term *term, t_input *input, unsigned int c)
{
	if (ft_isprint(c))
		return (input_add_char(term, input, (char)c));
	else if (c == term->keys[K_BSP] || c == term->keys[K_DEL])
		return (input_del_char(term, input, c));
	else if (c == term->keys[K_LEFT])
		return (move_curs_left(term, input));
	else if (c == term->keys[K_RIGHT])
		return (move_curs_right(term, input));
	else if (c == term->keys[K_UP]) //ctrl - down 
		return (move_curs_up(term, input));
	else if (c == term->keys[K_DOWN]) //ctrl - up
		return (move_curs_down(term, input));
	else if (c == term->keys[K_HOME])
		return (move_curs_home(term, input));
	else if (c == term->keys[K_END])
		return (move_curs_end(term, input));
	else if (c == term->keys[K_NXTW])
		return (move_curs_nextw(term, input));
	else if (c == term->keys[K_PRVW])
		return (move_curs_prevw(term, input));
	else if (c == term->keys[K_CUTWORD])
		return (cut_previous_word(term, input));
	else if (c == term->keys[K_CUTAFTER])
		return (cut_after(input));
	else if (c == term->keys[K_CUTBEFORE])
		return (cut_before(term, input));
	else if (c == term->keys[K_PASTE])
		return (paste(term, input));
	else if (c == EOL || c == 4)
		return (handle_eol(term, input));
	return (0);
}

int			input_read_line(t_term *term, t_input *input)
{
	unsigned int	c;

	c = 0;
	//input->line = line_new(32); //handle this in reset input
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
	return (0);
}
