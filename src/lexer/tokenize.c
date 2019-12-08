/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:09:52 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:00 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/* *********************************UTILS************************************ */

bool            ft_strisnbr(char *str) //libft
{
    while (*str)
    {
        if (!ft_isdigit(*str++))
            return (false);
    }
    return (true);
}

bool			is_operator_start(char c)
{
	return (c == '<' || c == '>' || c == '&' || c == ';' || c == '|');
}

bool			is_operator(char c)
{
    return ((is_operator_start(c)) || c == '-');
}

bool			is_operator_next(char *ope, char c)
{
    /*
    ** A trie containing operators would be far more elegant, but i m too lazy.
    */
    if (is_operator(c))
    {
        if (c == '<')
            return (ft_strequ(ope, "<"));
        else if (c == '>')
            return (ft_strequ(ope, "<") || ft_strequ(ope, ">"));
        else if (c == '&')
            return (ft_strequ(ope, "<") || ft_strequ(ope, ">") || ft_strequ(ope, "&"));
        else if (c == '|')
            return (ft_strequ(ope, "|"));
        else if (c == '-')
            return (ft_strequ(ope, "<<"));
    }
    return (0);
}

int             get_operator_type(char *ope)
{
    if (ft_strequ(ope, "<<"))
        return (DLESS);
    else if (ft_strequ(ope, ">>"))
        return (DGREAT);
    else if (ft_strequ(ope, "<&") || ft_strequ(ope, "<"))
        return (LESSAND);
    else if (ft_strequ(ope, ">&") || ft_strequ(ope, ">"))
        return (GREATAND);
    else if (ft_strequ(ope, "<>"))
        return (LESSGREAT);
    else if (ft_strequ(ope, "<<-"))
        return (DLESSDASH);
    else if (ft_strequ(ope, "&"))
        return (AMPERSAND);
    else if (ft_strequ(ope, "&&"))
        return (AND_IF);
    else if (ft_strequ(ope, "|"))
        return (PIPE);
    else if (ft_strequ(ope, "||"))
        return (OR_IF);
    else if (ft_strequ(ope, ";"))
        return (SEMI);
    return (NONE);
}

bool			is_quote(char c)
{
	return (c == '\\' || c == '\"' || c == '\'');
}

/* ************************Tokenization functions****************************** */

int     tok_end(t_lexer *lexer, char **str)
{
    int     ret;

    if (**str == '\0')
    {
        if (lexer->curr_tok->type == NONE)
            lexer->curr_tok->type = END;
        else if ((ret = add_token(lexer, END)) < 0)
            return (ret);
        return (1);
    }
    return (0);
}

int     tok_ope(t_lexer *lexer, char **str)
{
    int     ret;

    if (is_operator_start(**str))
    {
        if (lexer->curr_tok->type != NONE
            && (ret = add_token(lexer, NONE)) < 0)
            return (ret);
        ft_dstr_add(&lexer->curr_tok->content, *(*str)++);
        while (is_operator_next(lexer->curr_tok->content->str, **str))
            ft_dstr_add(&lexer->curr_tok->content, *(*str)++);
        lexer->curr_tok->type = get_operator_type(lexer->curr_tok->content->str);
        if (DLESS <= lexer->curr_tok->type && lexer->curr_tok->type <= DLESSDASH
            && ft_strisnbr(lexer->prev_tok->content->str))
            lexer->prev_tok->type = IO_NUMBER;
        return (1);
    }
    return (0);
}

int     tok_eol(t_lexer *lexer, char **str)
{
    int     ret;

    if (**str == '\n')
    {
        if (lexer->curr_tok->type == NONE)
            lexer->curr_tok->type = NEWLINE;
        else if ((ret = add_token(lexer, NEWLINE)) < 0)
            return (ret);
        ft_dstr_add(&lexer->curr_tok->content, **str); //not neccessary ?
        (*str)++;
        return (1);
    }
    return (0);
}

int     tok_spc(t_lexer *lexer, char **str)
{
    int     ret;

    if (**str == ' ')
    {
        if ((ret = add_token(lexer, NONE)) != 0)
            return (ret);
        while (**str == ' ')
            (*str)++;
        return (1);
    }
    return (0);
}

