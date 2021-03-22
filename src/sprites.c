#include "cub3d.h"

static t_spr	*sprite_new(t_win_mlx *mlx, int y, int x, int id)
{
    t_spr	*sp;

    if (!(sp = (t_spr*)malloc(sizeof(t_spr))))
    {
        mlx->errcode = 155;
        ft_exit_close_win(mlx);
    }
    sp->id = id;
    sp->x = (float)x + 0.5;
    sp->y = (float)y + 0.5;
    sp->dist = 0.0;
    sp->prev = NULL;
    sp->next = NULL;
    return (sp);
}

static void	sprite_add_front(t_win_mlx *mlx, t_spr *sp)
{
    t_spr	*new_sp;

    if (mlx->sprites && sp)
    {
        new_sp = sp;
        new_sp->next = mlx->sprites;
        new_sp->next->prev = new_sp;
        mlx->sprites = new_sp;
    }
}

void		sprites_init(t_win_mlx *mlx)
{
    int		i;
    int		j;
    int		k;
    t_spr	*sp;

    k = 0;
    i = 0;
    while (++i < mlx->conf->map_height)
    {
        j = 0;
        while (++j < mlx->conf->map_width)
        {
            if (mlx->conf->map[i][j] == 2)
            {
                sp = sprite_new(mlx, i, j, ++k);
                if (mlx->sprites)
                    sprite_add_front(mlx, sp);
                else
                    mlx->sprites = sp;
            }
        }
    }
}