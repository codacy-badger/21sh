/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:18:07 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 19:43:30 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

int			ft_node_new(void *data)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (ALLOC_ERROR);
	node->data = data;
	node->nb_children = 0;
	node->capacity = 0;
	node->child = NULL;
	return (0);
}

static int	ft_node_realloc(t_node *node)
{
	t_node	**child_new;
	int		i;

	child_new = malloc(sizeof(t_node **) * node->capacity * 2);
	if (child_new == NULL)
		return (ALLOC_ERROR);
	node->capacity *= 2;
	i = 0;
	while (i < node->nb_children)
	{
		child_new[i] = node->child[i];
		i++;
	}
	free(node->child);
	node->child = child_new;
	return (0);
}

int			ft_node_add_child(t_node *parent, t_node *child)
{
	if (parent->child == NULL)
	{
		parent->child = malloc(sizeof(t_node *) * 2);
		if (parent->child == NULL)
			return (ALLOC_ERROR);
		parent->capacity = 2;
	}
	else if (parent->capacity == parent->nb_children)
	{
		if (ft_node_realloc(parent) == ALLOC_ERROR)
			return (ALLOC_ERROR);
	}
	parent->child[parent->nb_children++] = child;
	return (0);
}
