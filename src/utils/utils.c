/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 14:46:46 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

ssize_t	getcsize_rev(char *s)
{
	ssize_t	size;

	size = 1;
	if (*s-- < 0)
	{
		size++;
		while (!(*s-- & (1 << 6)))
			size++;
	}
	return (size);
}

ssize_t	getcsize(int c)
{
	char	*ptr;
	ssize_t	size;
	int		i;

	i = 7;
	size = 1;
	ptr = (char *)&c;
	if ((*ptr & (1 << i--)))
	{
		while ((*ptr & (1 << i)) && size < 4)
		{
			size++;
			i--;
		}
	}
	return (size);
}

ssize_t	ft_putwc(int c)
{
	ssize_t	size;

	size = getcsize(c);
	if (write(STDOUT_FILENO, (char *)&c, size) != size)
		return (0);
	return (size);
}

int		ft_putc(int c)
{
	if (write(STDOUT_FILENO, (char *)&c, 1) != 1)
		return (0);
	return (1);
}
