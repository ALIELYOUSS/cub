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
	t_garbage_node	*garbage_head;
}   t_cub;
int	one_player_on_map(char **map);
char	**dup_map(char **map);
void	get_player_pos(t_cub **cb);
int	cub_items(char *map_line, t_cub *cb_st);
int	parse_map(char **map, t_cub **cb_st);
int	check_wall(char *map_line);
int	asign_map(t_cred_list *list, t_cub **cub);
int	asign_colors(t_cred_list *list, t_cub **cb_st);
int	asign_texters(t_cred_list *list, t_cub **cub);
int	missing_or_dup(t_cred_list *list);
int	check_order(char **td);
void	print_error(char *message);
char	**dir_texters_path(int fd);
int	valid_map_arg(char *arg);
char	**get_argb_colors(int fd);
int	add_content(t_cred_list **map_list, char *content);
int	get_list_size(t_cred_list *map_list);
char	**get_map(t_cred_list *list);
char	**convert_to_td(t_cred_list *map_list);
int	td_len(char **td);
void	print_td(char **str);
t_cred_list	*grap_credantials(int fd);
int	check_content_order(t_cred_list *list);
int	is_map_line(char *line);
void	free_list(t_cred_list *list);

#endif
