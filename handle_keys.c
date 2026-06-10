/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:57:19 by mohifdi           #+#    #+#             */
/*   Updated: 2026/06/10 16:57:20 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


int close_window(void *param)
{
    t_data *data;

    data = (t_data *)param;
    mlx_destroy_image(data->mlx, data->img);
    mlx_destroy_image(data->mlx, data->tex_no.img);
    mlx_destroy_image(data->mlx, data->tex_so.img);
    mlx_destroy_image(data->mlx, data->tex_we.img);
    mlx_destroy_image(data->mlx, data->tex_ea.img);
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
    return (0);
}

int key_press(int keycode, t_data *data)
{
    if (keycode == 119)
        data->key_w = 1;
    if (keycode == 115)
        data->key_s = 1;
    if (keycode == 97)
        data->key_a = 1;
    if (keycode == 100)
        data->key_d = 1;
    if (keycode == 65361)
        data->angle -= 0.1;
    if (keycode == 65363)
        data->angle += 0.1;
    if (keycode == 65307)
        close_window(data);
    return (0);
}

int key_release(int keycode, t_data *data)
{
    if (keycode == 119)
        data->key_w = 0;
    if (keycode == 115)
        data->key_s = 0;
    if (keycode == 97)
        data->key_a = 0;
    if (keycode == 100)
        data->key_d = 0;
    return (0);
}
