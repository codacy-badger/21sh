/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 20:03:18 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/12 18:49:50 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_parse_error;

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
	str = NULL;
	free(delim_cmp);
	if (g_parse_error == SILENT_ABORT)
		ft_dstr_del((void **)&heredoc, NULL);
	else
	{
		param_expand(heredoc, 0, env);
		str = heredoc->str;
	}
	free(heredoc);
	return (str);
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
