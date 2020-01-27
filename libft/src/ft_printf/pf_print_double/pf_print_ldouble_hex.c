/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_ldouble_hex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:32:10 by nbousset          #+#    #+#             */
/*   Updated: 2019/05/04 17:01:01 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		remove_trailing_zeros(char *str)
{
	size_t	i;

	i = ft_strlen(str) - 1;
	while (str[i] == '0')
		i--;
	str[i + 1] = '\0';
}

static void		suffix_ldouble_hex(t_printf *pf, int exponent)
{
	unsigned int	exp;
	char			suffix[3];
	char			*str_exp;

	exp = (exponent < 0) ? -exponent : exponent;
	if (!(pf->flags & PREC_FLAG))
		remove_trailing_zeros(pf->str);
	else
		pf->str[2 + pf->precision] = '\0';
	if ((pf->flags & HASH_FLAG) && (pf->flags & PREC_FLAG)
													&& pf->precision == 0)
		pf->str = ft_strsuffix(pf->str, ".", 1);
	suffix[0] = 'P';
	suffix[1] = (exponent < 0) ? '-' : '+';
	suffix[2] = '\0';
	str_exp = ft_utoa(exp);
	if (pf->str)
		pf->str = ft_strsuffix(pf->str, suffix, 1);
	if (pf->str && str_exp)
		pf->str = ft_strsuffix(pf->str, str_exp, 1);
	ft_memdel((void **)&str_exp);
}

static void		prefix_ldouble_hex(t_printf *pf, t_double *t_f)
{
	char	prefix[4];
	size_t	i;

	i = 0;
	ft_memset(prefix, '\0', 4);
	if (t_f->neg)
		prefix[i++] = '-';
	else if (pf->flags & PLUS_FLAG)
		prefix[i++] = '+';
	else if (pf->flags & SPACE_FLAG)
		prefix[i++] = ' ';
	ft_memcpy(&prefix[i], "0X", 2);
	if ((pf->flags & ZERO_FLAG) && prefix[0])
	{
		if (pf->field_width > ft_strlen(prefix))
			pf->field_width -= ft_strlen(prefix);
		pf_pad_field_width(pf);
	}
	if (pf->str)
		pf->str = ft_strprefix(pf->str, prefix, 1);
}

static void		write_ldouble_hex(t_printf *pf, t_double *t_f)
{
	if (t_f->is_nan || t_f->is_inf)
		return (print_inf_nan(pf, t_f));
	if (!(pf->flags & PREC_FLAG))
		pf->precision = 13;
	pf->str = pf_lmantissa_to_hex(t_f, pf->precision);
	if (pf->str)
		suffix_ldouble_hex(pf, t_f->real_exponent);
	if (pf->str)
		prefix_ldouble_hex(pf, t_f);
	if (pf->str)
		pf_pad_field_width(pf);
	if (pf->str)
	{
		if (!(pf->flags & UP_FLAG))
			ft_strtolower(pf->str);
		pf_bufferize(pf, pf->str, ft_strlen(pf->str));
	}
	else
		pf_error(pf, "Dynamic allocation error.\n");
}

void			pf_print_ldouble_hex(t_printf *pf)
{
	t_double	t_f;

	ft_bzero(&t_f, sizeof(t_double));
	ft_frexpl(&t_f, va_arg(*pf->args, long double));
	write_ldouble_hex(pf, &t_f);
	ft_memdel((void **)&pf->str);
	pf->str = NULL;
	pf->len_modif = 0;
	pf->flags = 0;
}
