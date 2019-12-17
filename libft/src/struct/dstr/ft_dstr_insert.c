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

/*
** i is the index in the dstr where you want to insert.
** str is the address of the string to insert, len is the length of that string,
*/
int		ft_dstr_insert(t_dstr *dstr, size_t i, char *str, size_t len)
{
	char	*tmp;
	char	*ptr;
	size_t	new_len;

	if (!dstr)
		return (0);
	new_len = dstr->len + len;
	if (new_len > dstr->size - 1)
	{
		tmp = dstr->str;
		dstr->size = ft_next_power_of_two(new_len + 1);
		dstr->str = (char *)ft_memrealloc(dstr->str, dstr->len, dstr->size);
		free(tmp);
		if (!dstr->str)
			return (-1);
	}
	ptr = dstr->str + i;
	ft_memmove(ptr + len, ptr, ft_strlen(ptr) + 1);
	ft_memcpy(ptr, str, len);
	dstr->len += len;
	return (len);
}
