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
# define TITLE "cub3D"
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 3.0
# define RAYS 200.0
# define FOV 45.0
# define MIN_WIN_WIDTH 100
# define MIN_WIN_HEIGHT 100
# define FOV_ANGLE 66
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
# define KEY_ESC 53

typedef struct	s_keys
{
    int k_left;
    int k_right;
    int k_w;
    int k_a;
    int k_s;
    int k_d;
}				t_keys;

typedef struct	s_texture
{
    int				width;
    int				height;
    void			*ptr;
    int			    bits_per_pix;
    int			    line_len;
    int			    endian;
    char			*data;
}				t_texture;

typedef struct	s_spr
{
    int			id;
    float		x;
    float		y;
    float		dist;
    struct s_sp	*prev;
    struct s_sp	*next;
}				t_spr;

typedef struct	s_spr_vars
{
    float		dist_x;
    float		dist_y;
    float		inv_factor;
    float		transform_x;
    float		transform_y;
    int			scr_x;
    int			vert_offset;
    int			width;
    int			height;
    int			start_x;
    int			start_y;
    int			end_x;
    int			end_y;
    int			tex_x;
    int			tex_y;
}				t_spr_vars;

typedef struct	s_wall_vars
{
    int			map_x;
    int			map_y;
    float		side_dist_x;
    float		side_dist_y;
    float		delta_dist_x;
    float		delta_dist_y;
    int			step_x;
    int			step_y;
    float		camera_x;
    float		ray_dir_x;
    float		ray_dir_y;
    int			hit;
    float		wall_dist;
    int			wall_side;
    int			line_height;
    int			line_start;
    int			line_end;
    float		wall_x;
    int			tex_x;
    int			tex_y;
    float		tex_pos;
    float		tex_step;
    int			tex_mirror;
}				t_wall_vars;

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
    int	            ceil;
    int         	floor;
    int				map_started;
    int             save;
}				t_conf;

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

typedef struct	s_game
{
    float		player_x;
    float		player_y;
    float		dir_x;
    float		dir_y;
    float		plane_x;
    float		plane_y;
    float		move_speed;
    float		rot_speed;
    float		*wall_dist_arr;
    float		old_dir_x;
    float		old_dir_y;
    float		old_plane_x;
    float		old_plane_y;
}				t_game;

typedef struct	s_win_mlx
{
    int			win_width;
    int			win_height;
    t_texture	*win_img;
    t_texture	*tex_ea;
    t_texture	*tex_we;
    t_texture	*tex_no;
    t_texture	*tex_so;
    t_texture	*tex_spr;
    void		*win_ptr;
    void		*mlx_ptr;
    void		*surface;
    char		*data;
    t_keys      keys;
    t_game		game;
    t_spr		*sprites;
    int			errcode;
    t_conf      *conf;
}				t_win_mlx;

void		print_err(int errcode, t_conf *conf);
void	    ft_exit_errcode(int errcode, t_conf *conf);
int			ft_exit_close_win(t__win_mlx *mlx);
void        ft_parse(char *filepath, t_conf *conf);
void        clear_conf(t_conf *conf);
void    del_game(t_win_mlx *mlx);
t_texture	*load_texture(t_conf *conf, char *filename);
int	    create_win_texture(t_win_mlx *mlx);
void		del_texture(void *mlx_ptr, t_texture *texture);
void		start_game(t_win_mlx *win_mlx, t_conf *conf);
int			ft_game_init(t_win_mlx *mlx);
void		sprites_init(t_win_mlx *mlx);
void		screenshot(t_win_mlx *mlx);
void		raycasting(t_win_mlx *mlx);
void    create_map(t_conf *conf);
void    check_close_map(t_conf *conf);
void     check_identifiers(t_conf *conf, t_flag  *flags, char *line);
void    check_color(t_conf *conf, char *line);
void    check_texture(t_conf *conf, char *line);
void        check_resolution(t_conf *conf, char *line);
void    skip_digit(char *line, int *i);
void    skip_spaces(char *line, int *i);
int				key_release(int key, t_win_mlx *mlx);
int				key_press(int key, t_win_mlx *mlx);
int			update(t_win_mlx *mlx);
void		draw_vert_line(t_win_mlx *mlx, t_wall_vars *w_vars, int x);
int			sprites_handling(t_win_mlx *mlx);
void		draw_sprite(t_win_mlx *mlx, t_spr *sp);
void		draw_background(t_win_mlx *mlx);
void		draw_pixel(t_texture *img, int x, int y, int color);
int			draw_all(t_win_mlx *mlx);

#endif
