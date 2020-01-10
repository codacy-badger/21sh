/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2020/01/03 15:42:33 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Think about interactive & non interactive mode...
** assert read line works properly when read from file
*/

int		init(t_sh *shell)
{
	extern char	**environ;

	ft_bzero(shell, sizeof(*shell));
	init_sig(shell);
	init_term(&shell->term);
	init_input(&shell->input, &shell->term);
	init_lexer(&shell->lexer, &shell->input);
	shell->env = env_dup(environ);
	return (0);
}
