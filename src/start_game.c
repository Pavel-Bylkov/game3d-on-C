#include "cub3d.h"
#include "mlx.h"
#include <time.h>

static void	dir_n_plane_calculation(t_win_mlx *mlx)
{
    mlx->game.dir_x = 0;
    mlx->game.dir_y = 0;
    mlx->game.plane_x = 0;
    mlx->game.plane_y = 0;
    if (mlx->conf->orientation == 'N')
    {
        mlx->game.dir_y = -1;
        mlx->game.plane_x = tan(M_PI * FOV_ANGLE / 360);
    }
    else if (mlx->conf->orientation == 'S')
    {
        mlx->game.dir_y = 1;
        mlx->game.plane_x = -tan(M_PI * FOV_ANGLE / 360);
    }
    else if (mlx->conf->orientation == 'W')
    {
        mlx->game.dir_x = -1;
        mlx->game.plane_y = -tan(M_PI * FOV_ANGLE / 360);
    }
    else if (mlx->conf->orientation == 'E')
    {
        mlx->game.dir_x = 1;
        mlx->game.plane_y = tan(M_PI * FOV_ANGLE / 360);
    }
}

static void	key_init(t_win_mlx *mlx)
{
    mlx->keys.k_w = 0;
    mlx->keys.k_a = 0;
    mlx->keys.k_s = 0;
    mlx->keys.k_d = 0;
    mlx->keys.k_left = 0;
    mlx->keys.k_right = 0;
}

int			ft_game_init(t_win_mlx *mlx)
{
    mlx->game.player_x = (float)mlx->conf->px + 0.5;
    mlx->game.player_y = (float)mlx->conf->py + 0.5;
    dir_n_plane_calculation(mlx);
    mlx->game.move_speed = MOVE_SPEED * 1.5;
    mlx->game.rot_speed = ROTATE_SPEED * M_PI / 180;
    if (!(mlx->game.wall_dist_arr = (float*)malloc(
                sizeof(float) * mlx->win_width)))
        return (mlx->errcode = 155);
    if (!mlx->conf->save)
        key_init(mlx);
    return (0);
}

static int	ft_mlx_window_images_init(t_win_mlx *mlx, t_conf *conf)
{
    mlx->win_ptr = NULL;
    mlx->sprites = NULL;
    mlx->mlx_ptr = mlx->conf->tmp_mlx_ptr;
    mlx_get_screen_size(mlx->mlx_ptr, &mlx->win_width, &mlx->win_height);
    if (mlx->win_width > conf->win_width)
        mlx->win_width = conf->win_width;
    if (mlx->win_height > conf->win_height)
        mlx->win_height = conf->win_height;
    if (!conf->save && !(mlx->win_ptr = mlx_new_window(
                mlx->mlx_ptr, mlx->win_width, mlx->win_height, TITLE)))
        return (173);
    mlx->tex_ea = conf->texture_e;
    mlx->tex_we = conf->texture_w;
    mlx->tex_no = conf->texture_n;
    mlx->tex_so = conf->texture_s;
    mlx->tex_spr = conf->texture_sprite;
    return (create_win_texture(mlx));
}

void		start_game(t_win_mlx *win_mlx, t_conf *conf)
{
    win_mlx->conf = conf;
    win_mlx->errcode = 0;
    if ((win_mlx->errcode = ft_mlx_window_images_init(&win_mlx, conf)))
        ft_exit_close_win(&win_mlx);
    if (ft_game_init(&win_mlx))
        ft_exit_close_win(&win_mlx);
    sprites_init(&win_mlx);
    if (conf->save)
        screenshot(&win_mlx);
    mlx_hook(win_mlx->win_ptr, 17, 1L << 17, ft_exit_close_win, &win_mlx);
    mlx_hook(win_mlx->win_ptr, 2, 1L << 0, key_press, &win_mlx);
    mlx_hook(win_mlx->win_ptr, 3, 1L << 1, key_release, &win_mlx);
    mlx_loop_hook(win_mlx->mlx_ptr, update, &win_mlx);
}


