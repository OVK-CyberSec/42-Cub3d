#include "../includes/cub3d.h"

/*
** make_color: packs R,G,B into a single 0xRRGGBB integer.
*/
static int	make_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

/*
** load_texture: loads one XPM texture file into t_tex via mlx.
** Returns 0 on success, 1 on error.
*/
static int	load_texture(t_data *data, t_tex *tex, const char *path)
{
	tex->img = mlx_xpm_file_to_image(data->mlx, (char *)path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (ft_error(ERR_TEX_INVALID));
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	return (0);
}

/*
** init_textures: loads all four directional textures from the config.
** Returns 0 on success, 1 on error.
*/
static int	init_textures(t_data *data, t_config *cfg)
{
	if (load_texture(data, &data->tex_no, cfg->tex_no))
		return (1);
	if (load_texture(data, &data->tex_so, cfg->tex_so))
		return (1);
	if (load_texture(data, &data->tex_we, cfg->tex_we))
		return (1);
	if (load_texture(data, &data->tex_ea, cfg->tex_ea))
		return (1);
	return (0);
}

/*
** init_game_struct: sets up the MLX connection, window, framebuffer image,
** textures, floor/ceiling packed colors, and player spawn position.
** Returns 0 on success, 1 on error.
*/
int	init_game_struct(t_data *data, t_config *cfg)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_error(ERR_MLX_START));
	data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, "cub3D");
	if (!data->win)
		return (ft_error(ERR_MLX_WIN));
	data->img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	if (!data->img)
		return (ft_error(ERR_MLX_IMG));
	data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pixel,
			&data->line_length,
			&data->endian);
	if (init_textures(data, cfg))
		return (1);
	data->floor_color = make_color(cfg->floor_r, cfg->floor_g, cfg->floor_b);
	data->ceil_color = make_color(cfg->ceil_r, cfg->ceil_g, cfg->ceil_b);
	player_position(data->map, &data->player_x, &data->player_y, &data->angle);
	return (0);
}
