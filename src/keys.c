#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

static void	ft_move(t_win_mlx *mlx, int dir)
{
    if (mlx->conf->map[(int)mlx->game.player_y][(int)(mlx->game.player_x
            + dir * (mlx->game.dir_x * mlx->game.move_speed))] == 3)
        mlx->game.player_x += dir * (mlx->game.dir_x * mlx->game.move_speed);
    if (mlx->conf->map[(int)(mlx->game.player_y + dir * (mlx->game.dir_y
            * mlx->game.move_speed))][(int)mlx->game.player_x] == 3)
        mlx->game.player_y += dir * (mlx->game.dir_y * mlx->game.move_speed);
}

static void	ft_strafe(t_win_mlx *mlx, int dir)
{
    if (mlx->conf->map[(int)mlx->game.player_y][(int)(mlx->game.player_x
            + dir * (mlx->game.plane_x * mlx->game.move_speed))] == 3)
        mlx->game.player_x += dir * (mlx->game.plane_x * mlx->game.move_speed);
    if (mlx->conf->map[(int)(mlx->game.player_y + dir * (mlx->game.plane_y
            * mlx->game.move_speed))][(int)mlx->game.player_x] == 3)
        mlx->game.player_y += dir * (mlx->game.plane_y * mlx->game.move_speed);
}

static void	ft_rotate(t_win_mlx *mlx, int dir)
{
    mlx->game.old_dir_x = mlx->game.dir_x;
    mlx->game.dir_x = mlx->game.dir_x * cos(dir * mlx->game.rot_speed) - \
						mlx->game.dir_y * sin(dir * mlx->game.rot_speed);
    mlx->game.dir_y = mlx->game.old_dir_x * sin(dir * mlx->game.rot_speed) + \
						mlx->game.dir_y * cos(dir * mlx->game.rot_speed);
    mlx->game.old_plane_x = mlx->game.plane_x;
    mlx->game.plane_x = mlx->game.plane_x * cos(dir * mlx->game.rot_speed) - \
						mlx->game.plane_y * sin(dir * mlx->game.rot_speed);
    mlx->game.plane_y = mlx->game.old_plane_x * sin(dir * mlx->game.rot_speed) \
						+ mlx->game.plane_y * cos(dir * mlx->game.rot_speed);
}

int			update(t_win_mlx *mlx)
{
    mlx_do_sync(mlx->mlx_ptr);
    if (mlx->keys.k_w && !mlx->keys.k_s)
        ft_move(mlx, 1);
    if (mlx->keys.k_s && !mlx->keys.k_w)
        ft_move(mlx, -1);
    if (mlx->keys.k_a && !mlx->keys.k_d)
        ft_strafe(mlx, -1);
    if (mlx->keys.k_d && !mlx->keys.k_a)
        ft_strafe(mlx, 1);
    if (mlx->keys.k_left && !mlx->keys.k_right)
        ft_rotate(mlx, -1);
    if (mlx->keys.k_right && !mlx->keys.k_left)
        ft_rotate(mlx, 1);
    return (draw_all(mlx));
}

int				key_press(int key, t_win_mlx *mlx)
{
    if (key == KEY_ESC)
        ft_exit_close_win(mlx);
    else if (key == KEY_W)
        mlx->keys.k_w = 1;
    else if (key == KEY_A)
        mlx->keys.k_a = 1;
    else if (key == KEY_S)
        mlx->keys.k_s = 1;
    else if (key == KEY_D)
        mlx->keys.k_d = 1;
    else if (key == KEY_LEFT)
        mlx->keys.k_left = 1;
    else if (key == KEY_RIGHT)
        mlx->keys.k_right = 1;
    return (0);
}

int				key_release(int key, t_win_mlx *mlx)
{
    if (key == KEY_W)
        mlx->keys.k_w = 0;
    else if (key == KEY_A)
        mlx->keys.k_a = 0;
    else if (key == KEY_S)
        mlx->keys.k_s = 0;
    else if (key == KEY_D)
        mlx->keys.k_d = 0;
    else if (key == KEY_LEFT)
        mlx->keys.k_left = 0;
    else if (key == KEY_RIGHT)
        mlx->keys.k_right = 0;
    return (0);
}
