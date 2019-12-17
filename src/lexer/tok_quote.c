/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:00 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int  tok_squote(t_lexer *lexer)
{
    if (lexer->qstatus == NONE)
        lexer->qstatus = SQUOTE;
    else if (lexer->qstatus == SQUOTE)
        lexer->qstatus = NONE;
    return (0);
}

static int  tok_dquote(t_lexer *lexer)
{
    if (lexer->qstatus == NONE)
        lexer->qstatus = DQUOTE;
    else if (lexer->qstatus == DQUOTE)
        lexer->qstatus = NONE;
    return (0);
}

static int  tok_escape(t_lexer *lexer)
{
    if (lexer->qstatus == NONE)
        lexer->qstatus = BSLASH;
    return (0);
}

int         tok_quote(void *lex, char **str)
{
    t_lexer *lexer;

	lexer = (t_lexer *)lex;
    if (**str == '\\')
        return (tok_escape(lexer));
    else if (**str == '\'')
        return (tok_squote(lexer));
    else if (**str == '"')
        return (tok_dquote(lexer));
    return (0);
}