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

/*
** We have to get term struct each time we want to get a key,
** which is really annoying.
*/

static int  preprocess(t_input *input)
{
    t_line  *line;
    char    *eol;

    line = input->line;
    eol = &line->str[line->len - 1];
    if (line->len == 1)
        return (0);
    if (*eol == '\n' && *(--eol) == BACKSLASH)
    {
        ft_strremove(eol, 2);
        //input_add_line()
        line_add(&input->line, line_new(32), 1);
        input->prompt = input->shell->data.prompts[PS2];
        return (LEX_NO_EOL);
    }
    return (0);
}

int         lexer_tokenize(t_lexer *lexer, t_input *input)
{
    int     ret;

    if ((ret = preprocess(input)) != 0)
        return (ret);
    
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
    input_reset(input);
    return (0);
}