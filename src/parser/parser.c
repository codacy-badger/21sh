/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:46:45 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/11 18:46:03 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#define PARSE_ERROR 20

int		g_parse_error;
char	*g_error_near = NULL;
t_node	g_heredocs = (t_node){NULL, 0, 0, NULL};

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

	if (g_parse_error != 0)
		return (NULL);
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

int		traverse_ast(t_node *node, t_env *env, t_lexer *lexer)
{
	int		i;

	if (node == NULL)
		return (1);
	if (node->data == NULL)
	{
		expand(node, env);
		return (exec_command(node, env, lexer));
	}
	else if (((t_token *)node->data)->type == PIPE)
		return (exec_pipe(node, env, lexer));
	i = 0;
	while (i < node->nb_children)
		traverse_ast(node->child[i++], env, lexer);
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

	if ((lexer->state & START))
		eat(lexer);
	if (lexer->curr_tok == NULL)
		return (0);
	g_parse_error = NOERR;
	ast = get_ast(lexer);
	if (!(lexer->state & START) && !(lexer->state & END))
	{
		g_parse_error = (g_parse_error == NOERR) ? TOKENS_LEFT : g_parse_error;
		token_del((void **)&lexer->curr_tok, NULL);
		while (eat(lexer) != END_OF_INPUT)
			token_del((void **)&lexer->curr_tok, NULL);
	}
	if (ast == NULL && g_parse_error == NOERR)
		g_parse_error = NULL_AST;
	while (ast != NULL)
	{
		if (ast->node == NULL && g_parse_error == NOERR)
			g_parse_error = NULL_AST_NODE;
		if (g_parse_error == NOERR)
		{
			get_all_heredocs(lexer->inputp, &g_heredocs);
			if (g_parse_error != SILENT_ABORT)
			{
				tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->oldterm);
				traverse_ast(ast->node, env, lexer);
				tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->newterm);
				tputs(term->caps[C_KS], 1, ft_putc);
			}
		}
		free_ast_nodes(ast->node);
		tmp = ast;
		ast = ast->next;
		free(tmp);
	}
	if (g_parse_error > 0)
		printf("21sh: parse error near '%s' errno:%d\n", g_error_near, g_parse_error);
	free(g_error_near);
	g_error_near = NULL;
	return (0);
}
