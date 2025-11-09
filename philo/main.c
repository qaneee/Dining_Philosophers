/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:52:15 by arvardan          #+#    #+#             */
/*   Updated: 2025/11/01 12:30:28 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	parse_input(t_table *t, char **argv, int argc)
{
	t->philo_count = ft_atol(argv[1]);
	t->time_to_die = ft_atol(argv[2]);
	t->time_to_eat = ft_atol(argv[3]);
	t->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		t->must_eat = ft_atol(argv[5]);
	else
		t->must_eat = -1;
}

static void	validate_input(int argc, char **arr)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_atol(arr[i]) || ft_atol(arr[i]) <= 0)
		{
			printf("Invalid input!\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid argument count!\n");
		exit(EXIT_FAILURE);
	}
	validate_input(argc, argv);
	parse_input(&table, argv, argc);
	init_all(&table);
	start_dinner(&table);
	free_all(&table);
	return (0);
}
