#include "../includes/cub3d.h"

/*
** set_angle: sets the player's starting angle based on the spawn character.
*/
static void	set_angle(char c, double *angle)
{
	if (c == 'N')
		*angle = -PI / 2;
	else if (c == 'S')
		*angle = PI / 2;
	else if (c == 'E')
		*angle = 0;
	else if (c == 'W')
		*angle = PI;
}

/*
** player_position: scans the map for the player spawn cell (N/S/E/W),
** sets player_x, player_y and angle accordingly.
*/
void	player_position(char **map, double *px, double *py, double *angle)
{
	int	y;
	int	x;

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
				set_angle(map[y][x], angle);
				return ;
			}
			x++;
		}
		y++;
	}
}

/*
** cub: initialises and runs the game from a parsed config.
*/
void	cub(t_config *cfg)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	data.map = cfg->map;
	if (init_game_struct(&data, cfg))
	{
		free_config(cfg);
		return ;
	}
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.win, 12, 1L << 15, render, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop_hook(data.mlx, render, &data);
	render(&data);
	mlx_loop(data.mlx);
	free_config(cfg);
}

/*
** main: validates arguments, parses the .cub file, then launches the game.
*/
int	main(int argc, char **argv)
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
	cub(&cfg);
	return (0);
}
