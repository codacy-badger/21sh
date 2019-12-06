/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:00 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int  preprocess(t_input *input)
{
    t_line  *line;
    int     k_eol;
    char    *eol;

    line = input->line;
    eol = &line->str[line->len - 1];
    k_eol = input->keys[K_EOL]; //handle eof ?
    if (line->len == 1)
        return (0);
    if (*eol == k_eol && *(--eol) == BACKSLASH)
    {
        ft_strremove(eol, 2);
        input_add_line(input); //add new line to the list and change the prompt
        return (LEX_NO_EOL);
    }
    /*
    ** do other preprocessing stuff if necessary
    */
    return (0);
}

int         lexer_tokenize(t_lexer *lexer, t_input *input, t_term *term)
{
    int     ret;

    if ((ret = preprocess(input)) != 0)
        return (ret);
    /*
    ** start tokenization,
    **      function table, with one function for each token type,
    **          in same order as grammar rules
    **      while (*str)
    **          for each functions in table
    **              function(&str)
    **              {
    **                  if char does not correspond to the function, do nothing
    **                  else, add token list &&
    **                         move ptr to next token &&
    **                            && function table index = 0
    **              }
    */

    /********debug**********/
    t_line *line;
    line = input->line;
    while (line->next)
        line = line->next;
    while (line)
    {
        printf("%s", line->str);
        line = line->prev;
    }
    /******************/
    input_reset(term, input);
    return (0);
}
