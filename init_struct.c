/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:56:45 by mohifdi           #+#    #+#             */
/*   Updated: 2026/06/10 16:56:46 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int init_img_noso(t_data *data)
{
    data->tex_no.img = mlx_xpm_file_to_image(data->mlx, "images/NO.xpm",
        &data->tex_no.width, &data->tex_no.height);
    if (!data->tex_no.img)
    {
        printf("Error: Unable to load images/NO.xpm\n");
        return (1);
    }
    data->tex_no.addr = mlx_get_data_addr(data->tex_no.img,
        &data->tex_no.bpp,
        &data->tex_no.line_len,
        &data->tex_no.endian);
    data->tex_so.img = mlx_xpm_file_to_image(data->mlx, "images/SO.xpm",
        &data->tex_so.width, &data->tex_so.height);
    if (!data->tex_so.img)
    {
        printf("Error: Unable to load images/SO.xpm\n");
        return (1);
    }
    data->tex_so.addr = mlx_get_data_addr(data->tex_so.img,
        &data->tex_so.bpp,
        &data->tex_so.line_len,
        &data->tex_so.endian);
    return (0);
}

int init_img_weea(t_data *data)
{
    data->tex_we.img = mlx_xpm_file_to_image(data->mlx, "images/WE.xpm",
        &data->tex_we.width, &data->tex_we.height);
    if (!data->tex_we.img)
    {
        printf("Error: Unable to load images/WE.xpm\n");
        return (1);
    }
    data->tex_we.addr = mlx_get_data_addr(data->tex_we.img,
        &data->tex_we.bpp,
        &data->tex_we.line_len,
        &data->tex_we.endian);
    data->tex_ea.img = mlx_xpm_file_to_image(data->mlx, "images/EA.xpm",
        &data->tex_ea.width, &data->tex_ea.height);
    if (!data->tex_ea.img)
    {
        printf("Error: Unable to load images/EA.xpm\n");
        return (1);
    }
    data->tex_ea.addr = mlx_get_data_addr(data->tex_ea.img,
        &data->tex_ea.bpp,
        &data->tex_ea.line_len,
        &data->tex_ea.endian);
    return (0);
}

int init_game_struct(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
        return (1);
    data->win = mlx_new_window(data->mlx, 640, 360, "Cub3d");
    data->img = mlx_new_image(data->mlx, 640, 360);
    if (!data->win || !data->img)
        return (1);
    data->addr = mlx_get_data_addr(
        data->img,
        &data->bits_per_pixel,
        &data->line_length,
        &data->endian
    );
    if (init_img_noso(data) || init_img_weea(data))
        return (1);
    player_position(data->map, &data->player_x, &data->player_y, &data->angle);
    return (0);
}
