/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 18:32:28 by amalkevy          #+#    #+#             */
/*   Updated: 2018/06/18 18:32:31 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	ft_go_to_end(t_opt *inf)
{
	t_room	*p;
	t_way	*w_p;

	while (ft_check_next(inf->way))
	{
		if (inf->way->head)
			while (!inf->way->head->next)
				inf->way = inf->way->next;
		w_p = inf->way;
		while (w_p && w_p->head->next)
		{
			p = w_p->head;
			free_room(w_p->head);
			w_p->head = w_p->head->next;
			if (p)
				ft_memdel((void**)(&p));
			w_p = w_p->next;
		}
		ft_print_way(inf);
		ft_move(inf);
	}
}

int		ft_is_str_num(char *s)
{
	int		i;

	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (i != 0 && s[i] == '\0')
		return (1);
	return (0);
}

int		ft_is_num_of_ant(char *s)
{
	if (!s)
		return (0);
	if (s[0] == '#' && ft_strcmp("##start", s) && ft_strcmp("##end", s))
		return (2);
	return (ft_is_str_num(s));
}

void	ft_ant(char *line, t_opt *inf, int r)
{
	if (r == 1)
	{
		ft_printf("%s\n", line);
		inf->n_of_ant = ft_atoi(line);
		if (inf->n_of_ant <= 0)
			r = 0;
	}
	if (line)
		ft_memdel((void **)(&line));
	if (r == 0 || inf->n_of_ant > 214748364)
	{
		(inf->e) ? ft_printf("\e[1;31mIncorect number of ants\e[0m\n")
		: ft_printf("Error\n");
		exit(1);
	}
}

int		ft_check_ant(t_opt *inf)
{
	char	*line;
	int		r;
	int		g;

	line = NULL;
	if (get_next_line(inf->fd, &line) == -1)
	{
		(inf->e) ? ft_printf("\e[1;31mCould not read file\e[0m\n") : 0;
		return (0);
	}
	r = ft_is_num_of_ant(line);
	while (r == 2)
	{
		ft_printf("%s\n", line);
		if (line)
			ft_memdel((void **)(&line));
		g = get_next_line(inf->fd, &line);
		if (g == -1)
			return (0);
		r = ft_is_num_of_ant(line);
	}
	ft_ant(line, inf, r);
	return (1);
}
