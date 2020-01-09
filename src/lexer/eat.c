/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/09 19:26:04 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** In case of line continuation or quotes, we set a boolean in input,
** to tell readline that it must not create a new line and not reset
** the input index. this boolean will be reset to false by input/enter()
** function.
** We reset the state and send preprocess to check for line continuation.
*/

static int	get_input(t_lexer *lexer)
{
	int		i;

	i = 0;
	if ((lexer->state & LINE_CONT) || lexer->quote)
	{
		i = lexer->str - lexer->inputp->line->str;
		lexer->inputp->line_cont = true;
	}
	readline(lexer->inputp);
	lexer->str = &lexer->inputp->line->str[i];
	lexer->state &= ~(LINE_CONT | START);
	return (0);
}

/*
** If the previous token was delimited, we set curr_tok to NULL,
** otherwise we ll append to the curr_tok
*/

static int	init_state(t_lexer *lexer)
{
	lexer->state &= ~END;
	if (lexer->state & DELIMITED)
	{
		lexer->curr_tok = NULL;
		lexer->state &= ~DELIMITED;
	}
	if ((lexer->state & (START | LINE_CONT)) || lexer->quote)
		get_input(lexer);
	return (0);
}

/*
** We set appropriate states, we get input if needed,
** we tokenize until a token has been delimited or end is reached.
** If a token has been delimited, we return the type,
** else if LINE_CONT was set or the quotes are not closed, we
** return eat() to delimit the token, otherwise there is no token left
** and we return 0
*/

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
	if ((lexer->state & LINE_CONT) || lexer->quote)
		return (eat(lexer));
	else if (lexer->state & DELIMITED)
		return (lexer->curr_tok->type);
	return (reset_lexer(lexer));
}
