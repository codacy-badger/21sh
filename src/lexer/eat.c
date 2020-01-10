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

static int	get_input(t_lexer *lexer)
{
	int		i;
	int 	count;

	i = 0;
	count = 0;
	if ((lexer->state & LINE_CONT) || lexer->quote)
	{
		i = lexer->str - lexer->inputp->line->str;
		lexer->inputp->line_cont = true;
	}
	readline(lexer->inputp);
	lexer->str = &lexer->inputp->line->str[i];
	lexer->state &= ~(LINE_CONT | START);
	if (lexer->docdelim)
	{
		i = lexer->inputp->line->len - 1;
		while (lexer->inputp->line->str[--i] == BSLASH)
			count++;
		if (count % 2)
		{
			lexer->state |= LINE_CONT;
			ft_dstr_remove(lexer->inputp->line, lexer->inputp->line->len - 2, 2);
			lexer->inputp->pos -= 2;
		}
	}
	else
		lexer->len = lexer->inputp->line->len;
	return (0);
}

static int	get_heredoc(t_lexer *lexer)
{
	char	*oldstr;
	size_t	cmpi;
	size_t	cmplen;
	size_t	delimlen;

	delimlen = ft_strlen(lexer->docdelim);
	oldstr = lexer->str;
	lexer->docptr = lexer->docptr ? lexer->docptr : &lexer->str[lexer->len];
	while (!(lexer->state & DELIMITED))
	{
		cmpi = lexer->docptr - lexer->inputp->line->str;
		while ((!*(lexer->docptr = &lexer->inputp->line->str[cmpi])
		|| (lexer->state & LINE_CONT)) && (lexer->inputp->line_cont = true))
			get_input(lexer);
		if (!((cmplen = ft_strchr(lexer->docptr, '\n') - lexer->docptr) == delimlen
		&& ft_strnequ(lexer->docptr, lexer->docdelim, cmplen)
		&& (lexer->state |= DELIMITED)))
			ft_dstr_insert(lexer->curr_tok->value, lexer->curr_tok->value->len,
			lexer->docptr, cmplen + 1);
		lexer->docptr += cmplen + 1;
	}
	return ((lexer->str = oldstr) && (lexer->docdelim = NULL));
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
	else if (lexer->docdelim && (lexer->curr_tok = token_new(WORD))) //check
		get_heredoc(lexer);
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
	if (lexer->state & DELIMITED)
		return (*lexer->curr_tok->value->str
		? lexer->curr_tok->type : eat(lexer));
	else if ((lexer->state & LINE_CONT) || lexer->quote)
		return (eat(lexer));
	lexer->curr_tok = NULL;
	return (reset_lexer(lexer));
}
