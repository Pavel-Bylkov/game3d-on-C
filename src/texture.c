#include <cub3d.h>
#include "libft.h"
#include "mlx.h"

t_texture	*load_texture(t_conf *conf, char *filename)
{
    t_texture	*res;

    res = ft_calloc(sizeof(t_texture), 1);
    if (!res)
        ft_exit_errcode(155, conf);
    res->ptr = mlx_xpm_file_to_image(
            conf->tmp_mlx_ptr, filename, &(res->width), &(res->height));
    if (!res->ptr)
        ft_exit_errcode(176, conf);
    res->bits_per_pix = 32;
    res->line_len = res->width * 4;
    res->endian = 0;
    res->data = mlx_get_data_addr(
            res->ptr, &res->bits_per_pix, &res->line_len, &res->endian);
    if (!res->data)
        ft_exit_errcode(175, conf);
    return (res);
}

int	    create_win_texture(t_win_mlx *mlx)
{
    mlx->win_img = ft_calloc(sizeof(t_texture), 1);
    if (!mlx->win_img)
        return(155);
    mlx->win_img->ptr = mlx_new_image(
            mlx->mlx_ptr, mlx->win_width, mlx->win_height)
    if (!mlx->win_img->ptr)
        return (174);
    mlx->win_img->data = mlx_get_data_addr(
            mlx->win_img->ptr,&mlx->win_img->bits_per_pix,
            &mlx->win_img->line_len, &mlx->win_img->endian)
    if (!mlx->win_img->data)
        return (175);
    return(0);
}

void		del_texture(void *mlx_ptr, t_texture *texture)
{
    mlx_destroy_image(mlx_ptr, texture->ptr);
    free(texture);
}