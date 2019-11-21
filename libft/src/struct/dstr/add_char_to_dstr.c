/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char_to_dstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 23:03:42 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/21 23:05:58 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void		add_char_to_dstr(t_dstr **str, char c)
{
	char	*new;

	if (*str == NULL)
		*str = new_dstr(c);
	else if ((*str)->len == (*str)->capacity - 1)
	{
		(*str)->capacity *= 2;
		new = ft_memalloc((*str)->capacity * sizeof(char));
		ft_memcpy(new, (*str)->str, (*str)->len);
		free((*str)->str);
		(*str)->str = new;
		(*str)->str[(*str)->len] = c;
		(*str)->len++;
	}
	else
	{
		(*str)->str[(*str)->len] = c;
		(*str)->len++;
	}
}
