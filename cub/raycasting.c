#include "cub.h"

void init_ray(t_ray *r, double pos_x, double pos_y, double angle)
{
    r->dir_x = cos(angle);
    r->dir_y = sin(angle);
    r->map_x = (int)pos_x;
    r->map_y = (int)pos_y;
    r->delta_x = fabs(1 / r->dir_x);
    r->delta_y = fabs(1 / r->dir_y);
}

void init_step(t_ray *r, double pos_x, double pos_y)
{
    if (r->dir_x < 0)
    {
        r->step_x = -1;
        r->side_x = (pos_x - r->map_x) * r->delta_x;
    }
    else
    {
        r->step_x = 1;
        r->side_x = (r->map_x + 1.0 - pos_x) * r->delta_x;
    }
    if (r->dir_y < 0)
    {
        r->step_y = -1;
        r->side_y = (pos_y - r->map_y) * r->delta_y;
    }
    else
    {
        r->step_y = 1;
        r->side_y = (r->map_y + 1.0 - pos_y) * r->delta_y;
    }
}

void perform_dda(char **map, t_ray *r, t_hit *hit)
{
    int wall;

    wall = 0;
    while (!wall)
    {
        if (r->side_x < r->side_y)
        {
            r->side_x += r->delta_x;
            r->map_x += r->step_x;
            hit->hit_side = 0;
        }
        else
        {
            r->side_y += r->delta_y;
            r->map_y += r->step_y;
            hit->hit_side = 1;
        }
        if (map[r->map_y][r->map_x] == '1')
            wall = 1;
    }
}

void finalize_hit(t_ray *r, t_hit *hit,
                        double pos_x, double pos_y)
{
    if (hit->hit_side == 0)
        hit->distance = r->side_x - r->delta_x;
    else
        hit->distance = r->side_y - r->delta_y;
    hit->hit_x = pos_x + r->dir_x * hit->distance;
    hit->hit_y = pos_y + r->dir_y * hit->distance;
    if (hit->hit_side == 0)
        hit->side = (r->dir_x > 0) ? 0 : 1;
    else
        hit->side = (r->dir_y > 0) ? 2 : 3;
}

t_hit cast_ray(char **map, double pos_x, double pos_y, double angle)
{
    t_ray  r;
    t_hit  hit;

    init_ray(&r, pos_x, pos_y, angle);
    init_step(&r, pos_x, pos_y);
    perform_dda(map, &r, &hit);
    finalize_hit(&r, &hit, pos_x, pos_y);
    return (hit);
}