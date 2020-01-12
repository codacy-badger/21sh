/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_getsuffix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:36:04 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 21:03:29 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_path_getsuffix(const char *path, char alloc)
{
	char	*suffix;
	int		len;
	int		i;

	len = 0;
	i = ft_strlen(path) - 1;
	if (path[i] == '/')
	{
		i--;
		len++;
	}
	while (path[i] != '/' && i >= 0)
	{
		i--;
		len++;
	}
	if (alloc)
	{
		if (!(suffix = (char *)ft_xmalloc(len + 1)))
			return (NULL);
		ft_memcpy(suffix, &(path[i + 1]), len);
	}
	else
		suffix = (char *)&(path[i + 1]);
	return (suffix);
}
