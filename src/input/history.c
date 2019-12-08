/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 23:14:17 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 01:21:51 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_line	*line_dup(t_line *line)
{
	t_line *new;

	new = line_new(line->size);
	new->i = line->i;
	new->len = line->len;
	ft_strcpy(new->str, line->str);
	return (new);
}

int		history_move_up(t_term *term, t_input *input)
{
	int		old_i;

	if (ft_list_empty(input->history))
		return (1);
	old_i = input->line->i;
	if (input->history_cur == NULL)
	{
		input->history_cur = input->history->prev;
		input->line_backup = input->line;
	}
	else if (!ft_list_is_first(input->history_cur, input->history))
	{
		input->history_cur = input->history_cur->prev;
		line_del(&input->line);
	}
	else
		return (1);
	while (old_i-- > 0)
		movcleft(term);
	clear_fromc(term);
	input->line = line_dup(input->history_cur->data);
	input->line->i = input->line->len;
	display_str(term, input->line->str);
	return (0);
}

int		history_move_down(t_term *term, t_input *input)
{
	int		old_i;

	if (input->history_cur == NULL)
		return (1);
	old_i = input->line->i;
	line_del(&input->line);
	if (!ft_list_is_last(input->history_cur, input->history))
	{
		input->history_cur = input->history_cur->next;
		input->line = line_dup(input->history_cur->data);
	}
	else
	{
		input->history_cur = NULL;
		input->line = input->line_backup;
	}
	while (old_i-- > 0)
		movcleft(term);
	clear_fromc(term);
	input->line->i = input->line->len;
	display_str(term, input->line->str);
	return (0);
}
