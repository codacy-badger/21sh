/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ceil_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:32:10 by nbousset          #+#    #+#             */
/*   Updated: 2019/05/04 17:01:01 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_ceil_double(double *fp, size_t precision)
{
	double		f;
	uintmax_t	integer_part;
	int			expo;
	int			mod;

	f = (*fp < 0.0) ? -(*fp) : *fp;
	integer_part = (uintmax_t)(f);
	expo = 0;
	while (precision--)
	{
		f *= 10.0;
		mod = integer_part % 10;
		integer_part = (uintmax_t)(f);
		f -= (integer_part);
		expo--;
	}
	if ((mod = (uintmax_t)(f * 10.0) % 10) > 4)
	{
		if (*fp > 0.0)
			*fp += (long double)ft_power(10, (double)expo);
		else if (*fp < 0.0)
			*fp -= (long double)ft_power(10, (double)expo);
	}
}
