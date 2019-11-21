/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hentrydel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:27:46 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/12 19:41:15 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_hentrydel(t_hentry **ahentry)
{
	if (!ahentry || !*ahentry)
		return ;
	if ((*ahentry)->type == CPY)
		ft_memdel((void *)&(*ahentry)->value);
	ft_memdel((void *)&(*ahentry)->key);
	(*ahentry)->head = NULL;
	(*ahentry)->prev = NULL;
	(*ahentry)->next = NULL;
	ft_memdel((void *)ahentry);
}
