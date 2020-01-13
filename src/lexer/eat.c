/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/13 19:03:15 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	get_input(t_lexer *lexer)
{
	char		*str;
	char		*tmp;
	const char	*prompt;

	prompt = lexer->quote ? "> " : "$> ";
	lexer->inputp->first_line = (lexer->quote == NONE);
	str = readline(lexer->inputp, prompt);
	if (str == NULL)
		return (0);
	if (lexer->quote)
	{
		tmp = ft_strjoin(lexer->str, str);
		free(lexer->str);
		lexer->str = tmp;
	}
	else
		lexer->str = ft_strdup(str);
	lexer->state &= ~(START);
	lexer->len += lexer->inputp->line->len;
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
	if (lexer->state & START || lexer->quote)
		get_input(lexer);
	return (0);
}

static void	delete_nl(char *str)
{
	char *nl;

	if (str != NULL && (nl = ft_strchr(str, '\n')))
		*nl = '\0';
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
	while (!(lexer->state & (DELIMITED | END)) && lexer->str)
	{
		end(lexer)
		|| operator_next(lexer)
		|| operator_end(lexer)
		|| quote(lexer)
		|| operator_new(lexer)
		|| blank(lexer)
		|| word_next(lexer)
		|| comment(lexer)
		|| word_start(lexer);
	}
	if (lexer->state & DELIMITED)
		return (*lexer->curr_tok->value->str
		? lexer->curr_tok->type : eat(lexer));
	else if (lexer->quote)
		return (eat(lexer));
	lexer->curr_tok = NULL;
	delete_nl(lexer->str);
	if (lexer->str && lexer->str[0] != 0 && lexer->str[0] != ' ')
		ft_lstadd(lexer->inputp->head,
				ft_lstnew(ft_dstr_new(lexer->str, ft_strlen(lexer->str), 1)));
	return (reset_lexer(lexer));
}
