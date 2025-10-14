#include "../header/cub.h"

int valid_map_arg(char *arg)
{
	char    *s;

	s = ft_strnstr(arg, ".cub", ft_strlen(arg));
	if (s == NULL)
	{
		ft_putstr_fd("INVALID MAP FILE !\n", 2);
		return (0);
	}
	else if (ft_strlen(s) == 4 && ft_strncmp(s, ".cub", 4) == 0)
		return (1);
	ft_putstr_fd("INVALID MAP FILE !\n", 2);
	return (0);
}

int	add_content(t_cred_list **list, char *content)
{
	t_cred_list	*node;
	t_cred_list	*tmp;

	tmp = NULL;
	node = malloc(sizeof(t_cred_list));
	if (!node || !list || !content)
		return (0);
	node->content = content;
	node->next = NULL;
	if (!*list)
	{
		*list = node;
		return (1);
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (1);
}

void    print_td(char **str)
{
	int i = 0;
	while (str && str[i])
	{
		printf("%s", str[i]);
		i++;
	}
}

void    print_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

int td_len(char **td)
{
	int i = 0;
	while (td && td[i])
		i++;
	return (i);
}

char	**convert_to_td(t_cred_list *map_list)
{
	char	**td;
	int		len;
	int		i;

	i = 0;
	len = get_list_size(map_list);
	td = malloc(sizeof(char *) * len);
	td[len] = NULL;
	while (map_list && i < len)
	{
		td[i] = ft_strdup(map_list->content);
		map_list = map_list->next;
		i++;
	}
	return (td);
}

int	get_list_size(t_cred_list *map_list)
{
	t_cred_list	*tmp;
	int		i;

	i = 0;
	tmp = map_list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	free_list(t_cred_list *list)
{
	t_cred_list	*tmp;

	tmp = NULL;
	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
	free(list);
}

int	check_content_order(t_cred_list *list)
{
	t_cred_list	*tmp;
	int			priority_flag;

	priority_flag = 0;
	tmp = list;
	while (tmp && !strcmp(tmp->content, "\n"))
		tmp = tmp->next;
	if (tmp && is_map_line(tmp->content))
		return (printf("map line detected in the wrong order !\n"), 0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "NO", 2) || !ft_strncmp(tmp->content, "SO", 2)
			|| !ft_strncmp(tmp->content, "WE", 2) || !ft_strncmp(tmp->content, "EA", 2)
			|| !ft_strncmp(tmp->content, "F", 1) || !ft_strncmp(tmp->content, "C", 1))
			priority_flag++;
		 if (is_map_line(tmp->content) && priority_flag < 6)
			return (printf("map line detected in the wrong order !\n"), 0);
		tmp = tmp->next;
	}
	return (1);
}

t_cred_list	*grap_credantials(int fd)
{
	t_cred_list	*list;
	char		*line;
	char		*content;

	content = NULL;
	line = get_next_line(fd);
	list = malloc(sizeof(t_cred_list));
	if (!list || !line)
		return (NULL);
	list = NULL;
	while (line)
	{
		if (!strcmp(line, "\n") || !line[0])
		{
			line = get_next_line(fd);
			continue ;
		}
		if (!is_map_line(line))
			content = ft_strtrim(line, " ");
		else if (!content)
			return (free_list(list), NULL);
		if (!is_map_line(line))
		{
			if (!add_content(&list, content))
				return (free_list(list), NULL);
		}
		else
		{
			if (!add_content(&list, line))
				return (free_list(list), NULL);
		}
		line = get_next_line(fd);
	}
	return (list);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != '\n'
			&& line[i] != 'W' && line[i] != 'S' && line[i] != 'N' && line[i] != 'N')
			return (0);
		i++;
	}
	return (1);	
}

int	check_dup(t_cred_list *list, char *to_check, int len)
{
	t_cred_list	*tmp;
	int			counter;

	counter = 0;
	tmp = list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, to_check, len))
			counter++;
		tmp = tmp->next;
	}
	return (counter);
}

