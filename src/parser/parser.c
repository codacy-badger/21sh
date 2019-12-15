/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:46:45 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/15 08:53:15 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#define PARSE_ERROR 20


t_node	*and_or(t_list_head **tok_list)
{
	return (pipeline(tok_list));
}

t_ast	*get_ast(t_list_head **tok_list)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (ast == NULL)
		return (NULL);
	ast->node = and_or(tok_list);
	ast->run_in_background = (token(*tok_list)->type == AMPERSAND);
	if (token(*tok_list)->type == AMPERSAND || token(*tok_list)->type == SEMI)
	{
		(*tok_list) = (*tok_list)->next;
		if (token(*tok_list)->type != END)
			ast->next = get_ast(tok_list);
		else
			ast->next = NULL;
	}
	return (ast);
}

int		parse(t_list_head *tok_list)
{
	t_ast *ast;

	ast = get_ast(&tok_list);
	if (ast == NULL)
		return (PARSE_ERROR);
	while (ast != NULL)
	{
		printf("AST:\n");
		print_ast(ast->node);
		ast = ast->next;
	}
	return (0);
}
