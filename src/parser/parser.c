/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:46:45 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/16 21:20:43 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#define PARSE_ERROR 20

t_token	*node_token(t_node *node)
{
	return (node->data);
}

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

int		traverse_ast(t_node *ast, t_env *env)
{
	int		i;

	if (ast->data == NULL)
		return (exec_command(get_argv(ast, env), env));
	else if (((t_token *)ast->data)->type == PIPE)
		return (exec_pipe(ast, env));
	i = 0;
	while (i < ast->nb_children)
		traverse_ast(ast->child[i++], env);
	return (1);
}

int		parse(t_list_head *tok_list, t_env *env)
{
	t_ast	*ast;
	char	**argv;

	ast = get_ast(&tok_list);
	if (ast == NULL)
		return (PARSE_ERROR);
	while (ast != NULL)
	{
		//printf("AST:\n");
		//print_ast(ast->node);
		traverse_ast(ast->node, env);
		ast = ast->next;
	}
	return (0);
}
