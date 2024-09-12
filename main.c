/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdijkman <jdijkman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 14:23:59 by jdijkman      #+#    #+#                 */
/*   Updated: 2024/08/23 16:59:16 by jdijkman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	pthread_mutex_t	*forks;
	t_data			data;
	t_phil			**phil;
	pthread_t		*threads;

	phil = NULL;
	forks = NULL;
	if (parse_input(argc, argv) || init_data(argv, &data))
		return (1);
	threads = malloc (sizeof(pthread_t) * data.philosophers);
	if (!threads)
		return (printf("ERROR in malloc\n"), ft_cleanup(&data, phil, forks, 1));
	forks = init_mutex_locks(&data, forks);
	if (forks == NULL)
		return (ft_cleanup(&data, phil, forks, 1));
	phil = init_p(&data, forks, phil);
	if (!phil)
		return (ft_cleanup(&data, phil, forks, 2));
	if (create_threads(&data, threads, phil))
		return (ft_cleanup(&data, phil, forks, 3));
	status_phil(&data, phil);
	join_threads(threads, data.philosophers);
	free(threads);
	return (ft_cleanup(&data, phil, forks, 4), free(forks), 0);
}
