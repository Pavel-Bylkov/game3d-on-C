#include "cub3d.h"
#include "libft.h"

static void	del_node(void *content)
{
    free(content);
}

void		clear_conf(t_conf *conf)
{
    int y;

    if (conf && conf->map_tmp)
        ft_lstclear(&(conf->map_tmp), &del_node);
    if (conf && conf->texture_n)
        del_texture(conf->tmp_mlx_ptr, conf->texture_n);
    if (conf && conf->texture_e)
        del_texture(conf->tmp_mlx_ptr, conf->texture_e);
    if (conf && conf->texture_w)
        del_texture(conf->tmp_mlx_ptr, conf->texture_w);
    if (conf && conf->texture_s)
        del_texture(conf->tmp_mlx_ptr, conf->texture_s);
    if (conf && conf->texture_sprite)
        del_texture(conf->tmp_mlx_ptr, conf->texture_sprite);
    if (conf && conf->err_str)
        free(conf->err_str);
    if (conf && conf->map)
    {
        y = 0;
        while (y < conf->map_height && conf->map[y])
            free(conf->map[y++]);
        free(conf->map);
    }
}

void    del_game(t_win_mlx *mlx)
{
    t_spr		*sp_tmp;

    if (mlx->game.wall_dist_arr)
        free(mlx->game.wall_dist_arr);
    if (mlx->win_ptr)
        mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
    if (mlx->win_img)
        del_texture(mlx->mlx_ptr, mlx->win_img);
    if (mlx->sprites)
    {
        while (mlx->sprites)
        {
            sp_tmp = mlx->sprites->next;
            free(mlx->sprites);
            mlx->sprites = sp_tmp;
        }
    }
    free(mlx->mlx_ptr);
    clear_conf(win_mlx->conf);
}