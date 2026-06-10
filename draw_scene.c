/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:56:00 by mohifdi           #+#    #+#             */
/*   Updated: 2026/06/10 17:05:20 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_tex_x(t_hit hit, t_tex *tex, double ray_angle)
{
	double	wall_x;
	int	tex_x;

	if (hit.hit_side == 0)
		wall_x = hit.hit_y - floor(hit.hit_y);
	else
		wall_x = hit.hit_x - floor(hit.hit_x);
	tex_x = (int)(wall_x * tex->width);
	if (hit.hit_side == 0 && cos(ray_angle) < 0)
		tex_x = tex->width - tex_x - 1;
	if (hit.hit_side == 1 && sin(ray_angle) > 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

void	compute_wall(double dist, int *start, int *end, int *height)
{
	int screen_h = 360;

	if (dist < 0.1)
		dist = 0.1;
	*height = (int)(screen_h / dist);
	*start  = (screen_h / 2) - (*height / 2);
	*end    = (screen_h / 2) + (*height / 2);
}

void	draw_column(t_data *d, t_column *col)
{
	int y = 0;
	int tex_y;
	int color;
	char *dst;

	while (y < 360)
	{
		if (y < col->start || y > col->end)
		{
	   	 put_pixel(d, col->x, y, (y < col->start) ? 0x87CEEB : 0x444444);
		}
	else
	{
	    int wall_y = y - (180 - col->wall_h / 2);
	    tex_y = wall_y * col->tex->height / col->wall_h;
	    if (tex_y < 0)              tex_y = 0;
	    if (tex_y >= col->tex->height) tex_y = col->tex->height - 1;

	    dst = col->tex->addr + (tex_y * col->tex->line_len
		+ (col->tex->bpp / 8) * col->tex_x);
	    color = *(unsigned int *)dst;
	    put_pixel(d, col->x, y, color);
	}
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