/*--------------------------------------*/

static int  tok_sqte(t_lexer *lexer, char **str)
{
    ft_dstr_add(&lexer->curr_tok->content, *(*str)++);
    while (**str && **str != '\'')
        ft_dstr_add(&lexer->curr_tok->content, *(*str)++);
    ft_dstr_add(&lexer->curr_tok->content, *(*str)++);
    return (1);
}

static int  tok_dqte(t_lexer *lexer, char **str)
{
    ft_dstr_add(&lexer->curr_tok->content, *(*str)++);
    while (**str && **str != '"')
        ft_dstr_add(&lexer->curr_tok->content, *(*str)++);
    ft_dstr_add(&lexer->curr_tok->content, *(*str)++);
    return (1);
}

static int  tok_escp(t_lexer *lexer, char **str)
{
    if (*(*str + 1) != '\n')
    {
        ft_dstr_add(&lexer->curr_tok->content, **str);
        ft_dstr_add(&lexer->curr_tok->content, *(*str + 1));
    }
    (*str) += 2;
    return (1);
}

static int  tok_qte(t_lexer *lexer, char **str)
{
    if (**str == '\\')
        return (tok_escp(lexer, str));
    else if (**str == '\'')
        return (tok_sqte(lexer, str));
    else if (**str == '"')
        return (tok_dqte(lexer, str));
    return (0);
}

int         tok_wrd(t_lexer *lexer, char **str)
{
    int     ret;

    if (**str)
    {
        if (lexer->curr_tok->type == NONE)
            lexer->curr_tok->type = WORD;
        else if (lexer->curr_tok->type != WORD 
            && (ret = add_token(lexer, WORD)) < 0)
            return (ret);
        if (is_quote(**str))
            return (tok_qte(lexer, str));
        ft_dstr_add(&lexer->curr_tok->content, *(*str)++);
        return (1);
    }
    return (0);
}

/*--------------------------------------*/

/* ************************************************************************** */

int     add_token(t_lexer *lexer, int type)
{
    if (lexer->prev_tok)
    {
        if (ft_strisnbr(lexer->curr_tok->content->str) &&
            DLESS <= lexer->prev_tok->type && lexer->prev_tok->type <= DLESSDASH)
            lexer->curr_tok->type = IO_NUMBER;
    }
    lexer->prev_tok = lexer->curr_tok;
    if (!(lexer->curr_tok = token_new(type)))
        return (-1);
    ft_list_add_tail(lexer->curr_tok, lexer->tokens);
    return (0);
}

/* ************************************************************************** */

int     tokenize(t_lexer *lexer, t_input *input)
{
    char    *str;
    //int     ret;

    str = input->line->str;
    while (lexer->curr_tok->type != END)
    {
        /*a function table would be cool
        **  i = 0;
        **  while (i < table_size)
        **  {
        **      if ((ret = table[i](lexer, str)) != 0)
        **      {
        **          if (ret < 0)
        **              return (ret);
        **          break ;
        **       }
        **       i++;
        **   }
        */
        if (tok_end(lexer, &str))  //check for errors
            continue ;
        if (tok_ope(lexer, &str))
            continue ;
        if (tok_eol(lexer, &str))
            continue ;
        if (tok_spc(lexer, &str))
            continue ;
        if (tok_wrd(lexer, &str))
            continue ;
    }

    /**************debug*************/    
    t_list_head *list;
    t_token     *token;

    list = lexer->tokens->next;
    while (list != lexer->tokens)
    {
        token = (t_token *)list->data;
        if (token->type == START)
            printf("[%s] -> ", "START");
        else if (ft_strequ(token->content->str, "\n"))
            printf("[%s] -> ", "EOL");
        else if (token->type == END)
            printf("[%s] -> ", "END");
        else
            printf("[%d: %s] -> ", token->type, token->content->str);
        list = list->next;
    }
    printf("%s\n", "NULL");
    /**************debug*************/

    input_reset(input);
    return (0);
}
