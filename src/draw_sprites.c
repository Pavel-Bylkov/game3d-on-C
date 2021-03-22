#include "cub3d.h"

void	sprite_vars_calc(t_win_mlx *mlx, t_spr *sp, t_sp_vars *sp_vars)
{
    sp_vars->dist_x = sp->x - mlx->game.player_x;
    sp_vars->dist_y = sp->y - mlx->game.player_y;
    sp_vars->inv_factor = 1.0 / (mlx->game.plane_x * mlx->game.dir_y - \
			mlx->game.plane_y * mlx->game.dir_x);
    sp_vars->transform_x = sp_vars->inv_factor * (mlx->game.dir_y * \
			sp_vars->dist_x - mlx->game.dir_x * sp_vars->dist_y);
    sp_vars->transform_y = sp_vars->inv_factor * (-mlx->game.plane_y * \
			sp_vars->dist_x + mlx->game.plane_x * sp_vars->dist_y);
    sp_vars->scr_x = (int)((mlx->win_width / 2) * (1 + \
			sp_vars->transform_x / sp_vars->transform_y));
    sp_vars->vert_offset = (int)(mlx->win_height * 0.2 / sp_vars->transform_y);
    if ((sp_vars->height = (int)(mlx->win_height / sp_vars->transform_y)) < 0)
        sp_vars->height *= -1;
    if ((sp_vars->start_y = -sp_vars->height / 2 + mlx->win_height \
		/ 2 + sp_vars->vert_offset) < 0)
        sp_vars->start_y = 0;
    if ((sp_vars->end_y = sp_vars->height / 2 + mlx->win_height / \
		2 + sp_vars->vert_offset) >= mlx->win_height)
        sp_vars->end_y = mlx->win_height - 1;
    if ((sp_vars->width = (int)(mlx->win_height / sp_vars->transform_y)) < 0)
        sp_vars->width *= -1;
    if ((sp_vars->start_x = -sp_vars->width / 2 + sp_vars->scr_x) < 0)
        sp_vars->start_x = 0;
    if ((sp_vars->end_x = sp_vars->width / 2
                + sp_vars->scr_x) >= mlx->win_width)
        sp_vars->end_x = mlx->win_width - 1;
}

static void	draw_sprite_vert_line(t_win_mlx *mlx, t_sp_vars *sp_vars, int x)
{
    int		y;
    int		d;
    int		color;

    y = sp_vars->start_y;
    while (y < sp_vars->end_y)
    {
        d = (y - sp_vars->vert_offset) * 256 - \
			mlx->win_height * 128 + sp_vars->height * 128;
        sp_vars->tex_y = ((d * mlx->tex_spr->height) / sp_vars->height) \
							/ 256;
        color = *(int*)(mlx->tex_spr->data + ((sp_vars->tex_x + \
				(sp_vars->tex_y * mlx->tex_spr->width)) * \
				(mlx->tex_spr->bits_per_pix / 8)));
        if (color & 0x00FFFFFF)
            draw_pixel(&mlx->win_img, x, y, color);
        y++;
    }
}

void		draw_sprite(t_win_mlx *mlx, t_spr *sp)
{
    int			x;
    t_sp_vars	sp_vars;

    sprite_vars_calc(mlx, sp, &sp_vars);
    x = sp_vars.start_x;
    while (x < sp_vars.end_x)
    {
        sp_vars.tex_x = (int)(256 * (x - (-sp_vars.width / 2 + \
							sp_vars.scr_x)) * mlx->tex_spr->width / \
							sp_vars.width) / 256;
        if (sp_vars.transform_y > 0 && x > 0 && x < mlx->win_width && \
				sp_vars.transform_y < mlx->game.wall_dist_arr[x])
            draw_sprite_vert_line(mlx, &sp_vars, x);
        x++;
    }
}


static int	swap_sprites_info(t_spr *a, t_spr *b)
{
    float	tmp_float;
    int     tmp_int;

    tmp_int = b->id;
    b->id = a->id;
    a->id = tmp_int;
    tmp_float = b->x;
    b->x = a->x;
    a->x = tmp_float;
    tmp_float = b->y;
    b->y = a->y;
    a->y = tmp_float;
    tmp_float = b->dist;
    b->dist = a->dist;
    a->dist = tmp_float;
    return (1);
}

static void	sprites_list_sort_by_dist(t_win_mlx *mlx)
{
    t_spr	*sp;
    int		flag;

    sp = mlx->sprites;
    flag = 1;
    while (swap_flag)
    {
        flag = 0;
        while (sp->next)
        {
            if (sp->dist < sp->next->dist)
                flag = swap_sprites_info(sp, sp->next);
            sp = sp->next;
        }
        sp = mlx->sprites;
    }
}

static void	sprites_dist_calculat(t_win_mlx *mlx)
{
    t_spr	*sp;

    sp = mlx->sprites;
    while (sp)
    {
        sp->dist = sqrt(pow(mlx->game.player_x - sp->x, 2) + \
						pow(mlx->game.player_y - sp->y, 2));
        sp = sp->next;
    }
}

int			sprites_handling(t_win_mlx *mlx)
{
    t_spr	*sprite;

    if (!mlx->sprites)
        return (0);
    sprites_dist_calculat(mlx);
    sprites_list_sort_by_dist(mlx);
    sprite = mlx->sprites;
    while (sprite)
    {
        draw_sprite(mlx, sprite);
        sprite = sprite->next;
    }
    return (0);
}
