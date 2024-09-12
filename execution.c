/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdijkman <jdijkman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/19 13:36:02 by jdijkman      #+#    #+#                 */
/*   Updated: 2024/08/26 18:33:07 by jdijkman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(char **argv, t_data *data)
{
	if (pthread_mutex_init(&data->lock, NULL))
		return (printf("ERROR IN MUTEX INIT\n"), 1);
	data->philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->sim_start = 0;
	data->finished_count = 0;
	data->stop = false;
	data->start = false;
	data->ready = 0;
	if (argv[5])
		data->meals_to_finish = ft_atoi(argv[5]);
	else
		data->meals_to_finish = -1;
	return (0);
}

void	*philosophize(void *arg)
{
	t_phil	*phil;
	int		id;

	phil = (t_phil *)arg;
	id = phil->id;
	while (read_bool(&phil->data->lock, &phil->data->start) == false)
		;
	ft_think(get_time() - phil->data->sim_start, phil);
	if (id % 2 == 1)
		me_sleep(40);
	while (read_bool(&phil->data->lock, &phil->data->stop) == false)
	{
		ft_eat(id, phil);
		inc_int(&phil->data->lock, &phil->finished_meals);
		if (read_bool(&phil->data->lock, &phil->data->stop))
			break ;
		ft_sleep(get_time() - phil->data->sim_start, phil);
		ft_think(get_time() - phil->data->sim_start, phil);
		if (read_bool(&phil->data->lock, &phil->data->stop))
			break ;
	}
	return (NULL);
}

t_phil	*fill_struct(t_data *data, t_phil *phil, int i, pthread_mutex_t *forks)
{
	phil->id = i;
	phil->forks = forks;
	phil->time_to_die = data->time_to_die;
	phil->last_meal_time = -1;
	phil->philosophers = data->philosophers;
	phil->time_to_eat = data->time_to_eat;
	phil->time_to_sleep = data->time_to_sleep;
	phil->finished_meals = 0;
	phil->done = false;
	phil->data = data;
	return (phil);
}

void	init_obsv(t_data *data, t_phil **phil)
{
	int	i;

	i = -1;
	while (read_int(&data->lock, &data->ready) < data->philosophers)
		;
	write_uint64(&data->lock, &data->sim_start, get_time());
	while (++i < data->philosophers)
		write_uint64(&data->lock, &phil[i]->last_meal_time, data->sim_start);
	write_bool(&data->lock, &data->start, true);
}

int	status_phil(t_data *data, t_phil **phil)
{
	int	i;

	i = 0;
	init_obsv(data, phil);
	while (i < data->philosophers)
	{
		if (get_time() - read_uint64(&data->lock, &phil[i]->last_meal_time) > \
			data->time_to_die)
			return (stop_phils(data), ft_die(get_time() - \
					data->sim_start, phil[i]), 0);
		if (data->meals_to_finish != -1 && read_int(&data->lock, \
			&phil[i]->finished_meals) >= data->meals_to_finish && \
			phil[i]->done == false)
		{
			data->finished_count ++;
			write_bool(&data->lock, &phil[i]->done, true);
			if (data->finished_count >= data->philosophers)
				return (stop_phils(data));
		}
		i ++;
		if (i >= data->philosophers)
			i = 0;
		usleep(50);
	}
	return (1);
}
