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

/*
** -str is the string you want to add to the dstr on creation.
**  Just pass "" for an empty string.
** -length is the number of bytes you want to copy from the string.
** -size is the size you want for the dstr, it avoids to create
**  a dstr of 1 then realloc if you know you will need more space.
** -if len is more than string length, we reduce it to the string length
**  to avoid segfault.
** -if len is more than size, size is increased to have enough space.
**  size is rounded to next power of two cause it s cool.
*/

t_dstr		*ft_dstr_new(char *str, size_t len, size_t size)
{
	t_dstr	*dstr;
	size_t	cmp;

	if (!str)
		return (NULL);
	if (!(dstr = (t_dstr *)ft_memalloc(sizeof(t_dstr))))
		return (NULL);
	if ((cmp = ft_strlen(str)) < len)
		len = cmp;
	if (size - 1 < len)
		size = ft_next_power_of_two(len + 1);
	else
		size = ft_next_power_of_two(size);
	if (!(dstr->str = (char *)ft_memalloc(size)))
	{
		free(dstr);
		return (NULL);
	}
	ft_memcpy(dstr->str, str, len);
	dstr->size = size;
	dstr->len = len;
	return (dstr);
}
