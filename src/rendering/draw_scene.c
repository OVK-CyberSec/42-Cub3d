#include "../includes/cub3d.h"

/*
** get_tex_x: determines the horizontal texture offset for the hit point.
** Mirrors the texture on walls hit from the opposite direction.
*/
static int get_tex_x(t_hit hit, t_tex *tex, double ray_angle)
{
    double  wall_x;
    int     tex_x;

    if (fabs(cos(ray_angle)) > fabs(sin(ray_angle)))
        wall_x = hit.hit_y;
    else
        wall_x = hit.hit_x;
    wall_x -= floor(wall_x);
    tex_x = (int)(wall_x * tex->width);
    if (cos(ray_angle) < 0)
        tex_x = tex->width - tex_x - 1;
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= tex->width)
        tex_x = tex->width - 1;
    return (tex_x);
}

/*
** compute_wall: calculates the projected wall column height and its
** screen start/end rows, clamped to the window bounds.
*/
static void compute_wall(double dist, int *start, int *end, int *height)
{
    int half;

    if (dist < 0.1)
        dist = 0.1;
    *height = (int)(WIN_H / dist);
    half = WIN_H / 2;
    *start = half - (*height / 2);
    *end = half + (*height / 2);
    if (*start < 0)
        *start = 0;
    if (*end >= WIN_H)
        *end = WIN_H - 1;
}

/*
** draw_column: renders a single vertical screen column:
**   - Ceiling: solid color above the wall.
**   - Wall:    sampled from the directional texture.
**   - Floor:   solid color below the wall.
*/
static void draw_column(t_data *d, t_column *col)
{
    int     y;
    int     tex_y;
    char    *src;
    int     color;

    y = 0;
    while (y < WIN_H)
    {
        if (y < col->start)
            put_pixel(d, col->x, y, d->ceil_color);
        else if (y <= col->end)
        {
            tex_y = (y - col->start) * col->tex->height / col->wall_h;
            if (tex_y < 0)
                tex_y = 0;
            if (tex_y >= col->tex->height)
                tex_y = col->tex->height - 1;
            src = col->tex->addr
                + (tex_y * col->tex->line_len
                    + (col->tex->bpp / 8) * col->tex_x);
            color = *(unsigned int *)src;
            put_pixel(d, col->x, y, color);
        }
        else
            put_pixel(d, col->x, y, d->floor_color);
        y++;
    }
}

/*
** render_column: casts a ray for screen column x, computes corrected distance,
** selects texture and draws the column.
*/
void render_column(t_data *d, int x, double ray)
{
    t_rayctx r;

    r.hit = cast_ray(d->map, d->player_x, d->player_y, ray);
    /* Fish-eye correction: project distance onto the view plane */
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

/*
** draw_scene: iterates over all WIN_W screen columns, casting one ray per column
** across a FOV-wide arc, then blits the completed framebuffer to the window.
*/
void draw_scene(void *param)
{
    t_data  *d;
    double  ray;
    double  step;
    int     x;

    d = (t_data *)param;
    ray = d->angle - (FOV / 2);
    step = FOV / WIN_W;
    memset(d->addr, 0, d->line_length * WIN_H);
    x = 0;
    while (x < WIN_W)
    {
        render_column(d, x, ray);
        ray += step;
        x++;
    }
    mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}
