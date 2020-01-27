/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_ldouble_sci.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:32:10 by nbousset          #+#    #+#             */
/*   Updated: 2019/05/04 17:01:01 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		suffix_ldouble_sci(t_printf *pf, int exponent)
{
	unsigned int	exp;
	char			suffix[4];
	char			*str_exp;

	exp = (exponent < 0) ? -exponent : exponent;
	if (pf->flags & HASH_FLAG && pf->precision == 0)
		pf->str = ft_strsuffix(pf->str, ".", 1);
	suffix[0] = 'E';
	suffix[1] = (exponent < 0) ? '-' : '+';
	suffix[2] = (exp < 10) ? '0' : '\0';
	suffix[3] = '\0';
	str_exp = ft_utoa(exp);
	if (!(pf->flags & UP_FLAG))
		ft_strtolower(suffix);
	if (pf->str)
		pf->str = ft_strsuffix(pf->str, suffix, 1);
	if (pf->str && str_exp)
		pf->str = ft_strsuffix(pf->str, str_exp, 1);
	ft_memdel((void **)&str_exp);
}

static void		prefix_ldouble_sci(t_printf *pf, t_double *t_f)
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

static void		write_ldouble_sci(t_printf *pf, t_double *t_f)
{
	long double	lf;
	int			exponent;

	if (t_f->is_nan || t_f->is_inf)
		return (print_inf_nan(pf, t_f));
	lf = t_f->lf;
	exponent = pf_get_ldouble_exp(&lf);
	pf->str = ft_ldtoa(lf, pf->precision);
	if (pf->str)
		suffix_ldouble_sci(pf, exponent);
	if (pf->str)
		prefix_ldouble_sci(pf, t_f);
	if (pf->str)
		pf_pad_field_width(pf);
	if (pf->str)
		pf_bufferize(pf, pf->str, ft_strlen(pf->str));
	else
		pf_error(pf, "Dynamic allocation error.\n");
}

void			pf_print_ldouble_sci(t_printf *pf)
{
	t_double	t_f;

	ft_bzero(&t_f, sizeof(t_double));
	ft_frexpl(&t_f, va_arg(*pf->args, long double));
	if (!(pf->flags & PREC_FLAG))
		pf->precision = 6;
	write_ldouble_sci(pf, &t_f);
	ft_memdel((void **)&pf->str);
	pf->str = NULL;
	pf->len_modif = 0;
	pf->flags = 0;
}
