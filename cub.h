#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
#include  <string.h>
# include "./minilibx-linux/mlx.h"
#include <stdlib.h>
# define PI 3.14159265358979323846
# define MARGIN 0.2

typedef struct s_tex
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     width;
    int     height;
}   t_tex;

typedef struct s_data
{
    void    *mlx;
    void    *win;
    char    **map;
    double  player_x;
    double  player_y;
    double  angle;
    int     key_w;
    int     key_s;
    int     key_a;
    int     key_d;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    char *addr_no;
    char *addr_so;
    char *addr_we;
    char *addr_ea;
    t_tex tex_no;
    t_tex tex_so;
    t_tex tex_we;
    t_tex tex_ea;
}   t_data;



typedef struct s_hit
{
    double distance;
    double hit_x;
    double hit_y;
    int side;
    int hit_side;
} t_hit;

typedef struct s_ray
{
    double  dir_x;
    double  dir_y;
    double  delta_x;
    double  delta_y;
    double  side_x;
    double  side_y;
    int     map_x;
    int     map_y;
    int     step_x;
    int     step_y;
}   t_ray;

typedef struct s_column
{
    int     x;
    int     start;
    int     end;
    int     tex_x;
    int     wall_h;
    t_tex   *tex;
}   t_column;

typedef struct s_rayctx
{
    t_hit      hit;
    double     dist;
    int        start;
    int        end;
    int        wall_h;
    t_column   col;
}   t_rayctx;

int     init_game_struct(t_data *data);
int     close_window(void *param);
int     render(void *param);
int     key_hook(int keycode, void *param);
void    render_column(t_data *d, int x, double ray);
void    update_player(t_data *data);
int     key_press(int keycode, t_data *data);
int     key_release(int keycode, t_data *data);
void    put_pixel(t_data *data, int x, int y, int color);
void    player_position(char **map, double *px, double *py, double *angle);
t_hit   cast_ray(char **map, double pos_x, double pos_y, double angle);
t_tex   *select_texture(t_data *data, t_hit hit);
void    draw_scene(void *param);


#endif