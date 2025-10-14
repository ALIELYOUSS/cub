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

void    print_td(char **str, int len)
{
	int i = 0;
	while (str && str[i] && i < len)
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
		content = ft_strtrim(line, " ");
		if (!content)
			return (free_list(list), NULL);
		if (!add_content(&list, content))
			return (free_list(list), NULL);
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
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != '\n')
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
	if (!cub)
		exit(EXIT_FAILURE);
	(*cub)->no_texture = get_wanted_line(list, "NO");
	(*cub)->so_texture = get_wanted_line(list, "SO");
	(*cub)->we_texture = get_wanted_line(list, "WE");
	(*cub)->ea_texture = get_wanted_line(list, "EA");
	if (!(*cub)->no_texture || !(*cub)->so_texture 
		|| !(*cub)->ea_texture || !(*cub)->we_texture)
		return (0);
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
	if (!tmp || tmp1)
		return (0);
	f = ft_split(tmp1 + 1, ',');
	c = ft_split(tmp + 1, ',');
	if (!f || !c || !f[0] || !f[1]
			|| !f[2] || !c[0] || !c[1] || !c[2])
		return (ft_putstr_fd("collor must be 255,255,255\n", 2), 0);
	while (f && c && f[i] && c[i])
	{
		if (!str_is_digit(f[i]) || !str_is_digit(c[i]))
			return (ft_putstr_fd("collors must be digit\n", 2), 0);
		i++;
	}
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