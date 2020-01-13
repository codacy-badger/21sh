/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 20:03:18 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/13 15:54:27 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_parse_error;

static void	remove_bslash(t_dstr *str)
{
	int i;

	i = 0;
	while (str->str[i])
	{
		if (str->str[i] == '\\')
		{
			if (str->str[i + 1] == '\n')
			{
				ft_dstr_remove(str, i, 2);
				continue;
			}
			if (str->str[i + 1] == '$' || str->str[i + 1] == '\\'
					|| str->str[i + 1] == '\'' || str->str[i + 1] == '"')
				ft_dstr_remove(str, i, 1);
		}
		i++;
	}
}

char		*get_heredoc(t_input *input, char *delim, t_env *env)
{
	char	*str;
	t_dstr	*heredoc;
	char	*delim_cmp;

	delim_cmp = ft_strjoin(delim, "\n");
	heredoc = ft_dstr_new("", 0, 32);
	input->first_line = false;
	while (1)
	{
		str = readline(input, "> ");
		if (ft_strequ(str, delim_cmp) || g_parse_error == SILENT_ABORT)
			break ;
		ft_dstr_insert(heredoc, heredoc->len, str, ft_strlen(str));
	}
	free(delim_cmp);
	if (g_parse_error == SILENT_ABORT)
		ft_dstr_del((void **)&heredoc, NULL);
	else
	{
		param_expand(heredoc, 0, env);
		remove_bslash(heredoc);
	}
	free(heredoc);
	return (heredoc ? heredoc->str : NULL);
}

void		get_all_heredocs(t_input *input, t_node *heredoc_list, t_env *env)
{
	int		i;
	char	*heredoc_str;
	t_node	*heredoc;

	i = 0;
	while (i < heredoc_list->nb_children && g_parse_error != SILENT_ABORT)
	{
		heredoc = heredoc_list->child[i];
		heredoc_str = get_heredoc(input,
				node_token(heredoc->child[1])->value->str, env);
		free(node_token(heredoc->child[1])->value->str);
		node_token(heredoc->child[1])->value->str = heredoc_str;
		i++;
	}
	i = 0;
	while (i < heredoc_list->nb_children)
	{
		heredoc_list->child[i] = NULL;
		i++;
	}
	heredoc_list->nb_children = 0;
}
