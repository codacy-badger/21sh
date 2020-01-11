/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 20:03:18 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/07 20:41:19 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	get_and_output_heredoc(t_lexer *lexer, t_node *op_node)
{
	lexer->docdelim = node_token(op_node->child[1])->value->str;
	eat(lexer);
	printf("doc:%s\n", lexer->curr_tok->value->str);
	fflush(stdout);
	token_del((void **)&lexer->curr_tok, NULL);
}
