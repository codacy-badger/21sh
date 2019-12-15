/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 23:49:26 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/15 08:53:14 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

typedef struct s_token t_token;

typedef struct s_ast 
{
	t_node			*node;
	struct s_ast	*next;
	bool			run_in_background;
} t_ast;


int		parse(t_list_head *tok_list);
t_token	*token(t_list_head *tok_list);
void	print_ast(t_node *ast);
bool	all_tokens_used(t_list_head *tok_list);
t_node	*io_redirect(t_list_head **tok_list);
t_node	*pipeline(t_list_head **tok_list);

#endif
