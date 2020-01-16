/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_line_edit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:07:57 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/16 15:10:50 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		rl_put_match(t_input *input, char *partial, char *match)
{
	char	*diff;
	int		diff_len;

	diff = match + ft_strlen(partial);
	diff_len = ft_strlen(diff);
	while (diff_len--)
		addchar(input, (t_uint8 **)&diff);
}

void		rl_print_match_list(t_list_head *comp_list, t_input *input)
{
	t_list_head *cur;
	char		backup;

	cur = comp_list->next;
	write(1, "\n", 1);
	while (cur != comp_list)
	{
		ft_putendl(cur->data);
		cur = cur->next;
	}
	draw_prompt(input, input->last_prompt);
	printstr(input->termp, input->line->str);
}
