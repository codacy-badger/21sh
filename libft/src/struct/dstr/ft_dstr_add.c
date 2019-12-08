/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 23:03:42 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/21 23:05:58 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void		ft_dstr_add(t_dstr **dstr, char c)
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
	(*dstr)->str[(*dstr)->len++] = c;
	(*dstr)->str[(*dstr)->len] = 0;
}
