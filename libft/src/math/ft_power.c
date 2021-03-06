/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbousset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:52:06 by nbousset          #+#    #+#             */
/*   Updated: 2019/06/13 22:30:53 by nbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double		ft_power(double nb, double pwr)
{
	if (pwr == 0.0)
		return (1.0);
	if (pwr < 0.0)
		return (1.0 / ft_power(nb, -pwr));
	return (nb * ft_power(nb, pwr - 1.0));
}
