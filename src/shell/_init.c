/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/17 20:16:33 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Think about interactive & non interactive mode...
** assert read line works properly when read from file
*/

int		init(t_sh *shell)
{
	int		ret;
	extern char	**environ;

	ft_bzero(shell, sizeof(*shell));
	init_sig(shell);
	if ((ret = init_term(&shell->term)) != 0)
		return (ret);
	if ((ret = init_input(&shell->input, &shell->term)) != 0)
		return (ret);
	if ((ret = lexer_init(&shell->lexer)) != 0)
		return (ret);
	shell->env = env_dup(environ);
	return (ret);
}
