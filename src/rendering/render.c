#include "../includes/cub3d.h"

/*
** put_pixel: writes color at (x, y) directly into the framebuffer.
** Skips out-of-bounds pixels silently.
*/
void put_pixel(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
        return ;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

/*
** select_texture: returns the correct wall texture based on the hit face.
**   side 0 = East wall  → East texture
**   side 1 = West wall  → West texture
**   side 2 = South wall → South texture
**   side 3 = North wall → North texture
*/
t_tex *select_texture(t_data *data, t_hit hit)
{
    if (hit.side == 0)
        return (&data->tex_ea);
    else if (hit.side == 1)
        return (&data->tex_we);
    else if (hit.side == 2)
        return (&data->tex_so);
    return (&data->tex_no);
}

/*
** render: main game loop hook called every frame.
** Updates player position then redraws the scene.
*/
int render(void *param)
{
    update_player(param);
    draw_scene(param);
    return (0);
}
