/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 23:03:42 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/21 23:05:58 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void		ft_dstr_insert(t_dstr **dstr, char c, int index)
{
	size_t	old_size;
	size_t	new_size;

	if (*dstr == NULL)
		*dstr = ft_dstr_new(1);
	if ((*dstr)->len == (*dstr)->capacity - 1)
	{
		old_size = (*dstr)->capacity;
		new_size = ((*dstr)->capacity *= 2);
		(*dstr)->str = (char *)ft_memrealloc((void **)&(*dstr)->str, old_size, new_size);
		if (!((*dstr)->str))
			return ; //(-1)
	}
	if (index > (*dstr)->capacity - 1)
		index = (*dstr)->capacity - 1;
	if (index < 0)
		index = 0;
	ft_strinsert(&(*dstr)->str[index], &c, 1);
	(*dstr)->len++;
}
