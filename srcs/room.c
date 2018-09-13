/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 12:11:46 by amalkevy          #+#    #+#             */
/*   Updated: 2018/06/19 12:11:51 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	ft_room(char **s, t_opt *inf)
{
	t_room	*new_room;
	t_room	*p;

	p = inf->rooms;
	new_room = (t_room*)malloc(sizeof(t_room));
	while (p && p->next != NULL)
		p = p->next;
	if (p != NULL && !(inf->s != 0 && inf->strt == -1) && !(inf->en != 0
	&& inf->end == -1))
		p->next = new_room;
	else if (!(inf->s != 0 && inf->strt == -1) && !(inf->en != 0 &&
	inf->end == -1))
		inf->rooms = new_room;
	new_room->next = NULL;
	new_room->name = ft_strdup(*s);
	new_room->index = (inf->rooms && inf->rooms->s_or_e == 's')
	? inf->n_of_rooms : inf->n_of_rooms + 1;
	new_room->ant = NULL;
	new_room->x = ft_atoi(*(s + 1));
	new_room->y = ft_atoi(*(s + 2));
	ft_st_or_end(inf, new_room);
}

int		ft_add_end2(t_opt *inf, t_room *r_p)
{
	if (inf->room_end)
	{
		r_p->next = inf->room_end;
		r_p->next->index = inf->n_of_rooms++;
	}
	return (1);
}

int		ft_add_end(t_opt *inf)
{
	t_room	*r_p;
	t_room	*p;

	r_p = inf->rooms;
	while (r_p && r_p->next)
	{
		if (ft_strcmp(r_p->next->name, inf->room_end->name) == 0)
		{
			if (r_p->next->x == inf->room_end->x && r_p->next->y
			== inf->room_end->y)
			{
				p = r_p->next;
				r_p->next = r_p->next->next;
				free_room(p);
				if (p)
					ft_memdel((void**)(&p));
				if (r_p->next == NULL)
					break ;
			}
			else
				return (0);
		}
		r_p = r_p->next;
	}
	return (ft_add_end2(inf, r_p));
}

int		ft_last_room(int r, int g, t_opt *inf, char *line)
{
	if (r == 0 && g > 0)
	{
		if (inf->room_end)
			if (ft_add_end(inf) == 0)
			{
				(inf->e) ? ft_printf("\e[1;31mSTOP! Incorect room\e[0m\n")
				: ft_printf("Error\n");
				exit(1);
			}
		return (ft_check_conect(inf, &line));
	}
	if (inf->e && (r == -1 || r == -2))
		(r == -2) ? ft_printf("\e[1;31mSTOP!\nError with start\e[0m\n")
		: ft_printf("\e[1;31mSTOP!\nError with end\n\e[0m");
	else if (r != -3)
		ft_printf("Error\n");
	exit(1);
}

int		ft_check_room(t_opt *inf)
{
	char	*line;
	int		r;
	int		g;

	line = NULL;
	g = get_next_line(inf->fd, &line);
	ft_printf("%s\n", line);
	r = ft_is_room(line, inf);
	while (r == 1 || r == 2 || r == 3)
	{
		if (line)
			ft_memdel((void**)(&line));
		g = get_next_line(inf->fd, &line);
		ft_printf("%s\n", line);
		if (g == -1)
			return (0);
		r = ft_is_room(line, inf);
		if (r == 0 && g > 0)
			break ;
	}
	return (ft_last_room(r, g, inf, line));
}
