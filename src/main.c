/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:58:22 by alel-you          #+#    #+#             */
/*   Updated: 2025/10/17 18:21:45 by alel-you         ###   ########.fr       */
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

int	parse_map(char **map, t_cub **cb_st)
{
	int	y;

	y = 1;
	if (!map)
		return (0);
	else if (!closed_map(map))
		return (0);
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