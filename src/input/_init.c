/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:23:20 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/11 18:32:41 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	init_keys(struct s_input *input)
{
	char	*s;

	input->keys[K_DEL] = (s = tgetstr("kD", NULL)) ? *(int *)s : 0;
	input->keys[K_LEFT] = (s = tgetstr("kl", NULL)) ? *(int *)s : 0;
	input->keys[K_RIGHT] = (s = tgetstr("kr", NULL)) ? *(int *)s : 0;
	input->keys[K_UP] = (s = tgetstr("ku", NULL)) ? *(int *)s : 0;
	input->keys[K_DOWN] = (s = tgetstr("kd", NULL)) ? *(int *)s : 0;
	input->keys[K_HOME] = (s = tgetstr("kh", NULL)) ? *(int *)s : 0;
	input->keys[K_CUP] = 71696882162459;
	input->keys[K_CDOWN] = 72796393790235;
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
}

int			init_input(struct s_input *input, struct s_term *term)
{
	init_keys(input);
	input->termp = term;
	input->head = ft_lstnew(NULL);
	input->curr = input->head;
	input->temp = NULL;
	input->esc = false;
	input->first_line = true;
	return (0);
}
