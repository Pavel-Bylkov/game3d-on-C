#include <cub3d.h>
#include "../includes/cub3d.h"

t_texture	*load_texture(void *mlx_ptr, char *filename)
{
    t_texture	*res;
    int			conf[3];

    res = ft_calloc(sizeof(t_texture), 1);
    res->ptr = mlx_xpm_file_to_image(
            mlx_ptr, filename, &(res->width), &(res->height));
    if (!res->ptr)
        return (res);
    conf[0] = 32;
    conf[1] = res->width * 4;
    conf[2] = 0;
    res->data = mlx_get_data_addr(
            res->ptr, &conf[0], &conf[1], &conf[2]);
    return (res);
}

void		del_texture(void *mlx_ptr, t_texture *texture)
{
    mlx_destroy_image(mlx_ptr, texture->ptr);
    free(texture);
}