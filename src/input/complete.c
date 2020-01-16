/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:22:51 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/16 18:22:49 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		g_nb_comp_match;

void		free_comp_list(t_list_head *comp_list)
{
	t_list_head *cur;
	t_list_head *tmp;

	cur = comp_list->next;
	while (cur != comp_list)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp->data);
		ft_list_del(tmp);
	}
	free(comp_list);
}

/*
** get the lowest common prefix of the list of matches. We sort the list then
** look at the lcp of the first and last elements of the list to find the lcp
** of the full list.
*/

typedef	int	(*t_cmp_func) (void *a, void *b);

char		*get_lcp(t_list_head *comp_list, char *partial)
{
	char	*first;
	char	*last;
	int		i;

	ft_list_sort(&comp_list, (t_cmp_func)ft_strcmp);
	first = comp_list->next->data;
	last = comp_list->prev->data;
	i = 0;
	while (first[i] == last[i])
		i++;
	if (ft_strlen(partial) == (unsigned int)i)
		return (NULL);
	return (ft_strndup(first, i));
}

char		*comp_get_partial_word(t_input *input)
{
	int		i;

	i = input->pos;
	while (i > 0 && input->line->str[i - 1] != ' ')
		i--;
	return (ft_strndup(input->line->str + i, input->pos - i));
}

extern t_env	*g_env;

int			rl_complete(t_input *input)
{
	t_list_head *comp_list;
	char		*partial;
	char		*lcp;

	if (input->line->str[input->pos] != '\0'
			&& input->line->str[input->pos] != ' ')
		return (0);
	partial = comp_get_partial_word(input);
	comp_list = comp_get_file_list(partial, false);
	lcp = NULL;
	if (g_nb_comp_match == 0)
	{
		free_comp_list(comp_list);
		free(partial);
		return (0);
	}
	if (g_nb_comp_match == 1)
		rl_put_match(input, partial, comp_list->next->data);
	else
	{
		if (input->first_tab_press && (lcp = get_lcp(comp_list, partial)))
			rl_put_match(input, partial, lcp);
		free(lcp);
		if (!input->first_tab_press)
		{
			rl_print_match_list(comp_list, input);
			input->first_tab_press = true;
		}
		else if (lcp == NULL)
			input->first_tab_press = false;
	}
	free(partial);
	free_comp_list(comp_list);
	return (0);
}
