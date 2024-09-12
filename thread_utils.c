/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdijkman <jdijkman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 14:36:29 by jdijkman      #+#    #+#                 */
/*   Updated: 2024/08/23 16:59:00 by jdijkman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*init_mutex_locks(t_data *data, pthread_mutex_t *locks)
{
	int	i;

	i = 0;
	locks = malloc (sizeof(pthread_mutex_t) * data->philosophers);
	if (!locks)
		ft_exit("ERROR in malloc", 1);
	while (i < data->philosophers)
	{
		if (pthread_mutex_init(&locks[i], NULL) != 0)
		{
			while (-- i > -1)
				pthread_mutex_destroy(&locks[i]);
			return (printf("ERROR in mutex init\n"), free(locks), NULL);
		}
		i ++;
	}
	return (locks);
}

int	stop_phils(t_data *data)
{
	write_bool(&data->lock, &data->stop, true);
	return (0);
}

int	create_threads(t_data *data, pthread_t *t, t_phil **phil)
{
	int	i;

	i = 0;
	while (i < data->philosophers)
	{
		if (pthread_create(&t[i], NULL, *philosophize, phil[i]))
		{
			join_threads(t, i - 1);
			free(t);
			return (printf("ERROR in pthread_create function\n"), 1);
		}
		inc_int(&data->lock, &data->ready);
		i ++;
	}
	return (0);
}

t_phil	**init_p(t_data *data, pthread_mutex_t *f, t_phil **phil)
{
	int	i;

	i = 0;
	phil = malloc (sizeof(t_phil) * data->philosophers);
	if (phil == NULL)
		ft_exit("ERROR in malloc", -1);
	while (i < data->philosophers)
	{
		phil[i] = malloc (sizeof(t_phil));
		if (phil[i] == NULL)
		{
			ft_free_struct(phil);
			ft_exit("ERROR in malloc", -1);
		}
		phil[i] = fill_struct(data, phil[i], i, f);
		i ++;
	}
	phil[i] = NULL;
	return (phil);
}
