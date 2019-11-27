/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:57 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		init_input(struct s_input *input)
{
	if (!(input->pmpt = (char **)ft_memalloc(sizeof(char *) * (4 + 1))))
		return ;
	if (!(input->pmpt[PS1] = ft_strdup(">> ")))
		return ;
	if (!(input->pmpt[PS2] = ft_strdup("-> ")))
		return ;
	if (!(input->pmpt[PS3] = ft_strdup("'> ")))
		return ;
	if (!(input->pmpt[PS4] = ft_strdup("\"> ")))
		return ;
	input->line = line_new(32);
}
