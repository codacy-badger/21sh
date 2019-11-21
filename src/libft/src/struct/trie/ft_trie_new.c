/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trie_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 00:10:15 by nbousset          #+#    #+#             */
/*   Updated: 2019/10/31 07:55:07 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

t_trie	*ft_trie_new(char c, void *ptr)
{
	t_trie	*trie;
	int		i;

	i = 0;
	if (!(trie = (t_trie *)ft_memalloc(sizeof(*trie))))
		return (NULL);
	while (i < 128)
		trie->next[i++] = NULL;
	trie->parent = NULL;
	trie->ptr = ptr;
	trie->c = c;
	return (trie);
}
