/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 21:32:58 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** I need to find more elegant way to handle operators, but for the moment,
** it works. I will think about it...
*/
static int	get_token_type(t_lexer *lexer)
{
	if (!lexer->curr_tok)
		return (END);
	if (is_operator_start(*lexer->curr_tok->value->str))
	{
		lexer->curr_tok->type = get_operator_type(lexer->curr_tok->value->str);
		if (is_redir(lexer->curr_tok) && !ft_iswhitespace(lexer->oldsep)
		&& ft_strisnbr(lexer->prev_tok->value->str))
			lexer->prev_tok->type = IO_NUMBER;
	}
	return (lexer->curr_tok->type);
}

static void	reset_lexer(t_lexer *lexer)
{
	lexer->state = START;
	lexer->str = NULL;
	lexer->curr_tok = NULL;
	lexer->prev_tok = NULL;
	lexer->oldchar = 0;
	lexer->oldsep = 0;
	lexer->quote = 0;
	lexer->quote_len = 0;
}

static int	init_state(t_lexer *lexer)
{
	lexer->state &= ~END;
	if ((lexer->state & (START | LINE_CONT)) || lexer->quote)
	{
		if (lexer->state & LINE_CONT)
		{
			lexer->inputp->line_cont = true;
			lexer->state &= ~LINE_CONT;
		}
		draw_prompt(lexer->inputp);
		readline(lexer->inputp);
		lexer->str = lexer->inputp->line->str;
		if (lexer->quote)
			lexer->quote_len = get_quote_len(lexer->str, lexer->quote);
		lexer->state &= ~START;
	}
	if (lexer->state & DELIMITED)
	{
		lexer->prev_tok = lexer->curr_tok;
		lexer->curr_tok = NULL;
		lexer->state &= ~DELIMITED;
	}
	return (0);
}

int			eat(t_lexer *lexer)
{
	init_state(lexer);
	while (!(lexer->state & (DELIMITED | END)))
	{
		if (end(lexer)
		|| operator_next(lexer)
		|| operator_end(lexer)
		|| quote(lexer)
		|| operator_new(lexer)
		|| blank(lexer)
		|| word_next(lexer)
		|| comment(lexer)
		|| word_start(lexer))
			continue ;
	}
	if (lexer->curr_tok && (lexer->state & DELIMITED))
		return (get_token_type(lexer));
	else if ((lexer->state & LINE_CONT) || lexer->quote)
		return (eat(lexer));
	reset_lexer(lexer);
	return (END);
}
