/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 08:48:18 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/15 08:50:25 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token	*token(t_list_head *tok_list)
{
	return (tok_list->data);
}

void	print_ast(t_node *ast)
{
	int i;

	if (ast == NULL)
		return ;
	printf("children:%d ", ast->nb_children);
	if (ast->data != NULL)
		printf("str:%s\n", ((t_token *)ast->data)->content->str);
	else
		printf("NULL\n");
	fflush(stdout);
	if (ast->nb_children > 0)
	{
		i = 0;
		while (i < ast->nb_children)
			print_ast(ast->child[i++]);
	}
}

bool	all_tokens_used(t_list_head *tok_list)
{
	if (token(tok_list)->type == END)
		return (true);
	if (token(tok_list)->type == AMPERSAND || token(tok_list)->type == SEMI)
		return (token(tok_list->next)->type == END);
	return (false);
}

