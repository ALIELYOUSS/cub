/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:58:22 by alel-you          #+#    #+#             */
/*   Updated: 2025/10/20 04:11:31 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub.h"

void    print_td(char **str)
{
	int i = 0;
	while (str && str[i])
	{
		printf("%s", str[i]);
		i++;
	}
}

int is_player(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	parse_map(char **map, t_cub **cb_st, t_cred_list *list)
{
	int		y;
	char	**p_map;

	y = 1;
	if (!map)
		return (0);
	player_position(map, cb_st);
	if (!closed_map(map))
		return (printf("Error\nmap isn't close\n"), 0);
	while (map[y] != NULL)
	{
		if (!cub_items(map[y], *cb_st))
			return (printf("map has unknow item\n"), 0);
		y++;
	}
	if (!one_player_on_map(map))
		return (printf("Error\n"), 0);
	return (1);
}

void	print_cred(t_cub *cb)
{
	printf("%s\n %s\n %s\n %s\n", cb->no_texture, cb->we_texture,cb->so_texture, cb->ea_texture);
	printf("%d, %d, %d\n", cb->floor_color[0], cb->floor_color[1], cb->floor_color[2]);
	printf("%d, %d, %d\n", cb->ceiling_color[0], cb->ceiling_color[1], cb->ceiling_color[2]);
	print_td(cb->map);
}

int main(int ac, char **av)
{
	t_cub   *cub_st;

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