#include "cub3d.h"
#include "../includes/cub3d.h"


static int ft_conf_init(t_conf *conf)
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
    conf->width = 0;
    conf->height = 0;
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
}

/*
void	update(t_game *game)
{
    if (game->keys->k_w)
        go(game, 0);
    if (game->keys->k_a)
        go(game, 1);
    if (game->keys->k_s)
        go(game, 2);
    if (game->keys->k_d)
        go(game, 3);
    if (game->keys->k_left)
        rotate(game, -1);
    if (game->keys->k_right)
        rotate(game, 1);
}

void	draw(t_game *game)
{
    update(game);
    mlx_clear_window(game->win->mlx_ptr, game->win->win_ptr);
    clear_data(game->win);
    raycast(game->world);
    draw_ceil_floor(game);
    draw_rays(game);
    draw_sprites(game);
    draw_hud(game);
    if (game->save)
    {
        save_screenshot();
        stop_game(game);
    }
    mlx_put_image_to_window(game->win->mlx_ptr, game->win->win_ptr,
                            game->win->surface, 0, 0);
}
*/

void	ft_exit_errcode(int errcode, t_conf *conf)
{
    f_print_err(errcode, conf);
    clear_conf(conf);
    exit(EXIT_FAILURE);
}

int     main(int ac, char **av)
{
    /*t_game	*game;*/
    t_conf	conf;
    int     len;

    errno = 0;
    if (ac < 2 || ac > 3)
        ft_exit_errcode(150, NULL);
    len = ft_strlen(av[1]);
    if (len < 5 || ft_strncmp(&av[1][len - 4], ".cub", 5) \
            || (ft_isdigit(av[1][len - 5]) || ft_isalpha(av[1][len - 5])))
        ft_exit_errcode(152, NULL);
    if (ac == 3 && ft_strncmp(av[2], "––save", 7))
        ft_exit_errcode(153, NULL);
    ft_conf_init(&conf);
    ft_parse(av[1], &conf);
    /*game = create_game(conf, "Cub3D");
    if (ac == 3)
        game->save = 1;
    game->draw = &draw;
    clear_conf(&conf);
    game_loop(game);
    del_game(game);*/
    return (EXIT_SUCCESS);
}

