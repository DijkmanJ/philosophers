/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdijkman <jdijkman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/23 14:15:33 by jdijkman      #+#    #+#                 */
/*   Updated: 2024/08/23 14:28:26 by jdijkman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	join_threads(pthread_t	*threads, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(threads[i], NULL);
		i ++;
	}
}

void	destroy_forks(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i ++;
	}
}

int	ft_cleanup(t_data *data, t_phil **phil, pthread_mutex_t *forks, int err)
{
	if (err > 0)
		pthread_mutex_destroy(&data->lock);
	if (err > 1)
		destroy_forks(data, forks);
	if (err > 2)
		ft_free_struct(phil);
	if (err == 4)
		return (0);
	return (1);
}
