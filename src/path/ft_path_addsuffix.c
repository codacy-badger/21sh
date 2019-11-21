/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_addsuffix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:36:04 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 21:03:29 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_path_addsuffix(const char *path, const char *suffix, char free_old)
{
	size_t	old_len;
	size_t	suff_len;
	size_t	new_len;
	char	*new_path;
	char	sep;

	sep = 0;
	old_len = ft_strlen(path);
	suff_len = ft_strlen(suffix);
	new_len = old_len + suff_len;
	if (*suffix != '/' && path[old_len - 1] != '/')
	{
		new_len++;
		sep = 1;
	}
	if (!(new_path = (char *)ft_memalloc(new_len + 1)))
		return (NULL);
	ft_memcpy((void *)new_path, (void *)path, old_len);
	if (sep)
		new_path[old_len++] = '/';
	ft_memcpy((void *)&new_path[old_len], (void *)suffix, suff_len);
	if (free_old)
		ft_memdel((void *)&path);
	return (new_path);
}
