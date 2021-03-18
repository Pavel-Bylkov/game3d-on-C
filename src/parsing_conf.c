#include "cub3d.h"
#include "../includes/cub3d.h"


void    skip_spaces(char *line, int *i)
{
    char c;

    c = line[*i];
    while (c == '\t' || c == '\v' || c == '\r' || c == '\f' || c == ' ')
    {
        *i += 1;
        c = line[*i];
    }
}

static int  ft_path_endwith(char *path, char *end)
{
    int len_path;
    int len_end;
    int min_path;

    len_path = ft_strlen(path);
    len_end = ft_strlen(end);
    min_path = len_end + 1;
    if (len_path < min_path
            || ft_strncmp(&path[len_path - len_end], end, min_path)
            || (ft_isdigit(path[len_path - min_path])
            || ft_isalpha(path[len_path- min_path])))
        return (0);
    return (1);
}

static void flag_init(t_flag *flags)
{
    flags->R = 0;
    flags->NO = 0;
    flags->SO = 0;
    flags->WE = 0;
    flags->EA = 0;
    flags->S = 0;
    flags->F = 0;
    flags->C = 0;
    flags->posN = 0;
    flags->posS = 0;
    flags->posE = 0;
    flags->posW = 0;
}

void        check_resolution(t_conf *conf, char *line)
{
    int i;

    if (line[0] == 'R')
    {
        i = 1;
        skip_spaces(line, &i);
        conf->win_width = ft_atoi(&line[i]);
        while (ft_isdigit(line[i]))
            i++;
        conf->win_height = ft_atoi(&line[i]);
        skip_spaces(line, &i);
        if (line[i])
        {
            conf->err_str = ft_strdup(line);
            ft_exit_errcode(160, conf);
        }
        if (conf->win_width < 100 || conf->win_height < 100)
            ft_exit_errcode(161, conf);
    }
}

static void    check_fileopen(char *path, t_conf *conf)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0 || close(fd) < 0)
        ft_exit_errcode(162, conf);
}

void    check_texture(t_conf *conf, char *line)
{
    t_texture   *tmp;
    int         i;

    if (line[0] != 'N' && line[0] != 'S' && line[0] != 'W' && line[0] != 'E')
        return ;
    i = 2;
    skip_spaces(line, &i);
    if (ft_path_endwith(&line[i], ".png") == 0
            && ft_path_endwith(&line[i], ".xpm") == 0)
        ft_exit_errcode(162, conf);
    check_fileopen(&line[i], conf);
    tmp = load_texture(conf->tmp_mlx_ptr, &line[i]);
    if (!ft_strncmp(line, "NO", 2))
        conf->texture_n = tmp;
    else if (!ft_strncmp(line, "SO", 2))
        conf->texture_s = tmp;
    else if (!ft_strncmp(line, "WE", 2))
        conf->texture_w = tmp;
    else if (!ft_strncmp(line, "EA", 2))
        conf->texture_e = tmp;
    else if (!ft_strncmp(line, "S ", 2))
        conf->texture_sprite = tmp;
    else
        del_texture(conf->tmp_mlx_ptr, tmp);
}

static void set_color(unsigned char *ceil_floor, int *color)
{
    ceil_floor[0] = (unsigned char)color[0];
    ceil_floor[1] = (unsigned char)color[1];
    ceil_floor[2] = (unsigned char)color[2];
}

void    check_color(t_conf *conf, char *line)
{
    int i;
    int color[3];
    int k;

    if (line[0] != 'F' && line[0] != 'C')
        return ;
    i = 1;
    k = -1;
    while (++k < 3)
    {
        skip_spaces(line, &i);
        color[k] = ft_atoi(&line[i]);
        if (color[k] < 0 || color[k] > 255)
            ft_exit_errcode(164, conf);
        while (ft_isdigit(line[i]))
            i++;
        if (k < 2 && line[i] && line[i++] != ',')
            ft_exit_errcode(163, conf);
    }
    skip_spaces(line, &i);
    if (line[i] != '\0')
        ft_exit_errcode(163, conf);
    if (line[0] == 'F')
        set_color(conf->floor, color);
    if (line[0] == 'C')
        set_color(conf->ceil, color);
}

static int  check_indifer(unsigned char *flag, char *indifer, char *line)
{
    if (line[0] && !ft_strncmp(line, indifer, ft_strlen(indifer)))
    {
        *flag += 1;
        return (1);
    }
    return (0);
}

