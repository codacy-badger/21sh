/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_line_edit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:07:57 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/17 16:28:27 by fratajcz         ###   ########.fr       */
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

/*
** for file completions, the match list has the partial word at the start of
** each match: eg typing libft/<tab> get a match list consisting of libft/src,
** libft/inc, etc.
** we only want to print the last part of the path so we calculate the length
** to skip and add it to every string we print. In the previous example, we
** print src, inc...
*/

void		rl_print_match_list(t_list_head *comp_list, char *partial,
		t_input *input)
{
	t_list_head *cur;
	char		backup;
	char		*last_slash;
	int			skip_len;

	if ((last_slash = ft_strrchr(partial, '/')) != NULL)
		skip_len = last_slash - partial + 1;
	else
		skip_len = 0;
	cur = comp_list->next;
	write(1, "\n", 1);
	while (cur != comp_list)
	{
		ft_putendl(cur->data + skip_len);
		cur = cur->next;
	}
	draw_prompt(input, input->last_prompt);
	printstr(input->termp, input->line->str);
}
