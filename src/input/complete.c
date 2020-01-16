/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:22:51 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/16 12:31:29 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		g_nb_comp_match;

t_list_head	*get_comp_filename(char *partial)
{
	char			*dir_to_search;
	DIR				*dirp;
	struct dirent	*dp;
	int				i;
	t_list_head		*comp_list;

	if ((dirp = opendir(".")) == NULL)
		return (NULL);
	i = 0;
	comp_list = ft_list_first_head(NULL);
	g_nb_comp_match = 0;
	while ((dp = readdir(dirp)))
	{
		if (ft_strstr(dp->d_name, partial) == dp->d_name)
		{
			ft_list_add_tail(ft_strdup(dp->d_name), comp_list);
			g_nb_comp_match++;
		}
	}
	closedir(dirp);
	return (comp_list);
}

void		rl_add_and_print_match(t_input *input, char *partial, char *match)
{
	char	*diff;
	int		diff_len;

	diff = match + ft_strlen(partial);
	diff_len = ft_strlen(diff);
	while (diff_len--)
		addchar(input, (t_uint8 **)&diff);
}

char		*get_comp_partial_word(t_input *input)
{
	int		i;

	i = input->pos;
	while (i > 0 && input->line->str[i - 1] != ' ')
		i--;
	return (ft_strndup(input->line->str + i, input->pos - i));
}

void		print_match_list(t_list_head *comp_list, t_input *input)
{
	t_list_head *cur;
	char		backup;

	cur = comp_list->next;
	write(1, "\n", 1);
	while (cur != comp_list)
	{
		printf("%s\n", cur->data);
		cur = cur->next;
	}
	fflush(stdout);
	draw_prompt(input, input->last_prompt);
	printstr(input->termp, input->line->str);
}

int			rl_complete(t_input *input)
{
	static bool	first_tab_press = true;
	t_list_head *comp_list;
	char		*partial;

	partial = get_comp_partial_word(input);
	comp_list = get_comp_filename(partial);
	if (g_nb_comp_match == 0)
		return (0);
	if (g_nb_comp_match == 1)
		rl_add_and_print_match(input, partial, comp_list->next->data);
	else if (first_tab_press == false)
	{
		print_match_list(comp_list, input);
		first_tab_press = true;
	}
	else
		first_tab_press = false;
	free(partial);
	return (0);
}
