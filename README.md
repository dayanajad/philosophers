*This project has been created as part of the 42 curriculum by dbinti-m.*

## PHILOSOPHERS

## Descriptions

The Dining Philosophers Problem: N philosophers sit around a table, each needing two forks to eat and each fork are shared between the neighbours. The sharing of the forks must be strategize to prevent deadlock or starvation.

Each philosopher is a thread and each fork is a mutex. To succeed in this project, we need to make sure no one dies when they shouldn't and no one survive when they shouldn't. 

## Instructions 

## Compilation
cd philo
make

## Execution

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep meals_required(optional)

All times are in milliseconds (ms). 

Example :
			
			./philo 5 800 200 200		(5 philosophers, no one should die)
			./philo	5 800 200 200 7		(5 philosophers ends after everyone eats 7 times)
			./philo 4 410 200 200		(4 philosophers, no one should die)
			./philo 1 800 200 200		(Single philosopher, should die (needs 2 forks))
			./philo 4 310 200 200		(1 philosopher should die)

## Output

timestamp_ms philosopher id action

## RESOURCES

- [Philosophers 42 Guide— “The Dining Philosophers Problem”](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)
- [POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/what_is_a_thread/)

## AI Usage

Used AI as a study buddy for threading concepts, race conditions and mutexes
