/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 23:03:31 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/21 23:06:12 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

t_dstr		*ft_dstr_new(size_t size)
{
	t_dstr *dstr;

	if (size == 0)
		size++;
	dstr = (t_dstr *)ft_memalloc(sizeof(t_dstr));
	dstr->str = (char *)ft_memalloc(size);
	dstr->capacity = size;
	dstr->len = 0;
	return (dstr);
}
