/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:11:17 by alel-you          #+#    #+#             */
/*   Updated: 2025/10/17 21:13:01 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub.h"

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
	else if (td_len(f) < 3 || td_len(c) < 3)
		return (printf("Error\nmissing a colors\n"), 0);
		(*cb_st)->floor_color[0] = ft_atoi(f[0]);
		(*cb_st)->floor_color[1] = ft_atoi(f[1]);
		(*cb_st)->floor_color[2] = ft_atoi(f[2]);
		(*cb_st)->ceiling_color[0] = ft_atoi(c[0]);
		(*cb_st)->ceiling_color[1] = ft_atoi(c[1]);
		(*cb_st)->ceiling_color[2] = ft_atoi(c[2]);
	if ((*cb_st)->floor_color[0] > -1 || (*cb_st)->ceiling_color[1] > -1
		|| (*cb_st)->floor_color[1] > -1 || (*cb_st)->ceiling_color[0] > -1
		|| (*cb_st)->floor_color[2] > -1 || (*cb_st)->ceiling_color[2] > -1)
			return (0);
	return (1);
}
