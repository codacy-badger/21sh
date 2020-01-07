/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:08:22 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/07 18:50:55 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** see POSIX Shell Command Language 2.6 Word Expansions
*/

void	tilde_expand(t_dstr *str)
{
	
}

void	param_expand(t_dstr *str)
{

}

/*
** return an argv-like array containing all words in the command (no operators)
*/

char	**field_split(t_node *command)
{

}

void	*remove_quotes(char **argv)
{
	
}

/*
** If the complete expansion appropriate for a word results in an empty field, 
** that empty field shall be deleted from the list of fields that form the
** completely expanded command, unless the original word contained single-quote
** or double-quote characters. -> bash does not seem to keep the empty field in
** any case ? would be easier to implement.
*/

void	*remove_empty_fields(char **argv)
{

}

char	**expand(t_node *command, t_env *env)
{
	int		i;
	char	**argv;

	i = 0;
	while (i < command->nb_children)
	{
		if (node_token(command->child[i])->type == WORD)
		{
			tilde_expand(node_token(command->child[i])->value);
			param_expand(node_token(command->child[i])->value);
		}
		i++;
	}
	argv = field_split(command);
	remove_quotes(argv);
	remove_empty_fields(argv);
	return (argv);
}
