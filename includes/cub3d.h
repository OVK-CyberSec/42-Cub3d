#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "cub/cub.h"
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include "../minilibx-linux/mlx.h"

/* ==============================
**  ERROR MESSAGES
** ============================== */

# define ERR_USAGE        "usage: ./cub3d <path/to/map.cub>"
# define ERR_FILE_NOT_CUB "Not a .cub file"
# define ERR_FILE_NOT_XPM "Not an .xpm file"
# define ERR_FILE_IS_DIR  "Is a directory"
# define ERR_FLOOR_CEILING   "Invalid floor/ceiling RGB color(s)"
# define ERR_COLOR_FLOOR     "Invalid floor RGB color"
# define ERR_COLOR_CEILING   "Invalid ceiling RGB color"
# define ERR_INVALID_MAP     "Map description is either wrong or incomplete"
# define ERR_INV_LETTER      "Invalid character in map"
# define ERR_NUM_PLAYER      "Map has more than one player"
# define ERR_TEX_RGB_VAL     "Invalid RGB value (min: 0, max: 255)"
# define ERR_TEX_MISSING     "Missing texture(s)"
# define ERR_TEX_INVALID     "Invalid texture(s)"
# define ERR_COLOR_MISSING   "Missing color(s)"
# define ERR_MAP_MISSING     "Missing map"
# define ERR_MAP_TOO_SMALL   "Map is not at least 3 lines high"
# define ERR_MAP_NO_WALLS    "Map is not surrounded by walls"
# define ERR_MAP_LAST        "Map is not the last element in file"
# define ERR_PLAYER_POS      "Invalid player position"
# define ERR_PLAYER_DIR      "Map has no player position (expected N, S, E or W)"
# define ERR_MALLOC          "Could not allocate memory"
# define ERR_MLX_START       "Could not start mlx"
# define ERR_MLX_WIN         "Could not create mlx window"
# define ERR_MLX_IMG         "Could not create mlx image"

/* ==============================
**  CONSTANTS
** ============================== */

# define PI         3.14159265358979323846
# define WIN_W      640
# define WIN_H      360
# define FOV        (PI / 3)
# define MOVE_SPEED 0.05
# define ROT_SPEED  0.05

/* ==============================
**  PARSING STRUCTS
** ============================== */

typedef struct s_config
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceil_r;
	int		ceil_g;
	int		ceil_b;
	char	**map;
	int		map_height;
	int		map_width;
}	t_config;

/* ==============================
**  RENDERING STRUCTS
** ============================== */

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_tex;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	double	player_x;
	double	player_y;
	double	angle;
	int		key_w;
	int		key_s;
	int		key_a;
	int		key_d;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_tex	tex_no;
	t_tex	tex_so;
	t_tex	tex_we;
	t_tex	tex_ea;
	int		floor_color;
	int		ceil_color;
}	t_data;

typedef struct s_hit
{
	double	distance;
	double	hit_x;
	double	hit_y;
	int		side;
	int		hit_side;
}	t_hit;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
}	t_ray;

typedef struct s_column
{
	int		x;
	int		start;
	int		end;
	int		tex_x;
	int		wall_h;
	t_tex	*tex;
}	t_column;

typedef struct s_rayctx
{
	t_hit		hit;
	double		dist;
	int			start;
	int			end;
	int			wall_h;
	t_column	col;
}	t_rayctx;

/* ==============================
**  PARSING PROTOTYPES
** ============================== */

int		ft_error(const char *msg);
int		parse_cub_file(const char *path, t_config *cfg);
int		parse_texture(char *line, char **dest);
int		parse_color(char *line, int *r, int *g, int *b);
int		handle_identifier(char *line, t_config *cfg);
int		parse_map(int fd, t_config *cfg, char *first_line);
int		validate_map(t_config *cfg);
char	*ft_strdup(const char *s);
char	*ft_strtrim(const char *s);
int		ft_atoi_strict(const char *s, int *out);
void	free_config(t_config *cfg);
void	free_split(char **arr);
int		ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);

/* ==============================
**  ENGINE PROTOTYPES
** ============================== */

void	cub(t_config *cfg);
int		init_game_struct(t_data *data, t_config *cfg);
void	player_position(char **map, double *px, double *py, double *angle);

/* ==============================
**  PLAYER PROTOTYPES
** ============================== */

void	update_player(t_data *data);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		close_window(void *param);

/* ==============================
**  RENDERING PROTOTYPES
** ============================== */

int		render(void *param);
void	put_pixel(t_data *data, int x, int y, int color);
t_tex	*select_texture(t_data *data, t_hit hit);
t_hit	cast_ray(char **map, double pos_x, double pos_y, double angle);
void	draw_scene(void *param);
void	render_column(t_data *d, int x, double ray);

#endif