int	missing_or_dup(t_cred_list *list)
{
 	t_cred_list *tmp;
	int			checker;

	checker = 0;
	tmp = list;
	if (check_dup(list, "SO", 2) > 1 || check_dup(list, "WE", 2) > 1 ||  check_dup(list, "EA", 2) > 1
		|| check_dup(list, "NO", 2) > 1 || check_dup(list, "C", 1) > 1 ||check_dup(list, "F", 1) > 1)
		return (printf("error DUPLICATED lines in map file !\n"), 0);
	if (!check_dup(list, "SO", 2) || !check_dup(list, "WE", 2) || !check_dup(list, "EA", 2)
		|| !check_dup(list, "NO", 2) || !check_dup(list, "C", 1) || !check_dup(list, "F", 1))
		return (printf("error MISSING lines in map file !\n"), 0);
	return (1);
}

char	*get_wanted_line(t_cred_list *list, char *wanted)
{
	t_cred_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, wanted,ft_strlen(wanted)))
			return (ft_strdup(tmp->content));
		tmp = tmp->next;
	}
	return (NULL);
}

int	asign_texters(t_cred_list *list, t_cub **cub)
{
	if(!cub)
		return (0);
	(*cub)->no_texture = get_wanted_line(list, "NO");
	(*cub)->so_texture = get_wanted_line(list, "SO");
	(*cub)->we_texture = get_wanted_line(list, "WE");
	(*cub)->ea_texture = get_wanted_line(list, "EA");
	if (!(*cub)->no_texture || !(*cub)->so_texture 
		|| !(*cub)->ea_texture || !(*cub)->we_texture)
		return (printf("moshkila am3lm"), 0);
	return (1);
}

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	a_valid_argb(char *str)
{
	int	comma_counter;
	int	i;

	i = 0;
	comma_counter = 0;
	while (str && str[i])
	{
		if (str[i] == ',')
			comma_counter++;
		i++;
	}
	if (comma_counter > 2 || comma_counter < 2)
			return (ft_putstr_fd ("value must be between 0 && 255\n", 2), 0);
	return (1);
}

int	map_size(t_cred_list *list)
{
	t_cred_list	*tmp;
	int			counter;

	counter = 0;
	tmp = list;
	while (tmp && !is_map_line(tmp->content))
		tmp = tmp->next;
	while (tmp)
	{
		counter++;
		tmp = tmp->next;
	}
	return (counter);
}

char	**get_map(t_cred_list *list)
{
	t_cred_list	*tmp;
	char		**map;
	int			index;

	map = malloc(sizeof(char *) * map_size(list) + 1);
	if(!map)
		return (NULL);
	map[map_size(list)] = NULL;
	tmp = list;
	while (tmp && !is_map_line(tmp->content))
		tmp = tmp->next;
	while (tmp && is_map_line(tmp->content))
	{
		map[index] = ft_strdup(tmp->content);
		index++;
		tmp = tmp->next;
	}
	return (map);
}

int	asign_map(t_cred_list *list, t_cub **cub)
{
	char	**map;

	map = get_map(list);
	if (!map)
		return (0);
	if (!parse_map(map, cub))
		return (0);
	return (1);
}

