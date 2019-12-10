/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/08 03:09:45 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_printable(unsigned long c)
{
	return ((char)c != 27 && !(c < 32 || c == 127));
}

ssize_t	getcsize_rev(char *s, int i)
{
	ssize_t	size;

	size = 1;
	if (i == 0)
		return (size);
	if (i && *s-- < 0)
	{
		size++;
		while (i-- && !(*s-- & (1 << 6)))
			size++;
	}
	return (size);
}

ssize_t	getcsize(int c)
{
	char	*ptr;
	ssize_t	size;
	int		i;

	i = 6;
	size = 1;
	ptr = (char *)&c;
	if (*ptr < 0)
	{
		while ((*ptr & (1 << i--)) && size < 5)
			size++;
	}
	return (size);
}

ssize_t	ft_putwc(char *c)
{
	ssize_t	size;

	size = getcsize(*c);
	if (write(STDOUT_FILENO, c, size) != size)
		return (0);
	return (size);
}

int		ft_putc(int c)
{
	if (write(STDOUT_FILENO, (char *)&c, 1) != 1)
		return (0);
	return (1);
}
