/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 23:14:17 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/11 20:08:46 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** -input->head is the head of the list, curr is the pointer, pointing on head
**  when we are on current line. The lines are added to head in enter() function
**  when eol is received.
** -temp is the current line backup, its set the first time we move up, and reset
**  to NULL when we go back on the current line. Its freed in enter() function if
**  it hasnt been reset to NULL.
** -In the case we have identical lines one after the other, we skip them.
** -I don t skip lines beginning by ' ', cause its complicated. But we could just
**  decide to not store them in history.
*/

static char		*str(t_list *list)
{
	return (((t_dstr *)list->data)->str);
}

static t_dstr	*getnextline(t_input *input)
{
	input->curr = input->curr->next;
	while (input->curr != input->head
	&& ft_strequ(str(input->curr), str(input->curr->prev)))
		input->curr = input->curr->next;
	return ((t_dstr *)input->curr->data);
}

static t_dstr	*getprevline(t_input *input)
{
	input->curr = input->curr->prev;
	while (input->curr->prev != input->head
	&& ft_strequ(str(input->curr), str(input->curr->prev)))
		input->curr = input->curr->prev;
	return ((t_dstr *)input->curr->data);
}

int				history_down(t_input *input)
{
	t_dstr	*target;

	if (input->curr == input->head)
		return (0);
	move_home(input);
	if (input->line)
		ft_dstr_del((void **)&input->line, NULL);
	if ((target = getnextline(input)) && input->curr != input->head
	&& !(input->line = ft_dstr_new(target->str, target->len, target->size)))
		return (-1);
	else if (input->curr == input->head)
	{
		input->line = input->temp;
		input->temp = NULL;
	}
	clearfromc(input->termp);
	printstr(input->termp, input->line->str);
	input->pos = input->line->len;
	return (0);
}

int			history_up(t_input *input)
{
	t_dstr	*target;

	if (input->curr->prev == input->head)
		return (0);
	move_home(input);
	if (!input->temp)
	{
		input->temp = input->line;
		input->line = NULL;
	}
	else if (input->line)
		ft_dstr_del((void **)&input->line, NULL);
	if ((target = getprevline(input))
	&& !(input->line = ft_dstr_new(target->str, target->len, target->size)))
		return (-1);
	clearfromc(input->termp);
	printstr(input->termp, input->line->str);
	input->pos = input->line->len;
	return (0);
}
