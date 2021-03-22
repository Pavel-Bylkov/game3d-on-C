#include "cub3d.h"
#include "libft.h"

static char	*get_filename(t_win_mlx *mlx)
{
    char	*filename;
    char	*name_index;
    char	*tmp;
    int		fd;
    int		i;

    i = 2;
    filename = ft_strdup("screenshot.bmp");
    while ((fd = open(filename, O_RDONLY)) > 0)
    {
        free(filename);
        if (close(fd) < 0)
            mlx->errcode = 177;
        if (mlx->errcode)
            return (NULL);
        if (!(name_index = ft_itoa(i++)) || \
			!(tmp = ft_strjoin("screenshot_", name_index)) || \
			!(filename = ft_strjoin(tmp, ".bmp")))
            mlx->errcode = 155;
        free((name_index) ? name_index : NULL);
        free((tmp) ? tmp : NULL);
        if (!filename)
            return (NULL);
    }
    return (filename);
}

static int	bmp_image_write(t_win_mlx *mlx, char *bitmap_file_header, \
															char *dib_header)
{
    int		fd;
    char	*filename;
    int		i;
    int		win_width;

    i = 0;
    win_width = mlx->win_img->bits_per_pix / 8 * mlx->win_width;
    if (!(filename = get_filename(mlx)))
        return (mlx->errcode);
    if ((fd = open(filename, O_RDWR | O_CREAT, 0664)) < 0)
        return (fd);
    write(fd, bitmap_file_header, 14);
    write(fd, dib_header, 40);
    while (i < mlx->win_height)
        write(fd, mlx->win_img->data + i++ * mlx->win_img->line_len, win_width);
    ft_putstr_fd(filename, 1);
    ft_putstr_fd(" saved\n", 1);
    free(filename);
    return ((close(fd) < 0) ? 177 : 0);
}

static void	bmp_headers_generate(t_win_mlx *mlx, char *bitmap_file_header, \
															char *dib_header)
{
    int		file_size;

    file_size = 14 + 40 + mlx->win_width * mlx->win_height * \
			mlx->win_img->bits_per_pix / 8;
    bitmap_file_header[0] = 'B';
    bitmap_file_header[1] = 'M';
    bitmap_file_header[2] = (char)(file_size);
    bitmap_file_header[3] = (char)(file_size >> 8);
    bitmap_file_header[4] = (char)(file_size >> 16);
    bitmap_file_header[5] = (char)(file_size >> 24);
    bitmap_file_header[10] = (char)(14 + 40);
    dib_header[0] = (char)(40);
    dib_header[4] = (char)(mlx->win_width);
    dib_header[5] = (char)(mlx->win_width >> 8);
    dib_header[6] = (char)(mlx->win_width >> 16);
    dib_header[7] = (char)(mlx->win_width >> 24);
    dib_header[8] = (char)(-mlx->win_height);
    dib_header[9] = (char)(-mlx->win_height >> 8);
    dib_header[10] = (char)(-mlx->win_height >> 16);
    dib_header[11] = (char)(-mlx->win_height >> 24);
    dib_header[12] = (char)(1);
    dib_header[14] = (char)(mlx->win_img->bits_per_pix);
}

void		screenshot(t_win_mlx *mlx)
{
    char	bitmap_file_header[14];
    char	dib_header[40];

    ft_bzero(bitmap_file_header, 14);
    ft_bzero(dib_header, 40);
    draw_background(mlx);
    raycasting(mlx);
    bmp_headers_generate(mlx, bitmap_file_header, dib_header);
    mlx->errcode = bmp_image_write(mlx, bitmap_file_header, dib_header);
    ft_exit_close_win(mlx);
}