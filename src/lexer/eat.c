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

/*
** We want to know if there is line continuation.
** We start by checking if the quote state is set, if it is, we
** get the quoted len for further tokenization, and increase our
** position in the string (not the pointer, just the index) cause
** we want to discard this part, as this part does not affect the
** line continuation.
** We process the rest of the string, and each time we find a quote,
** we set quote var and move to the end of the quoted field, then reset
** quote.
** When we reach the end of the string, if quote is backslash, it means
** that the last character, which is the newline, was escaped.
** In this case we remove the backslash and the newline from the input
** string and set LINE_CONT.
*/
static void	preprocess(t_lexer *lexer)
{
	char	quote;
	int		i;

	i = 0;
	quote = 0;
	if (lexer->quote
	&& (lexer->quote_len = get_quote_len(lexer->str, lexer->quote)))
		i += lexer->quote_len;
	while (lexer->str[i])
	{
		quote = 0;
		if (ft_isquote(lexer->str[i]))
		{
			quote = lexer->str[i];
			i += get_quote_len(&lexer->str[i + 1], quote);
		}
		i++;
	}
	if (quote == BSLASH)
	{
		ft_dstr_remove(lexer->inputp->line, lexer->inputp->line->len - 2, 2);
		lexer->inputp->pos -= 2;
		lexer->state |= LINE_CONT;
	}
}

/*
** In case of line continuation or quotes, we set a boolean in input,
** to tell readline that it must not create a new line and not reset
** the input index. this boolean will be reset to false by input/enter()
** function.
** In case the state is START, we set lexer->str to point on the beginning
** of the new input line, otherwise it is left unchanged, as readline will
** append the input to the current line.
** We reset the state and send preprocess to check for line continuation.
*/
static int	get_input(t_lexer *lexer)
{
	if ((lexer->state & LINE_CONT) || lexer->quote)
		lexer->inputp->line_cont = true;
	draw_prompt(lexer->inputp);
	readline(lexer->inputp);
	if (lexer->state & START)
		lexer->str = lexer->inputp->line->str;
	lexer->state &= ~(LINE_CONT | START);
	preprocess(lexer);
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
		lexer->prev_tok = lexer->curr_tok;
		lexer->curr_tok = NULL;
		lexer->state &= ~DELIMITED;
	}
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
	if ((lexer->state & (START | LINE_CONT)) || lexer->quote)
		get_input(lexer);
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
	if (lexer->state & DELIMITED)
		return (get_token_type(lexer));
	else if ((lexer->state & LINE_CONT) || lexer->quote)
		return (eat(lexer));
	reset_lexer(lexer);
	return (0);
}
