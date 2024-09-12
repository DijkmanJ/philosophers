/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdijkman <jdijkman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 14:24:25 by jdijkman      #+#    #+#                 */
/*   Updated: 2024/08/26 18:38:50 by jdijkman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct s_data
{
	pthread_mutex_t	lock;
	uint64_t		time_to_die;
	uint64_t		time_to_sleep;
	uint64_t		time_to_eat;
	uint64_t		sim_start;
	int				philosophers;
	int				meals_to_finish;
	int				finished_count;
	bool			start;
	int				ready;
	volatile bool	stop;
}	t_data;

typedef struct s_phil
{
	uint64_t		last_meal_time;
	uint64_t		time_to_sleep;
	uint64_t		time_to_eat;
	uint64_t		time_to_die;
	int				id;
	int				philosophers;
	int				finished_meals;
	bool			done;
	pthread_mutex_t	*forks;
	pthread_mutex_t	update_meal;
	t_data			*data;
}	t_phil;

//parsing.c
int				parse_input(int argc, char **argv);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strlen(char *str);
bool			max(char *str);

//execution.c
int				init_data(char **argv, t_data *data);
void			*philosophize(void *arg);
t_phil			*fill_struct(t_data *data, t_phil *phil, int i, \
				pthread_mutex_t *forks);
int				status_phil(t_data *data, t_phil **phil);

//state_change.c
void			ft_take_fork(int time, t_phil *phil);
int				ft_eat(int id, t_phil *phil);
void			ft_sleep(int time, t_phil *phil);
void			ft_think(int time, t_phil *phil);
void			ft_die(int time, t_phil *phil);

//utils.c
int				isnbr(char *str);
int				ft_atoi(const char *nptr);
void			print_struct(t_data *data);
void			ft_exit(char *error_msg, int exit_code);
void			ft_print(pthread_mutex_t *mtx, int time, \
				t_phil *phil, char *msg);

//thread_utils.c
pthread_mutex_t	*init_mutex_locks(t_data *data, pthread_mutex_t *locks);
int				stop_phils(t_data *data);
t_phil			**init_p(t_data *data, pthread_mutex_t *f, t_phil **phil);
int				create_threads(t_data *data, pthread_t *t, t_phil **phil);

//mutex_utils.c
bool			read_bool(pthread_mutex_t *mtx, volatile bool *dest);
uint64_t		read_uint64(pthread_mutex_t *mtx, uint64_t *dest);
int				*inc_int(pthread_mutex_t *mtx, int *value);
void			write_bool(pthread_mutex_t *mtx, volatile bool *dest, \
				volatile bool value);
void			write_uint64(pthread_mutex_t *mtx, uint64_t *dest, \
				uint64_t value);

//mutex_utils2.c
void			write_int(pthread_mutex_t *mtx, int *dest, int value);
int				read_int(pthread_mutex_t *mtx, int *dest);
void			ft_free_struct(t_phil **phil);
uint64_t		get_time(void);
void			me_sleep(uint64_t ms);

//cleanup.c
void			join_threads(pthread_t	*threads, int n);
void			destroy_forks(t_data *data, pthread_mutex_t *forks);
int				ft_cleanup(t_data *data, t_phil **phil, pthread_mutex_t \
				*forks, int err);
#endif