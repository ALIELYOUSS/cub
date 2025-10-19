/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:19:55 by alel-you          #+#    #+#             */
/*   Updated: 2025/10/19 20:32:15 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub.h"

int td_len(char **td)
{
	int i = 0;
	while (td && td[i])
		i++;
	return (i);
}

char	*equal_rows(char *line_map, int len)
{
	char	*dup;
	int		i;
	int		x;

	x = 0;
	i = 0;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (i < len && line_map[i])
	{
		if (line_map[i] != '\n' && line_map[i] != ' ')
		{
			dup[x++] = line_map[i++];
			continue ;
		}
		else if (line_map[i] == ' ')
		{
			dup[x++] = '.';
			i++;
			continue ;
		}
		i++;	
	}
	while (x < len - 1)
		dup[x++] = '.';
	dup[len - 1] = '\n';
	dup[len + 1] = '\0';
	return (dup);
}

char	**dup_map(char **map, t_cred_list *list)
{
	char	**dup_map;
	int		i;
	int		largest_row;

	if (!map || !list)
		return (NULL);
	i = 0;
	largest_row = get_largest_row(list);
	dup_map = malloc(sizeof(char *) * (td_len(map) + 1));
	if (!dup_map)
		return (0);
	while (i < td_len(map))
	{
		dup_map[i] = equal_rows(map[i], largest_row);
		i++;
	}
	dup_map[i] = NULL;
	return (dup_map);
}

int	valid_map_line(char *line)
{
	int	i;	

	i = 0;
	if (!line)
		return (0);
	if (line[0] && line[0] != '1')
		return (printf("Error\nmap must be close by walls\n"), 0);
	while (line[i])
	{
		if ((line[i + 1] && line[i] == '0' && line[i  + 1] == ' '))
			return (printf("Error\nMap persed '-'\n"), 0);
		else if (line[i  + 1] && line[i] == ' ' && line[i + 1] != ' ' 
			&& line[i + 1] != '1')
			return (printf("Error\nMap persed '-'\n"), 0);
		else if (!line[i + 1] && line[i] == '\n' && line[i - 1] != '1')
			return (printf("Error\nmap is not closed by walls\n"), 0);
		i++;
	}
	return (1);
}

int	closed_map(char **map)
{
	char	*line;
	int		y;
	int		line_len;

	y = 1;
	line_len = 0;
	if (!is_wall(map[0]))
		return (printf("Error\nfirst map_line isn't closed '-'\n"), 0);
	while (map[y]  && y < td_len(map) - 1)
	{
		line = ft_strtrim(map[y], " ");
		if (!line)
			return (0);
		else if (!valid_map_line(line))
			return (0);
		y++;
	}
	if (!is_wall(map[td_len(map) - 1]))
		return (printf("Error\nlast map line isn't closed '-'\n"), 0);
	return (1);
}

int	cub_items(char *line, t_cub *cb_st)
{
	int		i;
	char	*map_line;
	char	sp_or;

	sp_or = 0;
	i = 0;
	map_line = ft_strtrim(line, " ");
	while (map_line && map_line[i])
	{
		sp_or = map_line[i];
		if (sp_or == 'S' || sp_or == 'N' || sp_or == 'W' || sp_or == 'E')
			cb_st->plyer_pos.spg_or = sp_or;
		if (map_line[i] != 'N' &&  map_line[i] != 'S' &&  map_line[i] != 'W' && map_line[i] != '\n'
			&&  map_line[i] != 'E' && map_line[i] != '0' && map_line[i] !=  '1' && map_line[i] != ' ')
			return (printf("Error\nmap contains none cub items\n"), 0);
		i++;
	}
	if (!map_line)
		return (printf("Error\n"), 0);
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
