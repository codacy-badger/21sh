/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:56:57 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		input_init(struct s_input *input)
{
	input->prompt = input->shell->data.prompts[PS1];
	if (!(input->line = line_new(32)))
		return (ALLOC_ERROR);
	if (!(input->clipb = line_new(32)))
		return (ALLOC_ERROR);
	return (0);
}
