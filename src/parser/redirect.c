/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 04:05:12 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/02 17:55:25 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_node	*filename(t_lexer *lexer)
{
	t_node *node;

	if (lexer->curr_tok== NULL)
		return (NULL);
	node = NULL;
	//expand filename here ?
	if (lexer->curr_tok->type == WORD)
	{
		node = ft_node_new(lexer->curr_tok);
		eat(lexer);
	}
	return (node);
}

static t_node	*io_file(t_lexer *lexer, t_token *io_number)
{
	t_node		*node;
	t_node		*tmp;

	if (lexer->curr_tok == NULL)
		return (NULL);
	node = NULL;
	if (is_redir(lexer->curr_tok))
	{
		node = ft_node_new(lexer->curr_tok);
		eat(lexer);
		//(*token_list) = (*token_list)->next;
		tmp = ft_node_new(io_number);
		ft_node_add_child(node, tmp);
		ft_node_add_child(node, filename(lexer));
	}
	return (node);
}

t_node			*io_redirect(t_lexer *lexer)
{
	t_token *io_number;

	if (lexer->curr_tok == NULL)
		return (NULL);
	if (lexer->curr_tok->type == IO_NUMBER)
	{
		io_number = lexer->curr_tok;
		eat(lexer);
		return (io_file(lexer, io_number));
	}
	return (io_file(lexer, NULL));
}
