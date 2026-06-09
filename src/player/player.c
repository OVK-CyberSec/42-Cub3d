#include "../includes/cub3d.h"

/*
** close_window: destroys all mlx resources and exits cleanly.
** Bound to the window's red cross (event 17).
*/
int close_window(void *param)
{
    t_data *data;

    data = (t_data *)param;
    mlx_destroy_image(data->mlx, data->img);
    mlx_destroy_image(data->mlx, data->tex_no.img);
    mlx_destroy_image(data->mlx, data->tex_so.img);
    mlx_destroy_image(data->mlx, data->tex_we.img);
    mlx_destroy_image(data->mlx, data->tex_ea.img);
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
    return (0);
}

/*
** key_press: handles key-down events.
** WASD set flags for continuous movement; arrow keys rotate immediately;
** ESC quits cleanly.
*/
int key_press(int keycode, t_data *data)
{
    if (keycode == 119)
        data->key_w = 1;
    if (keycode == 115)
        data->key_s = 1;
    if (keycode == 97)
        data->key_a = 1;
    if (keycode == 100)
        data->key_d = 1;
    if (keycode == 65361)
        data->angle -= ROT_SPEED;
    if (keycode == 65363)
        data->angle += ROT_SPEED;
    if (keycode == 65307)
        close_window(data);
    return (0);
}

/*
** key_release: clears movement flags when WASD keys are released.
*/
int key_release(int keycode, t_data *data)
{
    if (keycode == 119)
        data->key_w = 0;
    if (keycode == 115)
        data->key_s = 0;
    if (keycode == 97)
        data->key_a = 0;
    if (keycode == 100)
        data->key_d = 0;
    return (0);
}

/* --- Movement helpers ---
** Each direction tests the new position against the map before applying it,
** providing basic wall-collision detection.
*/

static void move_forward(t_data *data, double speed)
{
    double nx;
    double ny;

    nx = data->player_x + cos(data->angle) * speed;
    ny = data->player_y + sin(data->angle) * speed;
    if (data->map[(int)ny][(int)nx] != '1')
    {
        data->player_x = nx;
        data->player_y = ny;
    }
}

static void move_backward(t_data *data, double speed)
{
    double nx;
    double ny;

    nx = data->player_x - cos(data->angle) * speed;
    ny = data->player_y - sin(data->angle) * speed;
    if (data->map[(int)ny][(int)nx] != '1')
    {
        data->player_x = nx;
        data->player_y = ny;
    }
}

static void strafe_right(t_data *data, double speed)
{
    double nx;
    double ny;

    nx = data->player_x - sin(data->angle) * speed;
    ny = data->player_y + cos(data->angle) * speed;
    if (data->map[(int)ny][(int)nx] != '1')
    {
        data->player_x = nx;
        data->player_y = ny;
    }
}

static void strafe_left(t_data *data, double speed)
{
    double nx;
    double ny;

    nx = data->player_x + sin(data->angle) * speed;
    ny = data->player_y - cos(data->angle) * speed;
    if (data->map[(int)ny][(int)nx] != '1')
    {
        data->player_x = nx;
        data->player_y = ny;
    }
}

/*
** update_player: applies all active movement flags each frame.
*/
void update_player(t_data *data)
{
    if (data->key_w)
        move_forward(data, MOVE_SPEED);
    if (data->key_s)
        move_backward(data, MOVE_SPEED);
    if (data->key_d)
        strafe_right(data, MOVE_SPEED);
    if (data->key_a)
        strafe_left(data, MOVE_SPEED);
}
