/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:45:05 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/17 14:06:30 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_comp_list(t_list_head **comp_list)
{
	t_list_head *cur;
	t_list_head *tmp;

	cur = (*comp_list)->next;
	while (cur != *comp_list)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp->data);
		ft_list_del(tmp);
	}
	free(*comp_list);
	*comp_list = NULL;
}

bool	is_cd(char *str, int i)
{
	if (i == 0)
		return (false);
	if (str[i] == 'd' && str[i - 1] == 'c')
	{
		if (i == 1)
			return (true);
		i -= 2;
		while (i > 0 && str[i] == ' ')
			i--;
		if (i == 0 || str[i] == '|' || str[i] == ';')
			return (true);
	}
	return (false);
}
