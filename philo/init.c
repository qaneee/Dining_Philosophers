/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:52:07 by arvardan          #+#    #+#             */
/*   Updated: 2025/11/01 12:29:49 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_num;

	philo_num = philo->table->philo_count;
	philo->first_fork = &forks[(philo_pos + 1) % philo_num];
	philo->second_fork = &forks[philo_pos];
	if (philo->philo_id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_num];
	}
}

static void	init_philo(t_table *t)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < t->philo_count)
	{
		philo = t->philos + i;
		philo->philo_id = i + 1;
		philo->is_full = false;
		philo->meals_eaten = 0;
		philo->table = t;
		pthread_mutex_init(&philo->philo_mutex, NULL);
		set_forks(philo, t->forks, i);
		philo->last_meal_time = 0;
		i++;
	}
}

void	init_all(t_table *t)
{
	int	i;

	i = 0;
	t->end_sim = false;
	t->are_threads_created = false;
	t->running_thread_count = 0;
	pthread_mutex_init(&t->table_mutex, NULL);
	pthread_mutex_init(&t->write_mutex, NULL);
	t->philos = malloc(sizeof(t_philo) * t->philo_count);
	if (!t->philos)
		return ;
	t->forks = malloc(sizeof(t_fork) * t->philo_count);
	if (!t->forks)
	{
		free(t->philos);
		return ;
	}
	while (i < t->philo_count)
	{
		t->forks[i].fork_id = i;
		pthread_mutex_init(&t->forks[i].fork, NULL);
		i++;
	}
	init_philo(t);
}
