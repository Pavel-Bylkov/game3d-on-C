# include "cub3d.h"

int main(int ac, char **av)
{
    t_game	*game;
    t_conf	*conf;

    if (ac < 2 || ac > 3 || (ac == 3 && ft_strncmp(av[2], "––save", 6)))
        parsing_error(NULL);
    info = parse(av[1]);
    game = create_game(info, "Cub3D by tmarx");
    if (ac == 3)
        game->screenshot = 1;
    destroy_info(info);
    game->draw = &draw;
    start_game(game);
    stop_game(game);
    return (0);
}