void     check_identifiers(t_conf *conf, t_flag  *flags, char *line)
{
    int     i;
    int     no_found;

    i = 0;
    skip_spaces(line, &i);
    if (conf->map_started == 1 || line[i] == '\0' || line[i] == '1')
        return ;
    no_found = 1;
    no_found -= check_indifer(&(flags->R), "R", &line[i]);
    no_found -= check_indifer(&(flags->NO), "NO", &line[i]);
    no_found -= check_indifer(&(flags->SO), "SO", &line[i]);
    no_found -= check_indifer(&(flags->WE), "WE", &line[i]);
    no_found -= check_indifer(&(flags->EA), "EA", &line[i]);
    no_found -= check_indifer(&(flags->S), "S ", &line[i]);
    no_found -= check_indifer(&(flags->F), "F", &line[i]);
    no_found -= check_indifer(&(flags->C), "C", &line[i]);
    if (no_found == 1)
    {
        conf->err_str = ft_strdup(line);
        ft_exit_errcode(156, conf);
    }
    check_resolution(conf, &line[i]);
    check_texture(conf, &line[i]);
    check_color(conf, &line[i]);
}

static int  check_flag(unsigned char flag)
{
    if (flag == 0)
        return (165);
    if (flag > 1)
        return (157);
    return (0);
}

static void     check_all_identifiers(t_conf *conf, t_flag  *flags)
{
    int errcode;

    if (conf->map_started == 0)
        return ;
    errcode = check_flag(flags->R);
    if (!errcode)
        errcode = check_flag(flags->NO);
    if (!errcode)
        errcode = check_flag(flags->SO);
    if (!errcode)
        errcode = check_flag(flags->WE);
    if (!errcode)
        errcode = check_flag(flags->EA);
    if (!errcode)
        errcode = check_flag(flags->S);
    if (!errcode)
        errcode = check_flag(flags->F);
    if (!errcode)
        errcode = check_flag(flags->C);
    if (errcode)
        ft_exit_errcode(errcode, conf);
}

static void set_flag(t_flag *flags, char direction)
{
    if (direction == 'N')
        flags->posN += 1;
    if (direction == 'S')
        flags->posS += 1;
    if (direction == 'E')
        flags->posE += 1;
    if (direction == 'W')
        flags->posW += 1;
}

static void  check_map_lines(t_conf *conf, t_flag *flags, char *line)
{
    int i;

    i = 0;
    skip_spaces(line, &i);
    if (conf->map_started == 1 && line[i] == '\0')
        ft_exit_errcode(158, conf);
    if (conf->map_started == 0 && line[i] == '1')
    {
        conf->map_started = 1;
        while (line[++i])
            if (line[i] != '1' && line[i] != ' ')
                ft_exit_errcode(170, conf);
    }
    else if (conf->map_started == 1 && line[i] != '1')
        ft_exit_errcode(171, conf);
    while (conf->map_started && line[i])
    {
        if (ft_strnchr("102NSEW ", line[i]) < 0)
        {
            conf->err_str = ft_strdup(line);
            ft_exit_errcode(166, conf);
        }
        set_flag(flags, line[i++]);
    }
    if (conf->map_started && i > conf->map_width)
        conf->map_width = i;
}

static void check_map_last_line(t_conf *conf, char *line)
{
    int i;

    i = 0;
    if (conf->map_started == 0)
        ft_exit_errcode(158, conf);
    skip_spaces(line, &i);
    if (line[i] == '\0')
        ft_exit_errcode(159, conf);
    while (line[i])
        if (line[i] != '1' && line[i++] != ' ')
            ft_exit_errcode(166, conf);
    if (i > conf->map_width)
        conf->map_width = i;
}

static void checking_map(t_conf *conf)
{
    t_list  *tmp;
    t_flag  flags;

    flag_init(&flags);
    tmp = conf->map_tmp;
    while (tmp->next)
    {
        check_identifiers(conf, &flags, tmp->content);
        check_all_identifiers(conf, &flags);
        check_map_lines(conf, &flags, tmp->content);
        tmp = tmp->next;
        if (conf->map_started)
            conf->map_height += 1;
    }
    conf->map_height += 1;
    check_map_last_line(conf, tmp->content);
    if (conf->map_width < 3 || conf->map_height < 3 ||
            flags.posN + flags.posE + flags.posS + flags.posW == 0)
        ft_exit_errcode(168, conf);
    if (flags.posN + flags.posE + flags.posS + flags.posW > 1)
        ft_exit_errcode(167, conf);
}

static t_list *skip_indifer(t_list *map)
{
    int     i;
    char    *line;

    while (map)
    {
        i = 0;
        line = map->content;
        skip_spaces(line, &i);
        if (line[i] == '1')
            return (map);
        map = map->next;
    }
    return (map);
}

static void	create_map_line(char s, t_conf *conf, int x, int y)
{
    if (s == '0')
        conf->map[y][x] = 3;
    else if (s == '1')
        conf->map[y][x] = 1;
    else if (s == '2')
        conf->map[y][x] = 2;
    else if (s == 'N' || s == 'S' || s == 'E' || s == 'W')
    {
        conf->px = x;
        conf->py = y;
        conf->orientation = s;
        conf->map[y][x] = 3;
    }
}

