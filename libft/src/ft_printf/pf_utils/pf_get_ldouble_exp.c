/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_get_ldouble_exp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 20:07:44 by nbousset          #+#    #+#             */
/*   Updated: 2019/04/15 01:08:47 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_get_ldouble_exp(long double *lf)
{
	int		exponent;

	exponent = 0;
	while (*lf > 0.0 && *lf < 1.0)
	{
		exponent--;
		*lf *= 10.0;
	}
	while (*lf >= 10.0)
	{
		exponent++;
		*lf /= 10.0;
	}
	return (exponent);
}
