/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collecter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:07:25 by alel-you          #+#    #+#             */
/*   Updated: 2025/10/16 16:50:05 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub.h"

void	*malloc(size_t size)
{
	static t_garbage_node	*gb_list;
	t_garbage_node			*new_node;
	void					*ptr;

	if (!gb_list)
		gb_list = malloc(sizeof(t_garbage_node));
	ptr = malloc(size);
	if (!ptr)
		exit(EXIT_FAILURE);
	new_node = malloc(sizeof(t_garbage_node));
	if (!new_node)
	{
		free(ptr);
		exit(EXIT_FAILURE);
	}
	new_node->ptr = ptr;
	new_node->next = NULL;
	garbage_add(&gb_list, new_node);
	return (ptr);
}

void	garbage_add(t_garbage_node **gb_list, t_garbage_node *new)
{
	t_garbage_node	*tmp;

	tmp = NULL;
	if (!new)
		return ;
	if (!*gb_list)
	{
		*gb_list = new;
		return ;
	}
	tmp = *gb_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;	
}
