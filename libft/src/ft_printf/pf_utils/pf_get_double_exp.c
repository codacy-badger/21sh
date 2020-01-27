/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_get_double_exp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 20:07:44 by nbousset          #+#    #+#             */
/*   Updated: 2019/04/15 01:08:47 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_get_double_exp(double *f)
{
	int		exponent;

	exponent = 0;
	while (*f > 0.0 && *f < 1.0)
	{
		exponent--;
		*f *= 10.0;
	}
	while (*f >= 10.0)
	{
		exponent++;
		*f /= 10.0;
	}
	return (exponent);
}
