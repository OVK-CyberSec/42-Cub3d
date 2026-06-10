/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:56:54 by mohifdi           #+#    #+#             */
/*   Updated: 2026/06/10 16:56:56 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void put_pixel(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}


t_tex   *select_texture(t_data *data, t_hit hit)
{
    if (hit.side == 0)
        return (&data->tex_ea);
    else if (hit.side == 1)
        return (&data->tex_we);
    else if (hit.side == 2)
        return (&data->tex_so);
    return (&data->tex_no);
}

int render(void *param)
{
    update_player(param);
    draw_scene(param);
    return (0);
}
