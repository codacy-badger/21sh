/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trie_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 00:10:15 by nbousset          #+#    #+#             */
/*   Updated: 2019/10/31 07:55:07 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_trie_del(t_trie **trie)
{
	int		i;

	i = 0;
	if (!trie || !*trie)
		return ;
	while (i < 128)
	{
		if ((*trie)->next[i])
			ft_trie_del(&((*trie)->next[i]));
		i++;
	}
	(*trie)->ptr = NULL;
	ft_memdel((void *)trie);
}
