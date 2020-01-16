/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:04:39 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/16 15:13:18 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_nb_comp_match;

t_list_head	*comp_get_file_list(char *partial)
{
	char			*dir_to_search;
	DIR				*dirp;
	struct dirent	*dp;
	int				i;
	t_list_head		*comp_list;

	g_nb_comp_match = 0;
	if ((dirp = opendir(".")) == NULL)
		return (NULL);
	i = 0;
	comp_list = ft_list_first_head("");
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

