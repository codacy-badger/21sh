/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:46:45 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/03 18:18:44 by fratajcz         ###   ########.fr       */
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
		//may cause lexer to crash?
		token_del((void **)&lexer->curr_tok, NULL);
		eat(lexer);
		if (lexer->curr_tok != NULL)
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

int		parse(t_lexer *lexer, t_env *env, t_term *term)
{
	t_ast	*ast;
	t_ast	*tmp;
	bool	error;

	if ((lexer->state & START))
		eat(lexer);
	ast = get_ast(lexer);
	error = false;
	if (!(lexer->state & START) && !(lexer->state & END))
	{
		error = true;
		while (eat(lexer) != END_OF_INPUT)
			;
	}
	if (ast == NULL)
		error = true;
	while (ast != NULL)
	{
		if (ast->node == NULL)
			error = true;
		if (!error)
		{
			tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->oldterm);
			traverse_ast(ast->node, env);
			tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->newterm);
		}
		free_ast_nodes(ast->node);
		tmp = ast;
		ast = ast->next;
		free(tmp);
	}
	free(ast);
	if (error)
		write(2, "parse error\n", 12);
	return (0);
}
