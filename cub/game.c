#include "cub.h"

void key_up(t_data *data, double speed)
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

void key_down(t_data *data, double speed)
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

void key_right(t_data *data, double speed)
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

void key_left(t_data *data, double speed)
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

void update_player(t_data *data)
{
    double speed;

    speed = 0.05;
    if (data->key_w)
        key_up(data, speed);
    if (data->key_s)
        key_down(data, speed);
    if (data->key_d)
        key_right(data, speed);
    if (data->key_a)
        key_left(data, speed);
}