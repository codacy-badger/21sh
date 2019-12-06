/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_reset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:23:20 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 01:23:57 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	input_clear_line(t_term *term, t_input *input)
{
	size_t	plen;

	plen = ft_strlen(*(input->pmpt));
	while (input->line->i)
		move_curs_left(term, input);
	while (plen--)
		movcleft(term);
	tputs(term->caps[C_CD], 1, ft_putc);
	display_str(term, *(input->pmpt));
}

void		input_init(struct s_input *input)
{
	if (!(input->pmpt = (char **)ft_memalloc(sizeof(char *) * (4 + 1))))
		return ;
	if (!(input->pmpt[PS1] = ft_strdup("21sh©>> ")))
		return ;
	if (!(input->pmpt[PS2] = ft_strdup("-> ")))
		return ;
	if (!(input->pmpt[PS3] = ft_strdup("'> ")))
		return ;
	if (!(input->pmpt[PS4] = ft_strdup("\"> ")))
		return ;
	if (!(input->line = line_new(32)))
		return ;
	if (!(input->clipb = line_new(32)))
		return ;
}

void		input_reset(t_term *term, t_input *input)
{
	input_clear_line(term, input);	
	line_del(&input->line);
	input->line = line_new(32);
}
