/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_inf_nan.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:32:10 by nbousset          #+#    #+#             */
/*   Updated: 2019/05/04 17:01:01 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	prefix_inf_nan(t_printf *pf, t_double *t_f)
{
	if (!(t_f->is_nan) && t_f->neg)
		pf->str = ft_strprefix(pf->str, "-", 1);
	else if (!(t_f->is_nan) && pf->flags & PLUS_FLAG)
		pf->str = ft_strprefix(pf->str, "+", 1);
	else if (!(t_f->is_nan) && pf->flags & SPACE_FLAG)
		pf->str = ft_strprefix(pf->str, " ", 1);
	else
		return ;
}

void		print_inf_nan(t_printf *pf, t_double *t_f)
{
	if (pf->flags & ZERO_FLAG)
		pf->flags ^= ZERO_FLAG;
	if (t_f->is_inf)
		pf->str = ft_strdup("inf");
	else if (t_f->is_nan)
		pf->str = ft_strdup("nan");
	prefix_inf_nan(pf, t_f);
	pf_pad_field_width(pf);
	pf_bufferize(pf, pf->str, ft_strlen(pf->str));
}
