/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copypaste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:37:34 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 02:12:42 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"

int		cut_word(t_input *input)
{
	char	*ptr;
	size_t	len;
	size_t	nprint;

	len = input->pos;
	if (len == 0)
		return (0);
	move_prevword(input);
	len -= input->pos;
	ptr = &input->line->str[input->pos];
	if (input->clip != NULL && input->oldkey == input->keys[K_CUTW]
	&& ft_dstr_insert(input->clip, 0, ptr, len) < 0)
		return (-1);
	else if (input->oldkey != input->keys[K_CUTW])
	{
		if (input->clip != NULL)
			ft_dstr_del((void **)&input->clip, NULL);
		if (!(input->clip = ft_dstr_new(ptr, len, len)))
			return (-1);
	}
	ft_dstr_remove(input->line, input->pos, len);
	nprint = printstr(input->termp, ptr);
	clearfromc(input->termp);
	movcto(input->termp, input->termp->cpos - nprint);
	return (0);
}

int		cut_after(t_input *input)
{
	size_t	len;

	len = input->line->len - input->pos;
	if (len == 0)
		return (0);
	if (input->clip != NULL)
		ft_dstr_del((void **)&input->clip, NULL);
	if (!(input->clip = ft_dstr_new(&input->line->str[input->pos], len, len)))
		return (-1);
	ft_dstr_remove(input->line, input->pos, len);
	clearfromc(input->termp);
	return (0);
}

int		cut_before(t_input *input)
{
	size_t	len;
	size_t	nprint;

	len = input->pos;
	if (len == 0)
		return (0);
	if (input->clip != NULL)
		ft_dstr_del((void **)&input->clip, NULL);
	if (!(input->clip = ft_dstr_new(input->line->str, len, len)))
		return (-1);
	move_home(input);
	ft_dstr_remove(input->line, 0, len);
	nprint = printstr(input->termp, input->line->str);
	clearfromc(input->termp);
	movcto(input->termp, input->termp->cpos - nprint);
	return (0);
}

int		paste(t_input *input)
{
	size_t	nprint;

	if (input->clip == NULL)
		return (0);
	ft_dstr_insert(input->line, input->pos, input->clip->str, input->clip->len);
	input->pos += input->clip->len;
	printstr(input->termp, input->clip->str);
	nprint = printstr(input->termp, &input->line->str[input->pos]);
	movcto(input->termp, input->termp->cpos - nprint);
	return (0);
}