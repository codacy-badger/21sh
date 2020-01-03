/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:46:45 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/03 15:54:46 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#define PARSE_ERROR 20

t_token	*node_token(t_node *node)
{
	return (node->data);
}

t_node	*and_or(t_lexer *lexer)
{
	return (pipeline(lexer));
}

t_ast	*get_ast(t_lexer *lexer)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	ast->next = NULL;
	ast->node = and_or(lexer);
	if (lexer->curr_tok == NULL)
	{
		ast->run_in_background = false;
		return (ast);
	}
	ast->run_in_background = (lexer->curr_tok->type == AMPERSAND);
	if (lexer->curr_tok->type == AMPERSAND || lexer->curr_tok->type == SEMI)
	{
		eat(lexer);
		token_del((void **)&lexer->prev_tok, NULL);
		if (lexer->curr_tok != NULL && !ft_strequ(lexer->curr_tok->value->str, "\n"))
			ast->next = get_ast(lexer);
	}
	return (ast);
}

/*
**	depth first tree traversal
**	if we encounter a command or a pipe node, stop traversing and execute it.
**	for now, this function actually always stops at the first call.
*/

int		traverse_ast(t_node *node, t_env *env)
{
	int		i;

	if (node == NULL)
		return (1);
	if (node->data == NULL)
		return (exec_command(node, env));
	else if (((t_token *)node->data)->type == PIPE)
		return (exec_pipe(node, env));
	i = 0;
	while (i < node->nb_children)
		traverse_ast(node->child[i++], env);
	return (1);
}

/*
**	gets the list of ASTs for the input, then executes all of them sequentially.
**	ex: the input "ls ; cat; wc" gets a list of 3 asts
**	asts are trees containing t_tokens in their "data" fields.
**	one node can have an infinite number of children.
*/

int		parse(t_lexer *lexer, t_env *env)
{
	t_ast *ast;

	eat(lexer);
	ast = get_ast(lexer);
	//if (eat(lexer) != 0)
	//	error
	if (ast == NULL)
		return (PARSE_ERROR);
	while (ast != NULL && ast->node != NULL)
	{
		traverse_ast(ast->node, env);
		ast = ast->next;
	}
	return (0);
}
