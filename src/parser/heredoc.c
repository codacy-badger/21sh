/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 20:03:18 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/11 18:44:44 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

extern int	g_parse_error;

char	*get_heredoc(t_input *input, char *delim)
{
	char	*str;
	char	*tmp;
	char	*heredoc_str;
	char	*delim_cmp;

	delim_cmp = ft_strjoin(delim, "\n");
	heredoc_str = NULL;
	input->first_line = false;
	while (1)
	{
		str = readline(input, "> ");
		if (ft_strequ(str, delim_cmp) || g_parse_error == SILENT_ABORT)
			break ;
		tmp = ft_strjoin(heredoc_str, str);
		free(heredoc_str);
		heredoc_str = tmp;
	}
	free(delim_cmp);
	if (g_parse_error == SILENT_ABORT)
		ft_memdel((void **)&heredoc_str);
	return (heredoc_str);
}

void	get_all_heredocs(t_input *input, t_node *heredoc_list)
{
	int		i;
	char	*heredoc_str;
	t_node	*heredoc;

	i = 0;
	while (i < heredoc_list->nb_children && g_parse_error != SILENT_ABORT)
	{
		heredoc = heredoc_list->child[i];
		heredoc_str = get_heredoc(input,
				node_token(heredoc->child[1])->value->str);
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
