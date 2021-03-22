#include "cub3d.h"
#include "libft.h"
#include <math.h>

static void	check_wall_hit_n_dist_calculat(t_win_mlx *mlx, \
                                            t_wall_vars *w_vars)
{
    w_vars->hit = 0;
    while (!w_vars->hit)
    {
        if (w_vars->side_dist_x < w_vars->side_dist_y)
        {
            w_vars->side_dist_x += w_vars->delta_dist_x;
            w_vars->map_x += w_vars->step_x;
            w_vars->wall_side = (w_vars->ray_dir_x < 0) ? 2 : 3;
        }
        else
        {
            w_vars->side_dist_y += w_vars->delta_dist_y;
            w_vars->map_y += w_vars->step_y;
            w_vars->wall_side = (w_vars->ray_dir_y < 0) ? 0 : 1;
        }
        if (mlx->conf->map[w_vars->map_y][w_vars->map_x] < 2)
            w_vars->hit = 1;
    }
    if (w_vars->wall_side > 1)
        w_vars->wall_dist = (w_vars->map_x - mlx->game.player_x + \
				(1 - w_vars->step_x) / 2) / w_vars->ray_dir_x;
    else
        w_vars->wall_dist = (w_vars->map_y - mlx->game.player_y + \
				(1 - w_vars->step_y) / 2) / w_vars->ray_dir_y;
}

static void	step_n_side_dist_calculat(t_win_mlx *mlx, t_wall_vars *w_vars)
{
    if (w_vars->ray_dir_x < 0)
    {
        w_vars->step_x = -1;
        w_vars->side_dist_x = (mlx->game.player_x - w_vars->map_x) * \
			w_vars->delta_dist_x;
    }
    else
    {
        w_vars->step_x = 1;
        w_vars->side_dist_x = (1.0 + w_vars->map_x - mlx->game.player_x) * \
			w_vars->delta_dist_x;
    }
    if (w_vars->ray_dir_y < 0)
    {
        w_vars->step_y = -1;
        w_vars->side_dist_y = (mlx->game.player_y - w_vars->map_y) * \
			w_vars->delta_dist_y;
    }
    else
    {
        w_vars->step_y = 1;
        w_vars->side_dist_y = (1.0 + w_vars->map_y - mlx->game.player_y) * \
			w_vars->delta_dist_y;
    }
}

static void	delta_dist_calculat(t_wall_vars *w_vars)
{
    if (!w_vars->ray_dir_y)
        w_vars->delta_dist_x = 0;
    else
        w_vars->delta_dist_x = (!w_vars->ray_dir_x) ? 1 : \
									fabs(1 / w_vars->ray_dir_x);
    if (!w_vars->ray_dir_x)
        w_vars->delta_dist_y = 0;
    else
        w_vars->delta_dist_y = (!w_vars->ray_dir_y) ? 1 : \
									fabs(1 / w_vars->ray_dir_y);
}

void		raycasting(t_win_mlx *mlx)
{
    int			x;
    t_wall_vars w_vars;

    w_vars.tex_mirror = 0;
    x = 0;
    while (x < mlx->win_width)
    {
        w_vars.camera_x = 2 * x / (float)mlx->win_width - 1;
        w_vars.ray_dir_x = mlx->game.dir_x + mlx->game.plane_x * \
								w_vars.camera_x;
        w_vars.ray_dir_y = mlx->game.dir_y + mlx->game.plane_y * \
								w_vars.camera_x;
        w_vars.map_x = (int)mlx->game.player_x;
        w_vars.map_y = (int)mlx->game.player_y;
        delta_dist_calculat(&w_vars);
        step_n_side_dist_calculat(mlx, &w_vars);
        check_wall_hit_n_dist_calculat(mlx, &w_vars);
        mlx->game.wall_dist_arr[x] = w_vars.wall_dist;
        draw_vert_line(mlx, &w_vars, x++);
    }
    sprites_handling(mlx);
}

