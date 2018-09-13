/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 12:24:52 by amalkevy          #+#    #+#             */
/*   Updated: 2018/06/19 12:33:08 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include <locale.h>
# include <stdarg.h>
# include <wchar.h>
# include <limits.h>
# include <fcntl.h>
# define N  "\x1B[0m"
# define R  "\x1B[31m"
# define G  "\x1B[32m"
# define U  "\x1B[33m"
# define M  "\x1B[35m"
# define Y "\x1B[36m"

typedef struct		s_ants
{
	int				data;
	struct s_ants	*next;
}					t_ants;

typedef struct		s_room
{
	char			s_or_e;
	t_ants			*ant;
	int				index;
	char			*name;
	struct s_room	*next;
	int				status;
	int				value;
	int				index_from_where;
	struct s_room	*prev;
	int				x;
	int				y;
}					t_room;

typedef struct		s_way
{
	t_room			*head;
	int				index;
	struct s_way	*next;
	int				num_of_room;
}					t_way;

typedef struct		s_opt
{
	int				n_of_ant;
	t_room			*rooms;
	t_way			*way;
	int				*quee;
	char			s;
	char			en;
	char			**matr_smezh;
	int				n_of_rooms;
	int				strt;
	int				end;
	int				fd;
	int				r1;
	int				r2;
	char			e;
	char			color;
	char			how_to_go;
	char			show;
	int				num_of_ways;
	char			*new_line;
	t_room			*room_end;
}					t_opt;

int					ft_is_str_num(char *s);
int					ft_check_room(t_opt *inf);
int					ft_check_conect(t_opt *inf, char **line);
int					ft_check_ant(t_opt *inf);
void				free_room(t_room *r);
int					ft_find_place(t_opt *inf, int i);
void				ft_made_quee(t_opt *inf);
void				ft_push_in_quee(t_opt *inf, int index);
t_room				*ft_take_from_quee(t_opt *inf);
void				ft_push_back(t_way **way, t_way *new_way);
int					ft_do(t_opt *inf);
void				ft_go(t_opt *inf);
t_room				*ft_find_room(t_room *rooms, int index);
t_room				*ft_help_norma(t_room *rooms);
void				ft_printf_ants(t_opt *inf, t_room *r_p, int *m);
void				ft_add_ant_to_end(t_room *r_p, int i);
void				ft_go_to_end(t_opt *inf);
int					ft_print_way(t_opt *inf);
t_room				*ft_check_for_pr(t_way *way);
void				ft_move(t_opt *inf);
int					ft_check_next(t_way *way);
int					ft_fit(char *s, char *def, t_opt *inf);
void				ft_room(char **s, t_opt *inf);
int					ft_is_room(char *s, t_opt *inf);
void				ft_st_or_end(t_opt *inf, t_room *new_room);

#endif
