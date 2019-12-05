/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/12/06 00:29:47 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		isctrl(t_term *term, unsigned int c)
{
	return (c == term->keys[K_EOL] || c == term->keys[K_EOF]
			|| c == term->keys[K_BSP] || c == term->keys[K_DEL]
			|| c == term->keys[K_LEFT] || c == term->keys[K_RIGHT]
			|| c == term->keys[K_UP] || c == term->keys[K_DOWN]
			|| c == term->keys[K_HOME] || c == term->keys[K_END]
			|| c == term->keys[K_NXTW] || c == term->keys[K_PRVW]
			|| c == term->keys[K_CUTW] || c == term->keys[K_CUTA]
			|| c == term->keys[K_CUTB] || c == term->keys[K_PAST]
			|| c == term->keys[K_REDRAW]);
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
