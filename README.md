## philosophers - The infamous dining philosophers problem

![result](https://github.com/oipadeol/philosophers/blob/main/readme_additions/result.png)

This is an implementation of the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

The dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

The problem is designed to illustrate the use of threads and resource sharing in a concurrent programming environment.
Each philosopher is represented by a thread. 

Each philosopher has two forks, and each fork is represented by a mutex. Each philosopher must acquire the two forks in order to eat. The forks are shared between the philosophers, so each philosopher must acquire the mutex associated with the fork. 

Deadlock is a problem where two or more threads are blocked waiting for each other, which must be avoided. A correct solution to the dining philosophers problem is to avoid deadlock.

## usage

The mandatory part solves the problem using different threads.

```
cd philo && make
```
```
./philo [num_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [num_of_meals]
```

The bonus part solves the problem by having the philosophers run as different processes.

```
cd philo_bonus && make
```
```
./philo [num_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [num_of_meals]
```

<img src="https://upload.wikimedia.org/wikipedia/commons/7/7b/An_illustration_of_the_dining_philosophers_problem.png" width=400px />

<sm>fig.1 - An illustration of the dining philosophers problem, src: wikipedia</sm>
