/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
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

int		init(t_sh *shell)
{
	ft_bzero(shell, sizeof(*shell));
	init_sig(shell);
	init_term(&shell->term);
	init_input(&shell->input, &shell->term);
	return (0);
}
