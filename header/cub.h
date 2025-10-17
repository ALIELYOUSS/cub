/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:58:35 by alel-you          #+#    #+#             */
/*   Updated: 2025/10/17 18:13:45 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CUB3D_H
#define	CUB3D_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include   "fcntl.h"
# include   "string.h"
# include   "stdio.h"
# include   "stdlib.h"

typedef struct s_cred_list
{
	char						*content;
	struct s_cred_list	*next;
}	t_cred_list;

typedef enum s_spawning_or
{
	N,
	E,
	W,
	S,
}   t_spawning_or;

typedef struct s_player_pos
{
	int				x;
	int				y;
	t_spawning_or	spg_or; 
}	t_player_pos;

typedef struct	s_garbage_node
{
	void					*ptr;
	struct s_garbage_node	*next;
}	t_garbage_node;

typedef struct	s_cub
{
	char				**map;
	int				map_h;
	int				map_w;
	char				*no_texture;
	char				*so_texture;
	char				*we_texture;
	char				*ea_texture;
	int				floor_color[3];
	int				ceiling_color[3];
	t_player_pos		plyer_pos;
}   t_cub;


t_cred_list	*grap_credantials(int fd);
char		*get_wanted_line(t_cred_list *list, char *wanted);
void 	  	print_td(char **str);
int			a_valid_argb(char *str);
int			check_content_order(t_cred_list *list);
int			asign_colors(t_cred_list *list, t_cub **cb_st);
int 		extract_credantials(t_cub **cb_st, int fd);
int			asign_texters(t_cred_list *list, t_cub **cub);
int			check_dup(t_cred_list *list, char *to_check, int len);
int			missing_or_dup(t_cred_list *list);
int 		td_len(char **td);
int			parse_arguments(t_cub **cb_st, char **av);
int			is_wall(char *wall);
int			add_content(t_cred_list **list, char *content);

int			parse_map(char **map, t_cub **cb_st);
int			get_largest_row(t_cred_list *list);
char		*equal_rows(char *line_map, int len);
char		**dup_map(char **map, t_cred_list *list);
int			get_map(t_cred_list *list, t_cub **cub);
int 		valid_map_arg(char *arg);
int			one_player_on_map(char **map);
int			cub_items(char *line, t_cub *cb_st);
int			closed_map(char **map);
int			is_map_line(char *line);
int 		valid_map_arg(char *arg);
int			map_size(t_cred_list *list);
int			asign_map(t_cred_list *list, t_cub **cub);

void		*malloc(size_t size);
void		garbage_add(t_garbage_node **gb_list, t_garbage_node *new);

#endif
