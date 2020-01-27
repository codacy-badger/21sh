/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:32:10 by nbousset          #+#    #+#             */
/*   Updated: 2019/05/04 17:01:01 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	handle_strings(t_printf *pf)
{
	return (pf_print_string(pf));
}

static void	handle_float(t_printf *pf)
{
	if (pf->conv == 'f' || pf->conv == 'F')
	{
		if (pf->len_modif & LD_LEN)
			return (pf_print_ldouble(pf));
		return (pf_print_double(pf));
	}
	else if (pf->conv == 'e' || pf->conv == 'E')
	{
		if (pf->len_modif & LD_LEN)
			return (pf_print_ldouble_sci(pf));
		return (pf_print_double_sci(pf));
	}
	else if (pf->conv == 'a' || pf->conv == 'A')
	{
		if (pf->len_modif & LD_LEN)
			return (pf_print_ldouble_hex(pf));
		return (pf_print_double_hex(pf));
	}
}

static void	handle_int(t_printf *pf)
{
	if (pf->conv == 'd' || pf->conv == 'D' || pf->conv == 'i')
		return (pf_print_int(pf));
	else if (pf->conv == 'o' || pf->conv == 'O')
		return (pf_print_uint(pf, 8));
	else if (pf->conv == 'u' || pf->conv == 'U')
		return (pf_print_uint(pf, 10));
	else if (pf->conv == 'x' || pf->conv == 'X'
			|| pf->conv == 'p' || pf->conv == 'P')
		return (pf_print_uint(pf, 16));
	else if (pf->conv == 'b' || pf->conv == 'B')
		return (pf_print_uint(pf, 2));
}

void		pf_handle_arg(t_printf *pf)
{
	if (ft_strchr("dDioOuUxXbBpP", pf->conv))
		return (handle_int(pf));
	else if (ft_strchr("fFaAeEgG", pf->conv))
		return (handle_float(pf));
	else if (ft_strchr("cCsS%", pf->conv))
		return (handle_strings(pf));
}
