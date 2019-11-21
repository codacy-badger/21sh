/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_dstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 23:03:31 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/21 23:06:12 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

t_dstr		*new_dstr(const char c)
{
	t_dstr *str;

	str = malloc(sizeof(t_dstr));
	str->str = ft_memalloc(4 * sizeof(char));
	str->str[0] = c;
	str->len = 1;
	str->capacity = 4;
	return (str);
}
