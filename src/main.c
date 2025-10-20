/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:58:22 by alel-you          #+#    #+#             */
/*   Updated: 2025/10/20 23:15:27 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	empty_line(char *line)
{
	int	i;
	
	i = 0;
	while (line && line[i] && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
		return (1);
	return (0);
}

int	parse_map(char **map, t_cub **cb_st, t_cred_list *list)
{
	int		y;
	char	**p_map;

	y = 0;
	if (!map || !map[0])
		return (printf("Error\n missing map\n"), 0);
	if (!closed_map(map))
		return (0);
	while (map[y] != NULL)
	{
		if (empty_line(map[y]))
			return (printf("remove emty lines from map\n"), 0);
		if (!cub_items(map[y]))
			return (printf("map has unknow item\n"), 0);
		y++;
	}
	if (!one_player_on_map(map))
		return (printf("Error\n"), 0);
	player_position(map, cb_st);
	return (1);
}

int	main(int ac, char **av)
{
	t_cub	*cub_st;

	cub_st = NULL;
	if (ac <= 1)
		return (printf("invalid arguments !!!\n"), 1);
	cub_st = malloc(sizeof(t_cub));
	if (!cub_st)
		return (perror(""), 1);
	if (!parse_arguments(&cub_st, av))
		return (1);
	print_cred(cub_st);
	return (0);
}
