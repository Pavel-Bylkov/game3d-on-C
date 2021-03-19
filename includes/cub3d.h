#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <string.h>
# include "libft.h"

# define ERRORS_FILE "./errors/errors.txt"
# define PLAYER_SPEED 0.1
# define ROTATE_SPEED 3.0
# define RAYS 200.0
# define FOV 45.0
# ifndef INF
#  define INF 100000000.0
# endif
# define SCALE 64
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_ESCAPE 53

typedef struct	s_keys
{
    int k_left;
    int k_right;
    int k_w;
    int k_a;
    int k_s;
    int k_d;
}				t_keys;

typedef struct	s_raycasting_data
{
    int	res;
    int	i;
    int	d;
    int	x;
    int	y;
    int	a;
}				t_raycasting_data;

typedef struct	s_window
{
    const char		*title;
    unsigned int	width;
    unsigned int	height;
    void			*win_ptr;
    void			*mlx_ptr;
    void			*surface;
    char			*data;
}				t_window;

typedef struct	s_texture
{
    int				width;
    int				height;
    void			*ptr;
    char			*data;
}				t_texture;

typedef struct	s_sprite
{
    int				x;
    int				y;
    float			sprite_x;
    float			sprite_y;
    float			dir_x;
    float			dir_y;
    float			inv_det;
    int				sprite_screen_x;
    int				sprite_width;
    int				sprite_height;
    int				draw_start_x;
    int				draw_end_x;
    int				draw_start_y;
    int				draw_end_y;
    unsigned char	color[4];
    float			transform_x;
    float			transform_y;
    int				texture_x;
    int				texture_y;
}				t_sprite;

typedef struct	s_ray
{
    t_texture	*texture;
    float		angle;
    float		distance;
    float		side_dist_x;
    float		side_dist_y;
    float		delta_dist_x;
    float		delta_dist_y;
    float		step_x;
    float		step_y;
    float		wall_x;
    int			map_x;
    int			map_y;
    float		ray_dir_x;
    float		ray_dir_y;
}				t_ray;

typedef struct	s_world
{
    float			angle;
    int				**map;
    t_list			*sprites;
    t_ray			**rays;
    t_texture		*texture_o;
    t_texture		*texture_e;
    t_texture		*texture_s;
    t_texture		*texture_n;
    t_texture		*texture_sprite;
    unsigned char	color_ceil[4];
    unsigned char	color_floor[4];
    int				mx;
    int				my;
    float			px;
    float			py;
    float			pz;
    float			plane_x;
    float			plane_y;
}				t_world;

typedef struct	s_game
{
    t_keys		*keys;
    t_window	*win;
    t_world		*world;
    int			save;
    void		(*draw)(struct s_game *);
}				t_game;

typedef struct	s_conf
{
    void			*tmp_mlx_ptr;
    t_texture		*texture_e;
    t_texture		*texture_w;
    t_texture		*texture_n;
    t_texture		*texture_s;
    t_texture		*texture_sprite;
    t_list			*map_tmp;
    unsigned char	**map;
    int				win_width;
    int				win_height;
    int				map_width;
    int				map_height;
    int				px;
    int				py;
    char			orientation;
    char            *err_str;
    unsigned char	ceil[3];
    unsigned char	floor[3];
    int				map_started;
}				t_conf;

typedef struct	s_rect
{
    int width;
    int height;
    int x;
    int y;
}				t_rect;

typedef struct	s_flag
{
    unsigned char R;
    unsigned char NO;
    unsigned char SO;
    unsigned char WE;
    unsigned char EA;
    unsigned char S;
    unsigned char F;
    unsigned char C;
    unsigned char posN;
    unsigned char posS;
    unsigned char posE;
    unsigned char posW;
}				t_flag;

void		f_print_err(int errcode, t_conf *conf);
void	    ft_exit_errcode(int errcode, t_conf *conf);
void        ft_parse(char *filepath, t_conf *conf);
void        clear_conf(t_conf *conf);
t_texture	*load_texture(void *mlx_ptr, char *filename);
void		del_texture(void *mlx_ptr, t_texture *texture);

#endif
