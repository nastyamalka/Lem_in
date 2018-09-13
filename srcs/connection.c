/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 12:05:07 by amalkevy          #+#    #+#             */
/*   Updated: 2018/06/19 12:05:11 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	ft_mal_matr(t_opt *inf)
{
	int		i;
	int		j;

	i = 0;
	inf->matr_smezh = (char**)(malloc(sizeof(char*) * (inf->n_of_rooms + 1)));
	while (i < inf->n_of_rooms)
	{
		j = 0;
		inf->matr_smezh[i] = (char*)(malloc(sizeof(char) *
		(inf->n_of_rooms + 1)));
		while (j < inf->n_of_rooms)
		{
			inf->matr_smezh[i][j] = '0';
			j++;
		}
		inf->matr_smezh[i][j] = '\0';
		i++;
	}
	inf->matr_smezh[i] = NULL;
}

int		ft_is_conection(char *s, t_opt *inf)
{
	char	*def;

	if (s[0] == '#')
		return (2);
	def = ft_strchr(s, '-');
	if (!def)
		return (0);
	if (!inf->matr_smezh)
		ft_mal_matr(inf);
	return (ft_fit(s, def, inf));
}

void	ft_no_end_start(t_opt *inf, char **line, int *r)
{
	if (inf->end == -1)
	{
		(inf->e) ? ft_printf("\e[1;31mNo end!!\e[0m\n") : ft_printf("Error\n");
		if (*line)
			ft_memdel((void**)(line));
		exit(1);
	}
	if (inf->strt == -1)
	{
		(inf->e) ? ft_printf("\e[1;31mNo start!\e[0m\n") : ft_printf("Error\n");
		if (*line)
			ft_memdel((void**)(line));
		exit(1);
	}
	ft_printf("%s\n", *line);
	*r = ft_is_conection(*line, inf);
	if (*line)
		ft_memdel((void**)(line));
	if (*r == 0 && inf->rooms != NULL)
	{
		(inf->e) ? ft_printf(("\e[1;31mSTOP! Incorect connection"
		"\e[0m\n")) : ft_printf("Error\n");
		exit(1);
	}
}

int		ft_check_conect(t_opt *inf, char **line)
{
	int		r;
	int		g;

	ft_no_end_start(inf, line, &r);
	while (r == 1 || r == 2)
	{
		g = get_next_line(inf->fd, line);
		ft_printf("%s\n", *line);
		if (g == -1)
			return (0);
		r = ft_is_conection(*line, inf);
		if (*line)
			ft_memdel((void**)(line));
		if (r == 0 && g > 0)
			break ;
	}
	if (r == 0 && g > 0 && inf->rooms != NULL)
	{
		if (*line)
			ft_memdel((void**)(line));
		(inf->e) ? ft_printf(("\e[1;31mSTOP! Incorect connection\e[0m\n"))
		: ft_printf("Error\n");
		return (0);
	}
	return (1);
}
