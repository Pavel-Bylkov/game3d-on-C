#include "cub3d.h"
#include "../includes/cub3d.h"

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

static int	ft_isspace(char c)
{
    if (c == '\t' || c == '\v' || c == '\r' || c == '\f' || c == ' ')
        return (1);
    return (0);
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

void        check_parsing_indifer(t_conf *conf, char *line)
{

}

void     check_identifiers(t_conf *conf, t_flag  *flags, char *line)
{
    int     i;
    int     no_found;

    i = 0;
    while (ft_isspace(line[i]))
        i++;
    if (conf->map_started == 1 || line[i] == '\0' || line[i] == '1')
        return ;
    no_found = 1;
    no_found -= check_indifer(&flags->R, "R", &line[i]);
    no_found -= check_indifer(&flags->NO, "NO", &line[i]);
    no_found -= check_indifer(&flags->SO, "SO", &line[i]);
    no_found -= check_indifer(&flags->WE, "WE", &line[i]);
    no_found -= check_indifer(&flags->EA, "EA", &line[i]);
    no_found -= check_indifer(&flags->S, "S", &line[i]);
    no_found -= check_indifer(&flags->F, "F", &line[i]);
    no_found -= check_indifer(&flags->C, "C", &line[i]);
    if (no_found == 1)
    {
        conf->err_str = ft_strdup(line);
        ft_exit_errcode(156, conf);
    }
    check_parsing_indifer(conf, &line[i]);
}

static int  check_flag(unsigned char *flag)
{
    if (*flag == 1)
        return (0);
    if (*flag == 0)
        return (165);
    if (*flag > 1)
        return (157);
}

static void     check_all_identifiers(t_conf *conf, t_flag  *flags)
{
    int errcode;

    if (conf->map_started == 0)
        return ;
    errcode = check_flag(&flags->R);
    if (!errcode)
        errcode = check_flag(&flags->NO);
    if (!errcode)
        errcode = check_flag(&flags->SO);
    if (!errcode)
        errcode = check_flag(&flags->WE);
    if (!errcode)
        errcode = check_flag(&flags->EA);
    if (!errcode)
        errcode = check_flag(&flags->S);
    if (!errcode)
        errcode = check_flag(&flags->F);
    if (!errcode)
        errcode = check_flag(&flags->C);
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
    while (ft_isspace(line[i]))
        i++;
    if (conf->map_started == 1 && line[i] == '\0')
        ft_exit_errcode(158, conf);
    if (conf->map_started == 0 && line[i] == '1')
    {
        conf->map_started = 1;
        while (line[++i])
            if (line[i] != '1' && line[i] != ' ')
                ft_exit_errcode(170, conf);
    }
    while (conf->map_started && line[i])
    {
        if (ft_strnchr("102NSEW ", line[i]) < 0)
        {
            conf->err_str = ft_strdup(line);
            ft_exit_errcode(166, conf);
        }
        set_flag(flags, line[i++]);
    }
    if (i > conf->map_width)
        conf->map_width = i;
}

static void check_map_last_line(t_conf *conf, char *line)
{
    int i;

    i = 0;
    if (conf->map_started == 0)
        ft_exit_errcode(158, conf);
    while (ft_isspace(line[i]))
        i++;
    if (line[i] == '\0')
        ft_exit_errcode(159, conf);
    while (line[++i])
        if (line[i] != '1' && line[i] != ' ')
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
        check_identifiers(conf, &flags, tmp->content))
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

void ft_parse(char *filepath, t_conf *conf)
{
    int		fd;
    int		ret;
    char	*line;

    fd = open(filepath, O_RDONLY);
    if (fd < 0)
        ft_exit_errcode(-1, NULL);
    while (get_next_line(fd, &line))
        ft_lstadd_back(&conf->map_tmp, ft_lstnew(line));
    ft_lstadd_back(&conf->map_tmp, ft_lstnew(line));
    checking_map(conf);
    if (!check_parsing(conf))
        parsing_error(conf);
    create_map(conf);
    return (conf);
}