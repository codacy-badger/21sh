/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_reset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:23:20 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 01:23:57 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	input_clear_line(t_term *term, t_input *input)
{
	size_t	plen;

	plen = ft_strlen(input->prompt);
	while (input->line->i)
		move_curs_left(term, input);
	while (plen--)
		movcleft(term);
	tputs(term->caps[C_CD], 1, ft_putc);
	display_str(term, input->prompt);
}

static void	init_keys(struct s_input *input)
{
	char	*s;

	input->keys[K_DEL] = (s = tgetstr("kD", NULL)) ? *(int *)s : 0;
	input->keys[K_LEFT] = (s = tgetstr("kl", NULL)) ? *(int *)s : 0;
	input->keys[K_RIGHT] = (s = tgetstr("kr", NULL)) ? *(int *)s : 0;
	input->keys[K_UP] = (s = tgetstr("ku", NULL)) ? *(int *)s : 0;
	input->keys[K_DOWN] = (s = tgetstr("kd", NULL)) ? *(int *)s : 0;
	input->keys[K_HOME] = (s = tgetstr("kh", NULL)) ? *(int *)s : 0;
	input->keys[K_END] = 4607771;
	input->keys[K_BSP] = 127;
	input->keys[K_ESC] = 27;
	input->keys[K_SPC] = 32;
	input->keys[K_ENTER] = 10;
	input->keys[K_REDRAW] = 12;
	input->keys[K_PRVW] = 24; // ^X
	input->keys[K_NXTW] = 14; // ^N
	input->keys[K_CUTW] = 23;// ^W
	input->keys[K_CUTA] = 11;// ^K
	input->keys[K_CUTB] = 21; // ^U
	input->keys[K_PAST] = 25; // ^Y
	input->keys[K_EOL] = 10; //nl,  cr??
	input->keys[K_EOF] = 4; // ^D
}

int			input_init(struct s_input *input, struct s_data *data)
{
	init_keys(input);
	input->prompt = data->prompts[PS1];
	if (!(input->line = line_new(32)))
		return (ALLOC_ERROR);
	if (!(input->clipb = line_new(32)))
		return (ALLOC_ERROR);
	return (0);
}

void		input_reset(t_term *term, t_input *input)
{
	input_clear_line(term, input);	
	line_del(&input->line);
	input->line = line_new(32);
}
