/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 00:37:04 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Think about interactive & non interactive mode...
** assert read line works properly when read from file
*/

int			shell_init(t_sh *shell)
{
	int		ret;

	ft_bzero(shell, sizeof(*shell));
	sig_init(shell);
	if ((ret = term_init(&shell->term)) != 0)
		return (ret);
	if ((ret = input_init(&shell->input)) != 0)
		return (ret);
	if ((ret = lexer_init(&shell->lexer)) != 0)
		return (ret);
	return (ret);
}