int	asign_colors(t_cred_list *list, t_cub **cb_st)
{
	int		i;
	char	**c;
	char	**f;
	char	*tmp;
	char	*tmp1;
	
	i = 0;
	tmp1 = get_wanted_line(list, "C");
	tmp = get_wanted_line(list, "F");
	if (!tmp1 || !tmp)
		return (0);
	if (!a_valid_argb(tmp1) || !a_valid_argb(tmp))
		return (printf("error\n"), 0);
	c = ft_split(tmp1 + 2, ',');
	f = ft_split(tmp + 2, ',');
	if (!c || !f)
		return (0);
	(*cb_st)->floor_color[0] = ft_atoi(f[0]);
	(*cb_st)->floor_color[1] = ft_atoi(f[1]);
	(*cb_st)->floor_color[2] = ft_atoi(f[2]);
	(*cb_st)->ceiling_color[0] = ft_atoi(c[0]);
	(*cb_st)->ceiling_color[1] = ft_atoi(c[1]);
	(*cb_st)->ceiling_color[2] = ft_atoi(c[2]);
	if ((*cb_st)->floor_color[0] > 255 || (*cb_st)->ceiling_color[1] > 255
		|| (*cb_st)->floor_color[1] > 255 || (*cb_st)->ceiling_color[0] > 255
		|| (*cb_st)->floor_color[2] > 255 || (*cb_st)->ceiling_color[2] > 255)
			return (ft_putstr_fd ("value must be between 0 && 255\n", 2), 0);
	return (1);
}

int	one_player_on_map(char **map)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = 0;
	while (map && map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'S'
				|| map[y][x] == 'E')
				count++;
			x++;
		}
		y++;
	}
	if (count != 1)
		return (ft_putstr_fd("one player should be on map\n", 2), 0);
	return (1);
}

void	get_player_pos(t_cub **cb)
{
	int		x;
	int		y;
	char	**map;

	if (!cb || !*cb || !(*cb)->map)
		return;
	y = 0;
	map = (*cb)->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'S'
				|| map[y][x] == 'E')
			{
				(*cb)->plyer_pos.x = x;
				(*cb)->plyer_pos.y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	closed_wall(char *map_line)
{
	int		i;
	char	*line;

	i = 0;
	line = ft_strtrim(map_line, "  ");
	if (!line)
		return (0);
	while (line && line[i])
	{
		if (line[i] != '1' || line[i] != ' ')
		{
			printf("%s\n", line);
			return (printf("map must be surrended by walls \n"), 0);
		}
		i++;
	}
	return (1);
}

int	parse_map(char **map, t_cub **cb_st)
{
	int	y;
	int max_lines;

	if (!map || !map[0])
		return (ft_putstr_fd("|| EMPTY MAP ! ||", 2), 0);
	max_lines = td_len(map);
	if (!closed_wall(map[0]))
		return (0);
	y = 1;
	while (y < max_lines - 1)
	{
		if (!cub_items(map[y], *cb_st))
			return (ft_putstr_fd("|| INVALID ITEM ON MAP ! |", 2), 0);
		y++;
	}
	if (max_lines > 1 && !closed_wall(map[max_lines - 1]))
		return (0);
	if (!one_player_on_map(map))
		return (0);
	(*cb_st)->map_h = max_lines;
	(*cb_st)->map = dup_map(map);
	get_player_pos(cb_st);
	return (1);
}

char	**dup_map(char **map)
{
	char	**dup_map;
	int		i;

	if (!map || !map)
		return (NULL);
	i = 0;
	dup_map = malloc(sizeof(char *) * (td_len(map) + 1));
	while (i < td_len(map))
	{
		dup_map[i] = ft_strdup(map[i]);
		i++;
	}
	dup_map[i] = NULL;
	return (dup_map);
}

int	cub_items(char *line, t_cub *cb_st)
{
	int		i;
	char	*map_line;

	i = 0;
	map_line = ft_strtrim(line, " ");
	if (!map_line || 
		(map_line[0] && map_line[0] != '1' && map_line[ft_strlen(map_line)] != '1'))
			return (printf("map must be surrended by wals"), 0);
	while (map_line[i])
	{
		if (map_line[i] && map_line[i + 1] && map_line[i] == ' ' && map_line[i + 1] != '1')
			return (printf("invalid map \n"), 0);
		else if (map_line[i] != 'N' &&  map_line[i] != 'S' &&  map_line[i] != 'W'
			&&  map_line[i] != 'E' && map_line[i] != '0' && map_line[i] !=  '1' && map_line[i] != ' ')
			return (0);
		i++;
	}
	if (!cb_st->map_w)
		cb_st->map_w = i;
	return (1);
}
