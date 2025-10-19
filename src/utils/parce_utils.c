/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:58:14 by alel-you          #+#    #+#             */
/*   Updated: 2025/10/19 21:48:35 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub.h"

t_cred_list	*grap_credantials(int fd)
{
	t_cred_list	*list;
	char		*line;
	char		*content;
	int			f;

	f = 0;
	content = NULL;
	line = get_next_line(fd);
	list = malloc(sizeof(t_cred_list));
	if (!list || !line)
		return (NULL);
	list = NULL;
	while (line)
	{
		if (!f && !strcmp(line, "\n"))
		{
			printf("%s\n", line);
			line = get_next_line(fd);
			continue ;
		}
		if (!is_map_line(line))
			content = ft_strtrim(line, " ");
		else if (!content)
			return (NULL);
		if (!is_map_line(line))
		{
			if (!add_content(&list, content))
				return (NULL);
		}
		else
		{
			f = 1;
			if (!add_content(&list, line))
				return (NULL);
		}
		line = get_next_line(fd);
	}
	return (list);
}

void	print_list(t_cred_list *list)
{
	t_cred_list *tmp = list;
	while (tmp)
	{
		printf("%s", tmp->content);
		tmp = tmp->next;
	}
}

int extract_credantials(t_cub **cb_st, int fd)
{
	t_cred_list	*list;

	list = grap_credantials(fd);
	if (!list)
		return (0);
	if (!missing_or_dup(list) || !check_content_order(list))
		return (0);
	else if (!asign_texters(list, cb_st))
		return (0);
	else if (!asign_colors(list, cb_st))
		return (0);
	else if (!get_map(list, cb_st))
		return (0);
	return (1);
}

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

int	parse_arguments(t_cub **cb_st, char **av)
{
	int fd;

	if (!valid_map_arg(av[1]))
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror(""), 0);
	(*cb_st)->map = NULL;
	(*cb_st)->map_h = 0;
	(*cb_st)->map_w = 0;
	(*cb_st)->no_texture = NULL;
	(*cb_st)->so_texture = NULL;
	(*cb_st)->we_texture = NULL;
	(*cb_st)->ea_texture = NULL;
	if (!extract_credantials(cb_st, fd))
		return (puts("ahhhhhhhhhhhh"), 0);
	return (1);
}