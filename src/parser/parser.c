/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:46:45 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/03 15:14:24 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#define PARSE_ERROR 20

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

int		parse(t_lexer *lexer)
{
	t_ast *ast;

	eat(lexer);
	ast = get_ast(lexer);
	//if (eat(lexer) != 0)
	//	error
	if (ast == NULL)
		return (PARSE_ERROR);
	while (ast != NULL)
	{
		printf("AST:\n");
		print_ast(ast->node, 0);
		ast = ast->next;
	}
	return (0);
}