void    create_map(t_conf *conf)
{
    t_list  *tmp;
    int     x;
    int     y;
    char    *line;

    conf->map = (unsigned char **)ft_calloc(sizeof(unsigned char *),
                                            conf->map_height);
    y = -1;
    while (++y < conf->map_height)
        conf->map[y] = (unsigned char *)ft_calloc(sizeof(unsigned char),
                                                  conf->map_width);
    y = -1;
    tmp = skip_indifer(conf->map_tmp);
    while (tmp && ++y < conf->map_height)
    {
        x = -1;
        line = tmp->content;
        while (++x < conf->map_width && line[x])
            create_map_line(line[x], conf, x, y);
        tmp = tmp->next;
    }
}

static void print_info_map(t_conf *conf)
{
    int x;
    int y;

    ft_putstr_fd("Texture EA : width ", 1);
    ft_putnbr_fd(conf->texture_e->width, 1);
    ft_putstr_fd(", height ", 1);
    ft_putnbr_fd(conf->texture_e->height, 1);
    ft_putstr_fd("\n", 1);
    ft_putstr_fd("Texture WE : width ", 1);
    ft_putnbr_fd(conf->texture_w->width, 1);
    ft_putstr_fd(", height ", 1);
    ft_putnbr_fd(conf->texture_w->height, 1);
    ft_putstr_fd("\n", 1);
    ft_putstr_fd("Texture NO : width ", 1);
    ft_putnbr_fd(conf->texture_n->width, 1);
    ft_putstr_fd(", height ", 1);
    ft_putnbr_fd(conf->texture_n->height, 1);
    ft_putstr_fd("\n", 1);
    ft_putstr_fd("Texture SO : width ", 1);
    ft_putnbr_fd(conf->texture_s->width, 1);
    ft_putstr_fd(", height ", 1);
    ft_putnbr_fd(conf->texture_s->height, 1);
    ft_putstr_fd("\n", 1);
    ft_putstr_fd("Texture Sprite : width ", 1);
    ft_putnbr_fd(conf->texture_sprite->width, 1);
    ft_putstr_fd(", height ", 1);
    ft_putnbr_fd(conf->texture_sprite->height, 1);
    ft_putstr_fd("\n\nWindows resolution: width ", 1);
    ft_putnbr_fd(conf->win_width, 1);
    ft_putstr_fd(", height ", 1);
    ft_putnbr_fd(conf->win_height, 1);
    ft_putstr_fd("\n\nMap size: width ", 1);
    ft_putnbr_fd(conf->map_width, 1);
    ft_putstr_fd(", height ", 1);
    ft_putnbr_fd(conf->map_height, 1);
    ft_putstr_fd("\n\nHero spawn: x - ", 1);
    ft_putnbr_fd(conf->px, 1);
    ft_putstr_fd(", y - ", 1);
    ft_putnbr_fd(conf->py, 1);
    ft_putstr_fd(", orientation - ", 1);
    ft_putchar_fd(conf->orientation, 1);
    ft_putstr_fd("\n\nColor Ceil: ", 1);
    ft_putnbr_fd(conf->ceil[0], 1);
    ft_putstr_fd(", ", 1);
    ft_putnbr_fd(conf->ceil[1], 1);
    ft_putstr_fd(", ", 1);
    ft_putnbr_fd(conf->ceil[2], 1);
    ft_putstr_fd("\n\nColor Floor: ", 1);
    ft_putnbr_fd(conf->floor[0], 1);
    ft_putstr_fd(", ", 1);
    ft_putnbr_fd(conf->floor[1], 1);
    ft_putstr_fd(", ", 1);
    ft_putnbr_fd(conf->floor[2], 1);
    ft_putstr_fd("\n\nMap array:\n", 1);
    y = -1;
    while (++y < conf->map_height)
    {
        x = -1;
        while (++x < conf->map_width)
            ft_putnbr_fd(conf->map[y][x], 1);
        ft_putstr_fd("\n", 1);
    }
}

void ft_parse(char *filepath, t_conf *conf)
{
    int		fd;
    int		ret;
    char	*line;

    if (!ft_path_endwith(filepath, ".cub"))
        ft_exit_errcode(152, conf);
    fd = open(filepath, O_RDONLY);
    if (fd < 0)
        ft_exit_errcode(151, conf);
    line = NULL;
    while (get_next_line(fd, &line) > 0)
        ft_lstadd_back(&conf->map_tmp, ft_lstnew(line));
    if (line)
        ft_lstadd_back(&conf->map_tmp, ft_lstnew(line));
    else
        ft_exit_errcode(154, conf);
    if (close(fd) < 0)
        ft_exit_errcode(151, conf);
    checking_map(conf);
    create_map(conf);
    print_info_map(conf);
}