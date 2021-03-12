#include "cub3d.h"
#include "../includes/cub3d.h"



void ft_parse(char *filepath, t_conf *conf)
{
    int		fd;
    int		ret;
    char	*line;

    fd = open(filepath, O_RDONLY);
    conf = ft_calloc(sizeof(t_conf), 1);
    if (fd < 0)
        ft_exit_errcode(int errcode, t_conf *conf)
        parsing_error(res);
    res->tmp_mlx_ptr = mlx_init();
    while ((status = get_next_line(fd, &line)) > 0)
    {
        handle_line(line, res);
        free(line);
    }
    handle_line(line, res);
    free(line);
    if (!check_parsing(res))
        parsing_error(res);
    create_map(res);
    return (conf);
}