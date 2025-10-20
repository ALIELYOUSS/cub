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

// int check_map_closed(char **map, int rows, int cols)
// {
//     int y;
//     int x;

//     y = 0;
//     while (map && map[y])
//     {
//         x = 0;
//         while (map[y][x])
//         {
//             if (map[y][x] == '0' || is_player(map[y][x]))
//             {
//                 if (y == 0 || x == 0 || y == rows - 1 || x == cols - 1)
//                     return (0);
//                 if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' ||
//                     map[y][x - 1] == ' ' || map[y][x + 1] == ' ' ||
//                     map[y - 1][x] == '\0' || map[y + 1][x] == '\0' ||
//                     map[y][x - 1] == '\0' || map[y][x + 1] == '\0')
//                     return (0);
//             }
//             x++;
//         }
//         y++;
//     }
//     return (1);
// }

int	parse_map(char **map, t_cub **cb_st, t_cred_list *list)
{
	int		y;
	char	**p_map;

	y = 1;
	if (!map)
		return (0);
	player_position(map, cb_st);
	p_map = dup_map(map, list);
	if (!closed_map(p_map))
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
		return (puts("ckajdsb"), 1);
	return (0);
}