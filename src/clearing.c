#include "cub3d.h"
#include "../includes/cub3d.h"

static void	del_node(void *content)
{
    free(content);
}

void		clear_conf(t_conf *conf)
{
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

}