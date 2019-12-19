/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:00 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t  get_quote_len(char *str, char quote)
{
    size_t  len;

    len = 0;
    while (*str && *str != quote)
    {
        len++;
        str++;
    }
    return (len + 1);
}

/*
** We just set the quote state and set the length of the quoted field.
** The length will be decreased each time we append a character to the token.
** When its zero, we reset the quote state to NONE.
** +1 are to include the quotes.
*/
int     quote(t_lexer *lexer)
{
    if (lexer->quote_len)
        return (0);
    else if (*lexer->str == BSLASH)
    {
        lexer->quote = BSLASH;
        lexer->quote_len = 2;
        return (1);
    }
    else if (*lexer->str == SQUOTE)
    {
        lexer->quote = SQUOTE;
        lexer->quote_len = get_quote_len(lexer->str + 1, SQUOTE) + 1;
        return (1);
    }
    else if (*lexer->str == DQUOTE)
    {
        lexer->quote = DQUOTE;
        lexer->quote_len = get_quote_len(lexer->str + 1, DQUOTE) + 1;
        return (1);
    }
    return (0);
}
