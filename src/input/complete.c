/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:22:51 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/16 10:58:14 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list_head		*get_comp_filename(char *partial)
{
	DIR 			*dirp;
	struct dirent	*dp;
	int				i;
	t_list_head		*head;

	if ((dirp = opendir(".")) == NULL)
		return (NULL);
	i = 0;
	head = ft_list_first_head(NULL);
	while ((dp = readdir(dirp)))
	{
		if (ft_strstr(dp->d_name, partial) == dp->d_name)
			ft_list_add_tail(ft_strdup(dp->d_name), head);
	}
	closedir(dirp);
	return (NULL);
}
