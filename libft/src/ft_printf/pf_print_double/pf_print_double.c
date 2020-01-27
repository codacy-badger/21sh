/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:32:10 by nbousset          #+#    #+#             */
/*   Updated: 2019/05/04 17:01:01 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		suffix_double(t_printf *pf)
{
	if (pf->flags & HASH_FLAG && pf->precision == 0)
		pf->str = ft_strsuffix(pf->str, ".", 1);
}

static void		prefix_double(t_printf *pf, t_double *t_f)
{
	char	prefix[2];

	ft_memset(prefix, '\0', 2);
	if (t_f->neg)
		prefix[0] = '-';
	else if (pf->flags & PLUS_FLAG)
		prefix[0] = '+';
	else if (pf->flags & SPACE_FLAG)
		prefix[0] = ' ';
	else
		return ;
	if ((pf->flags & ZERO_FLAG) && pf->field_width-- && prefix[0])
		pf_pad_field_width(pf);
	if (pf->str)
		pf->str = ft_strprefix(pf->str, prefix, 1);
}

static void		write_double(t_printf *pf, t_double *t_f)
{
	double		f;

	f = t_f->f;
	if (t_f->is_nan || t_f->is_inf)
		return (print_inf_nan(pf, t_f));
	pf->str = ft_dtoa(f, pf->precision);
	if (pf->str)
		suffix_double(pf);
	if (pf->str)
		prefix_double(pf, t_f);
	if (pf->str)
		pf_pad_field_width(pf);
	if (pf->str)
		pf_bufferize(pf, pf->str, ft_strlen(pf->str));
	else
		pf_error(pf, "Dynamic allocation error.\n");
}

void			pf_print_double(t_printf *pf)
{
	t_double	t_f;

	ft_bzero(&t_f, sizeof(t_double));
	ft_frexp(&t_f, va_arg(*pf->args, double));
	if (!(pf->flags & PREC_FLAG))
		pf->precision = 6;
	write_double(pf, &t_f);
	ft_memdel((void **)&pf->str);
	pf->str = NULL;
	pf->len_modif = 0;
	pf->flags = 0;
}
