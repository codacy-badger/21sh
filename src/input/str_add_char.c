/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_add_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/22 01:44:22 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	str_add_char(t_input *input, int c)
{
	ft_dstr_insert(&input->line, (char)c, input->i);
}
