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

static int  tok_squote(t_lexer *lexer, char **str)
{
    ft_dstr_add(&lexer->curr_tok->content, *(*str)++);
    while (**str && **str != '\'')
        ft_dstr_add(&lexer->curr_tok->content, *(*str)++);
    ft_dstr_add(&lexer->curr_tok->content, *(*str)++);
    return (1);
}

static int  tok_dquote(t_lexer *lexer, char **str)
{
    ft_dstr_add(&lexer->curr_tok->content, *(*str)++);
    while (**str && **str != '"')
        ft_dstr_add(&lexer->curr_tok->content, *(*str)++);
    ft_dstr_add(&lexer->curr_tok->content, *(*str)++);
    return (1);
}

static int  tok_escape(t_lexer *lexer, char **str)
{
    if (*(*str + 1) != '\n')
    {
        ft_dstr_add(&lexer->curr_tok->content, **str);
        ft_dstr_add(&lexer->curr_tok->content, *(*str + 1));
    }
    (*str) += 2;
    return (1);
}

int         tok_quote(t_lexer *lexer, char **str)
{
    lexer->prev = **str;
    if (**str == '\\')
        return (tok_escape(lexer, str));
    else if (**str == '\'')
        return (tok_squote(lexer, str));
    else if (**str == '"')
        return (tok_dquote(lexer, str));
    return (0);
}