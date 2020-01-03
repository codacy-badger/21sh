/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 08:48:18 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/03 14:36:39 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_ast(t_node *ast, int indent_level)
{
	int i;
	int	n;

	if (ast == NULL)
		return ;
	n = 0;
	while (n++ < indent_level)
		write(1, "  ", 2);
	if (ast == NULL)
		printf("NULL");
	if (ast->data != NULL)
		printf("%s\n", ((t_token *)ast->data)->value->str);
	else
		printf("cmd\n");
	fflush(stdout);
	if (ast->nb_children > 0)
	{
		i = 0;
		while (i < ast->nb_children)
			print_ast(ast->child[i++], indent_level + 1);
	}
}
