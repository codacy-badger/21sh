/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 04:05:12 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/05 16:58:27 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_parse_error;
extern char	*g_error_near;

/*
**	filename         : WORD
*/

static t_node	*filename(t_lexer *lexer)
{
	t_node *node;

	if (lexer->curr_tok == NULL || g_parse_error != 0)
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

/*
**  io_file          : '<'       filename
**                   | LESSAND   filename
**                   | '>'       filename
**                   | GREATAND  filename
**                   | DGREAT    filename
**                   | LESSGREAT filename
**                   ;
**
**	the io_number is added as child 0 of the redirect node, and the output is
**	added as child 1
**	example:               2> file.txt
**
**                           >
**                          / \
**                         2  file.txt
**
**  if there is no input file descriptor, the input node's data is set to NULL
**	like a command node (not ideal)
*/

static t_node	*io_file(t_lexer *lexer, t_token *io_number)
{
	t_node		*node;
	t_node		*filename_node;

	if (lexer->curr_tok == NULL || g_parse_error != 0)
		return (NULL);
	node = NULL;
	if (is_redir(lexer->curr_tok))
	{
		node = ft_node_new(lexer->curr_tok);
		eat(lexer);
		filename_node = filename(lexer);
		if (filename_node == NULL)
		{
			if (g_parse_error == 0)
			{
				g_parse_error = 4;
				g_error_near = ft_strdup(node_token(node)->value->str);
			}
			free_ast_nodes(node);
			return (NULL);
		}
		ft_node_add_child(node, ft_node_new(io_number));
		ft_node_add_child(node, filename_node);
	}
	return (node);
}

t_node			*io_redirect(t_lexer *lexer)
{
	t_token *io_number;

	if (lexer->curr_tok == NULL || g_parse_error != 0)
		return (NULL);
	if (lexer->curr_tok->type == IO_NUMBER)
	{
		io_number = lexer->curr_tok;
		eat(lexer);
		return (io_file(lexer, io_number));
	}
	return (io_file(lexer, NULL));
}
