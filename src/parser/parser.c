/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:46:45 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/21 17:49:18 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#define PARSE_ERROR 20

int		g_parse_error;
char	*g_error_near = NULL;
t_node	g_heredocs = (t_node){NULL, 0, 0, NULL};

t_token	*node_token(t_node *node)
{
	return ((t_token *)node->data);
}

/*
**	and_or         : pipeline and_or_list
**
**	returns and_or in this format :
**	ex:           ls && cat || ls && cat:
**
**                            "&&"
**                            /  \
**						   "||"   cat
**                         /  \
**						"&&"   ls
**                      /  \
**                    ls   cat
**
*/

t_node	*and_or_list(t_lexer *lexer, t_node *left_pipeline)
{
	t_node	*and_or;
	t_node	*right_pipeline;

	and_or = NULL;
	if (lexer->curr_tok == NULL || g_parse_error != NOERR)
		return (left_pipeline);
	if (lexer->curr_tok->type == AND_IF
	|| lexer->curr_tok->type == OR_IF)
	{
		and_or = ft_node_new(lexer->curr_tok);
		eat(lexer);
		ft_node_add_child(and_or, left_pipeline);
		while ((right_pipeline = pipeline(lexer)) == NULL
				&& g_parse_error != SILENT_ABORT)
		{
			lexer->and_or = true;
			eat(lexer);
		}
		lexer->and_or = false;
		ft_node_add_child(and_or, right_pipeline);
		and_or = and_or_list(lexer, and_or);
	}
	return (and_or ? and_or : left_pipeline);
}

t_node	*and_or(t_lexer *lexer)
{
	t_node	*left_pipeline;

	if (g_parse_error != NOERR)
		return (NULL);
	left_pipeline = pipeline(lexer);
	if (left_pipeline == NULL)
	{
		if (g_parse_error == 0)
		{
			g_parse_error = NO_CMD_BEFORE_AND_OR;
			if (lexer->curr_tok)
				g_error_near = ft_strdup(lexer->curr_tok->value->str);
		}
		return (NULL);
	}
	return (and_or_list(lexer, left_pipeline));
}

t_ast	*get_ast(t_lexer *lexer)
{
	t_ast	*ast;

	if (g_parse_error != 0)
		return (NULL);
	if (lexer->curr_tok->type == AMPERSAND || lexer->curr_tok->type == SEMI)
	{
		g_error_near = ft_strdup(lexer->curr_tok->value->str);
		token_del((void **)&lexer->curr_tok, NULL);
		eat(lexer);
		g_parse_error = NO_CMD_BEFORE_SEP;
		return (NULL);
	}
	ast = ft_xmalloc(sizeof(t_ast));
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
/*
 **	ex:           ls && cat || ls && cat:
 **
 **                            "&&"
 **                            /  \
 **						   "||"   cat
 **                         /  \
 **						"&&"   ls
 **                      /  \
 **                    ls   cat
 */

int		traverse_ast(t_node *node, t_env *env)
{
	int			i;

	if (node == NULL)
		return (1);
	else if (node->data == NULL)
	{
		expand(node, env);
		return (exec_command(node, env));
	}
	else if (((t_token *)node->data)->type == PIPE)
		return (exec_pipe(node, env));
	else if (((t_token *)node->data)->type == AND_IF)
	{
		if (traverse_ast(node->child[0], env) == 0)
			return (traverse_ast(node->child[1], env));
		return (1);
	}
	else if (((t_token *)node->data)->type == OR_IF)
	{
		if (traverse_ast(node->child[0], env) != 0) 
			return (traverse_ast(node->child[1], env));
		return (0);
	}
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

	if ((lexer->state & START))
		eat(lexer);
	if (lexer->curr_tok == NULL)
		return (0);
	g_parse_error = NOERR;
	ast = get_ast(lexer);
	if (!(lexer->state & START) && (!(lexer->state & END) || lexer->curr_tok != NULL))
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
			get_all_heredocs(lexer->inputp, &g_heredocs, env);
			if (g_parse_error != SILENT_ABORT)
			{
				tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->oldterm);
				traverse_ast(ast->node, env);
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
