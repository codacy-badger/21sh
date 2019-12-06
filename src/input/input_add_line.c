/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_add_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fratajcz <fratajcz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:08:08 by fratajcz          #+#    #+#             */
/*   Updated: 2019/11/27 15:38:19 by fratajcz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int     input_add_line(t_input *input)
{
    t_line  *new;

    if (!(new = line_new(32)))
        return (ALLOC_ERROR);
    line_add(&input->line, new, 1);
    return (0);
}
