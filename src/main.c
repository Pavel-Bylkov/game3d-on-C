#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

static void ft_conf_init(t_conf *conf)
{
    conf->tmp_mlx_ptr = mlx_init();
    if (conf->tmp_mlx_ptr == NULL)
        ft_exit_errcode(172, NULL);
    conf->texture_e = NULL;
    conf->texture_w = NULL;
    conf->texture_n = NULL;
    conf->texture_s = NULL;
    conf->texture_sprite = NULL;
    conf->map_tmp = NULL;
    conf->map = NULL;
    conf->win_width = 0;
    conf->win_height = 0;
    conf->map_width = 0;
    conf->map_height = 0;
    conf->px = 0;
    conf->py = 0;
    conf->orientation = 0;
    conf->err_str = NULL;
    conf->ceil[0] = 0;
    conf->ceil[1] = 0;
    conf->ceil[2] = 0;
    conf->floor[0] = 0;
    conf->floor[1] = 0;
    conf->floor[2] = 0;
    conf->map_started = 0;
    conf->save = 0;
}

void	ft_exit_errcode(int errcode, t_conf *conf)
{
    print_err(errcode, conf);
    clear_conf(conf);
    exit(EXIT_FAILURE);
}

int			ft_exit_close_win(t__win_mlx *mlx)
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
    ft_exit_errcode(mlx->errcode, mlx->conf);
}

int     main(int ac, char **av)
{
    t_win_mlx   win_mlx;
    t_conf      conf;

    errno = 0;
    if (ac < 2 || ac > 3)
        ft_exit_errcode(150, NULL);
    if (ac == 3 && ft_strncmp(av[2], "––save", 7))
        ft_exit_errcode(153, NULL);
    ft_conf_init(&conf);
    if (ac == 3)
        conf.save = 1;
    ft_parse(av[1], &conf);
    start_game(&win_mlx, &conf);
    mlx_loop(win_mlx.mlx_ptr);
    del_game(&win_mlx);
    return (EXIT_SUCCESS);
}

