#include "cub.h"


int get_tex_x(t_hit hit, t_tex *tex, double ray_angle)
{
    double  wall_x;
    int     tex_x;

    if (hit.hit_side == 0)
        wall_x = hit.hit_y;
    else
        wall_x = hit.hit_x;
    wall_x -= floor(wall_x);
    tex_x = (int)(wall_x * tex->width);
    if (hit.hit_side == 0 && cos(ray_angle) > 0)
        tex_x = tex->width - tex_x - 1;

    if (hit.hit_side == 1 && sin(ray_angle) < 0)
        tex_x = tex->width - tex_x - 1;
    return (tex_x);
}

void    compute_wall(double dist, int *start, int *end, int *height)
{
    if (dist < 0.1)
        dist = 0.1;
    *height = (int)(360 / dist);
    *start = 180 - (*height / 2);
    *end = 180 + (*height / 2);
    if (*start < 0)
        *start = 0;
    if (*end >= 360)
        *end = 359;
}

void    draw_column(t_data *d, t_column *col)
{
    int     y;
    int     tex_y;
    char    *dst;
    int     color;

    y = 0;
    while (y < 360)
    {
        if (y < col->start)
            put_pixel(d, col->x, y, 0x87CEEB);
        else if (y <= col->end)
        {
            tex_y = (y - col->start) * col->tex->height / col->wall_h;
            if (tex_y < 0)
                tex_y = 0;
            if (tex_y >= col->tex->height)
                tex_y = col->tex->height - 1;
            dst = col->tex->addr + (tex_y * col->tex->line_len
                    + col->tex->bpp / 8 * col->tex_x);
            color = *(unsigned int *)dst;
            put_pixel(d, col->x, y, color);
        }
        else
            put_pixel(d, col->x, y, 0x444444);
        y++;
    }
}


void    render_column(t_data *d, int x, double ray)
{
    t_rayctx   r;

    r.hit = cast_ray(d->map, d->player_x, d->player_y, ray);
    r.dist = r.hit.distance * cos(ray - d->angle);
    compute_wall(r.dist, &r.start, &r.end, &r.wall_h);
    r.col.tex = select_texture(d, r.hit);
    r.col.tex_x = get_tex_x(r.hit, r.col.tex, ray);
    r.col.x = x;
    r.col.start = r.start;
    r.col.end = r.end;
    r.col.wall_h = r.wall_h;
    draw_column(d, &r.col);
}

void    draw_scene(void *param)
{
    t_data  *d;
    double  ray;
    double  step;
    int     x;

    d = (t_data *)param;
    ray = d->angle - (PI / 6);
    step = (PI / 3) / 640;
    memset(d->addr, 0, d->line_length * 360);
    x = 0;
    while (x < 640)
    {
        render_column(d, x, ray);
        ray += step;
        x++;
    }
    mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}