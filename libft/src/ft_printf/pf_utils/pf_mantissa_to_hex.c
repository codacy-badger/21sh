/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_mantissa_to_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:32:10 by nbousset          #+#    #+#             */
/*   Updated: 2019/05/04 17:01:01 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		add_one(char *str)
{
	if (*str == 'F')
	{
		*str = '0';
		return (1);
	}
	if (*str == '9')
		*str = 'A';
	else
		(*str)++;
	return (0);
}

static void		ceil(char *str, size_t precision)
{
	char	carry;
	size_t	len;

	carry = 0;
	len = 2 + (precision ? precision : 1);
	if (str[len] > '8')
	{
		while (len--)
		{
			if (str[len] == '.' || str[len] == '\0')
				continue ;
			carry = add_one(&str[len]);
			if (carry == 0)
				break ;
		}
	}
	if (carry)
		str[0] = '2';
}

char			*pf_mantissa_to_hex(t_double *t_f, size_t precision)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = (precision > 13) ? precision + 2 : 15;
	if (!(str = (char *)ft_memalloc(len + 1)))
		return (NULL);
	if (t_f->is_denormalized)
	{
		t_f->mantissa <<= 1;
		t_f->real_exponent--;
	}
	str[0] = t_f->f == 0.0 ? '0' : '1';
	str[1] = (precision) ? '.' : '\0';
	i = 2;
	len = 13;
	while (len--)
		str[i++] = ft_dtoc_36((t_f->mantissa >> (len * 4)) & 15);
	len = precision;
	while (len-- > 13)
		str[i++] = '0';
	ceil(str, precision);
	return (str);
}
