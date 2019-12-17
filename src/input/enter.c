/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eol.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 16:53:55 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		enter(t_input *input)
{
	move_end(input);
	if (input->termp->cpos % input->termp->win.ws_col)
		movcnl(input->termp);
	if (input->temp)
		ft_dstr_del((void **)&input->temp, NULL);
	if (input->line->len > 0)
		ft_lstadd(input->head, ft_lstnew(input->line));
	else
		ft_dstr_del((void **)&input->line, NULL);
	input->curr = input->head;
	input->pos = 0;
	return (EOL);
}