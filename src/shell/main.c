/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:37:33 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/23 10:55:57 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	increase_shlvl(t_env *env)
{
	char	*shlvl_str;
	int		shlvl_int;

	shlvl_str = get_env_var("SHLVL", env);
	if (shlvl_str != NULL)
		shlvl_int = ft_atoi(shlvl_str) + 1;
	else
		shlvl_int = 1;
	shlvl_str = ft_itoa(shlvl_int);
	set_env_var("SHLVL", shlvl_str, env);
	free(shlvl_str);
}

int			main(int argc, char **argv)
{
	struct s_sh	shell;

	init(&shell, --argc, ++argv);
	g_env = &shell.env;
	increase_shlvl(g_env);
	while (1)
		parse(&shell.lexer, &shell.env, &shell.term);
	return (0);
}
