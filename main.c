/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:56:59 by mohifdi           #+#    #+#             */
/*   Updated: 2026/06/10 16:57:00 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    set_angle(char **map, int y, int x, double *angle)
{
    if (map[y][x] == 'N')
        *angle = -PI / 2;
    else if (map[y][x] == 'S')
        *angle = PI / 2;
    else if (map[y][x] == 'E')
        *angle = 0;
    else if (map[y][x] == 'W')
        *angle = PI;
}

void    player_position(char **map, double *px, double *py, double *angle)
{
    int y;
    int x;

    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == 'N' || map[y][x] == 'S'
                || map[y][x] == 'W' || map[y][x] == 'E')
            {
                *py = y + 0.5;
                *px = x + 0.5;
                set_angle(map, y, x, angle);
                return ;
            }
            x++;
        }
        y++;
    }
}

void    cub(char **map)
{
    t_data data;

    memset(&data, 0, sizeof(t_data));
    data.map = map;

    if (init_game_struct(&data))
        return ;
    mlx_hook(data.win, 2, 1L<<0, key_press, &data);
    mlx_hook(data.win, 3, 1L<<1, key_release, &data);
    mlx_hook(data.win, 12, 1L<<15, render, &data);
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_loop_hook(data.mlx, render, &data);
    render(&data);
    mlx_loop(data.mlx);
}

int main(int argc, char **argv)
{
	t_config	cfg;

	if (argc != 2)
	{
		ft_error(ERR_USAGE);
		return (1);
	}
	if (parse_cub_file(argv[1], &cfg))
	{
		free_config(&cfg);
		return (1);
	}

    cub(cfg.map);
    return (0);
}
