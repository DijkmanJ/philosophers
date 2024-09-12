/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state_change.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdijkman <jdijkman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 14:24:05 by jdijkman      #+#    #+#                 */
/*   Updated: 2024/08/27 12:09:30 by jdijkman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_take_fork(int time, t_phil *phil)
{
	if (read_bool(&phil->data->lock, &phil->data->stop) == false)
		ft_print(&phil->data->lock, time, phil, "has taken a fork");
	return ;
}

int	ft_eat(int id, t_phil *phil)
{
	int	first;
	int	second;

	first = id;
	second = (id + 1) % phil->philosophers;
	if (id % 2 == 0)
	{
		first = (id + 1) % phil->philosophers;
		second = id;
	}
	pthread_mutex_lock(&phil->forks[first]);
	ft_take_fork(get_time() - phil->data->sim_start, phil);
	if (read_bool(&phil->data->lock, &phil->data->stop) == true)
		return (pthread_mutex_unlock(&phil->forks[first]), 0);
	pthread_mutex_lock(&phil->forks[second]);
	ft_take_fork(get_time() - phil->data->sim_start, phil);
	write_uint64(&phil->data->lock, &phil->last_meal_time, get_time());
	if (phil->data->time_to_eat >= phil->data->time_to_die)
		me_sleep(phil->time_to_die);
	if (read_bool(&phil->data->lock, &phil->data->stop) == false)
		ft_print(&phil->data->lock, get_time() - phil->data->sim_start, \
				phil, "is eating");
	me_sleep(phil->time_to_eat);
	pthread_mutex_unlock(&phil->forks[second]);
	return (pthread_mutex_unlock(&phil->forks[first]), 0);
}

void	ft_sleep(int time, t_phil *phil)
{
	if (read_bool(&phil->data->lock, &phil->data->stop) == false)
		ft_print(&phil->data->lock, time, phil, "is sleeping");
	if (phil->data->time_to_sleep >= phil->data->time_to_die)
		me_sleep(phil->time_to_die);
	me_sleep(phil->time_to_sleep);
	return ;
}

void	ft_think(int time, t_phil *phil)
{
	if (read_bool(&phil->data->lock, &phil->data->stop) == false)
		ft_print(&phil->data->lock, time, phil, "is thinking");
	return ;
}

void	ft_die(int time, t_phil *phil)
{
	usleep(1000);
	if (read_bool(&phil->data->lock, &phil->data->stop) == true)
		ft_print(&phil->data->lock, time, phil, "died");
	return ;
}
