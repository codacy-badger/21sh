/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trie_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 00:10:15 by nbousset          #+#    #+#             */
/*   Updated: 2019/10/31 07:55:07 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

t_trie	*ft_trie_add(t_trie *trie, char *word, void *ptr)
{
	t_trie	*node;
	t_uint8	*uword;

	node = trie;
	uword = (t_uint8 *)word;
	if (!trie || !word)
		return (NULL);
	if (ft_trie_contains(trie, word))
		return (0);
	while (*(uword + 1))
	{
		if (!(node->next[*uword]))
		{
			if (!(node->next[*uword] = ft_trie_new(*uword, NULL)))
				return (NULL);
			node->next[*uword]->parent = node;
		}
		node = node->next[*uword];
		uword++;
	}
	if (!(node->next[*uword] = ft_trie_new(*uword, ptr)))
		return (NULL);
	node->next[*uword]->parent = node;
	node->next[*uword]->is_word = 1;
	return (node->next[*uword]);
}
