/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frexpl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:32:10 by nbousset          #+#    #+#             */
/*   Updated: 2019/05/04 17:01:01 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void		ft_frexpl(t_double *t_f, long double lf)
{
	unsigned long	*ptr;

	ptr = (unsigned long *)(&lf);
	ft_bzero(t_f, sizeof(t_double));
	if (lf == 0.0)
		return ;
	if (lf < 0.0)
	{
		t_f->neg = 1;
		lf = -lf;
	}
	t_f->lf = lf;
	t_f->mantissa |= (*ptr & LDOUBLE_MANTISSA_MASK);
	t_f->exponent = (*(++ptr) & LDOUBLE_EXPONENT_MASK);
	if (t_f->exponent == 0 && t_f->mantissa)
		t_f->is_denormalized = 1;
	else if (t_f->exponent == LDOUBLE_EXPONENT_MAX)
	{
		t_f->is_inf = (t_f->mantissa == 0) ? 1 : 0;
		t_f->is_nan = (t_f->mantissa == 0) ? 0 : 1;
	}
	if (t_f->is_denormalized)
		t_f->real_exponent = 1 - LDOUBLE_EXPONENT_SHIFT;
	else
		t_f->real_exponent = t_f->exponent - LDOUBLE_EXPONENT_SHIFT;
}
