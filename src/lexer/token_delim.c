/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_delim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:45:49 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:46:23 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
static void	set_operator_type(t_lexer *lexer)
{
	char	*ope;
	char	*prev_tok;

	ope = lexer->curr_tok->content->str;
	lexer->curr_tok->type = get_operator_type(ope);
	if (is_operator_redir(lexer->curr_tok) && lexer->prev_tok)
	{
		prev_tok = lexer->prev_tok->content->str;
		if (!ft_isblank(lexer->prev_sep) && ft_strisnbr(prev_tok))
			lexer->prev_tok->type = IO_NUMBER;
	}
}

void		token_delim(t_lexer *lexer, char **str)
{
	if (lexer->qstatus)
		return ;
	lexer->curr_tok->delimited = true;
	if (is_operator_start(*lexer->curr_tok->content->str))
		set_operator_type(lexer);
	//else if (is NAME, ASSIGMENT)
	//	do great stuff
	lexer->prev_sep = **str;
}
*/