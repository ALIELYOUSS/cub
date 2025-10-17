/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 22:53:56 by alel-you          #+#    #+#             */
/*   Updated: 2025/10/17 20:35:02 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char const *str)
{
	int		i;
	int		sign;
	long	tmp;

	i = 0;
	sign = 1;
	tmp = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (str[i] == '-')
			return (printf("Error\nonly feeds on positive numbers\n"), -1);
		tmp = (tmp * 10) + (str[i] - '0');
		i++;
	}
	while (str && str[i])
	{
		if (str[i] == ' ')
			return (printf("Error\nremove the white spaces in the argb\n"), -1);
		i++;
	}
	if (tmp > 255)
		return (ft_putstr_fd ("Error\nvalue must be between 0 && 255\n", 2), -1);
	return (tmp);
}
