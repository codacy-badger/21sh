/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/11 18:55:30 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** -We move cursor to newline only if we are not at the beginning of the line.
** -If the line backup for history is not NULL (because we have scrolled up
**  in history and not have not scrolled down to the prev current line), we
**  delete it.
** -We add the current line to history if its not empty, else we delete it.
** -We reset the history cursor and the pos.
*/

int			enter(t_input *input)
{
	move_end(input);
	ft_dstr_add(input->line, '\n');
	input->pos++;
	if (input->termp->cpos % input->termp->sizex)
		movcnl(input->termp);
	if (input->temp)
		ft_dstr_del((void **)&input->temp, NULL);
	input->curr = input->head;
	return (EOL);
}
