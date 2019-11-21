/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trie_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 00:10:15 by nbousset          #+#    #+#             */
/*   Updated: 2019/10/31 07:55:07 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_trie_rmv(t_trie *trie, char *word)
{
	t_trie	*entry;

	if (!(entry = ft_trie_get(trie, word)))
		return ;
	entry->is_word = 0;
	entry->ptr = NULL;
}
