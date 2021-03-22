#include "cub3d.h"


static int	get_pix_color(t_win_mlx *mlx, t_wall_vars *w_vars)
{
    t_texture	*tex_img;

    tex_img = NULL;
    if (w_vars->wall_side == 0)
        tex_img = mlx->tex_no;
    else if (w_vars->wall_side == 1)
        tex_img = mlx->tex_so;
    else if (w_vars->wall_side == 2)
        tex_img = mlx->tex_we;
    else if (w_vars->wall_side == 3)
        tex_img = mlx->tex_ea;
    w_vars->tex_y = (int)w_vars->tex_pos & (tex_img->height - 1);
    return (*(int*)(tex_img->data + ((w_vars->tex_x + (w_vars->tex_y * \
							tex_img->width)) * (tex_img->bits_per_pix / 8))));
}


static void	tex_vars_calculat(t_win_mlx *mlx, t_wall_vars *w_vars)
{
    t_texture	*tex;

    tex = NULL;
    w_vars->wall_x = (w_vars->wall_side > 1) ? mlx->game.player_y + \
		w_vars->wall_dist * w_vars->ray_dir_y : mlx->game.player_x + \
		w_vars->wall_dist * w_vars->ray_dir_x;
    w_vars->wall_x -= (int)(w_vars->wall_x);
    if (w_vars->wall_side == 0)
        tex = mlx->tex_no;
    else if (w_vars->wall_side == 1)
        tex = mlx->tex_so;
    else if (w_vars->wall_side == 2)
        tex = mlx->tex_we;
    else if (w_vars->wall_side == 3)
        tex = mlx->tex_ea;
    if (w_vars->wall_side == 1 || w_vars->wall_side == 2)
        w_vars->tex_mirror = 1;
    else
        w_vars->tex_mirror = 0;
    w_vars->tex_x = (!w_vars->tex_mirror) ? (int)(w_vars->wall_x * \
		(float)(tex->width)) : (int)((float)(tex->width) - \
		w_vars->wall_x * (float)(tex->width) - 1);
    w_vars->tex_step = 1.0 * tex->height / w_vars->line_height;
    w_vars->tex_pos = (w_vars->line_start - mlx->win_height / 2 + \
							w_vars->line_height / 2) * w_vars->tex_step;
}

void		draw_vert_line(t_win_mlx *mlx, t_wall_vars *w_vars, int x)
{
    int			color;
    int			y;

    w_vars->line_height = (int)((mlx->win_height / w_vars->wall_dist) * 1.25);
    w_vars->line_start = mlx->win_height / 2 - w_vars->line_height / 2;
    if (w_vars->line_start < 0)
        w_vars->line_start = 0;
    w_vars->line_end = mlx->win_height / 2 + w_vars->line_height / 2;
    if (w_vars->line_end >= mlx->win_height)
        w_vars->line_end = mlx->win_height - 1;
    y = w_vars->line_start;
    tex_vars_calculat(mlx, w_vars);
    while (y <= w_vars->line_end)
    {
        color = get_pix_color(mlx, w_vars);
        w_vars->tex_pos += w_vars->tex_step;
        draw_pixel(&mlx->img, x, y++, color);
    }
}
