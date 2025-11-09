/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:52:47 by arvardan          #+#    #+#             */
/*   Updated: 2025/09/29 19:32:39 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *p)
{
	unsigned long long	time_passed;
	long				time_to_die;
	long				last_meal;
	unsigned long long	current_time;

	if (get_bool(&p->philo_mutex, &p->is_full))
		return (false);
	last_meal = get_long(&p->philo_mutex, &p->last_meal_time);
	current_time = real_time();
	time_passed = current_time - last_meal;
	time_to_die = p->table->time_to_die;
	if (time_passed > (unsigned long long)time_to_die)
	{
		return (true);
	}
	return (false);
}

static bool	all_ate_enough(t_table *table)
{
	int	i;
	int	count;

	count = 0;
	if (table->must_eat <= 0)
		return (false);
	i = 0;
	while (i < table->philo_count)
	{
		if (get_bool(&table->philos[i].philo_mutex, &table->philos[i].is_full))
			count++;
		i++;
	}
	if (count == table->philo_count)
	{
		return (true);
	}
	return (false);
}

static bool	monitoring_helper(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count && !sim_finished(table))
	{
		if (philo_died(table->philos + i))
		{
			set_bool(&table->table_mutex, &table->end_sim, true);
			write_state(DIED, table->philos + i);
			return (true);
		}
		i++;
	}
	if (all_ate_enough(table))
	{
		set_bool(&table->table_mutex, &table->end_sim, true);
		return (true);
	}
	return (false);
}

void	*monitoring(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	while (!all_running(&table->table_mutex,
			&table->running_thread_count, table->philo_count))
	{
		usleep(1000);
	}
	while (!sim_finished(table))
	{
		if (monitoring_helper(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}
