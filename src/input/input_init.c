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

static int	init_prompts(struct s_input *input)
{
	if (!(input->prompts[PS1] = ft_strdup("21sh©>> ")))
		return (ALLOC_ERROR);
	if (!(input->prompts[PS2] = ft_strdup("-> ")))
		return (ALLOC_ERROR);
	if (!(input->prompts[PS3] = ft_strdup("'> ")))
		return (ALLOC_ERROR);
	if (!(input->prompts[PS4] = ft_strdup("\"> ")))
		return (ALLOC_ERROR);
	input->prompt = input->prompts[PS1];
	return (0);
}

int			input_init(struct s_input *input)
{
	int		ret;

	if ((ret = init_prompts(input)) < 0)
		return (ret);
	if (!(input->line = line_new(32)))
		return (ALLOC_ERROR);
	if (!(input->clipb = line_new(32)))
		return (ALLOC_ERROR);
	return (0);
}
