#include "cub3d.h"
#include "mlx.h"

int			draw_all(t_win_mlx *mlx)
{
    draw_background(mlx);
    raycasting(mlx);
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->win_img->ptr, 0, 0);
    return (0);
}

void		draw_pixel(t_texture *img, int x, int y, int color)
{
    char		*dst;

    dst = img->data + (y * img->line_len + x * (img->bits_per_pix / 8));
    *(unsigned int*)dst = color;
}

void		draw_background(t_win_mlx *mlx)
{
    int			x;
    int			y;

    x = 0;
    while (x < mlx->win_width)
    {
        y = 0;
        while (y < (mlx->win_height / 2))
        {
            draw_pixel(&mlx->win_img, x, y, mlx->conf->ceil);
            y++;
        }
        while (y < mlx->win_height)
        {
            draw_pixel(&mlx->win_img, x, y, mlx->conf->floor);
            y++;
        }
        x++;
    }
}