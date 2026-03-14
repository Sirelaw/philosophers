# Philosophers: Mastering Concurrency & Synchronization
## "The art of avoiding deadlocks in a resource-constrained environment."

This project is a deep-dive into the Dining Philosophers Problem, a classic synchronization challenge. The objective is to simulate a system where multiple threads (philosophers) compete for a limited set of shared resources (forks) without falling into deadlocks, starvation, or data races.

## The Embedded Context

In embedded systems, multiple tasks often compete for a single bus (like I2C/SPI) or a specific peripheral. If not managed correctly, the system hangs. This project demonstrates my ability to:

    Manage Shared Resources: Using Mutexes and Semaphores to gate access to hardware/memory.

    Precise Timing: Using gettimeofday and micro-sleeps to handle strict execution windows.

    Thread Safety: Ensuring data integrity across asynchronous execution flows.

## Technical Implementation

### 1. Multi-threading with pthreads

Each philosopher is represented as a separate thread. I implemented logic to ensure that threads synchronize their actions (eating, sleeping, thinking) while monitoring a "death" flag in a separate observer thread to ensure immediate system shutdown upon a philosopher's demise.

### 2. Synchronization Primitives

    Mutexes: Used to protect the state of each "fork" and the "last meal time" to prevent data races.

    Deadlock Avoidance: Implemented an optimized strategy for picking up forks (e.g., asymmetric picking or time-staggering) to ensure the circular wait condition is never met.

### 3. Time Management

Standard sleep functions (usleep) are often imprecise. I implemented a custom precise sleep function that uses a loop with small intervals to ensure the simulation stays accurate within millisecond tolerances—a critical skill for real-time embedded applications.

## Performance & Stability

The simulation is tested against extreme edge cases:

    Single Philosopher: Ensuring correct behavior when a resource can never be obtained.

    Large Clusters: Stress-testing with 200+ threads to verify the efficiency of the mutex locking mechanism.

    High-Speed Execution: Verifying that no data races occur even when survival times are tuned to the bare minimum.

## Getting Started
Prerequisites

    A C compiler (gcc or clang)

    Standard pthread library (usually available on Linux/macOS)

## Installation & Run
  Bash
  
```
git clone https://github.com/Sirelaw/philosophers.git
cd philo && make
# Arguments: [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]
./philo 5 800 200 200
```

### Bonus
The bonus part solves the problem by having the philosophers run as different processes.

```
cd philo_bonus && make
```
```
./philo [num_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [num_of_meals]
```
🧪 Testing for Data Races

This project was rigorously debugged using ThreadSanitizer and Valgrind to ensure zero data races and zero memory leaks.
Bash

gcc -fsanitize=thread -g philo.c -o philo
./philo 5 800 200 200



<img src="https://upload.wikimedia.org/wikipedia/commons/7/7b/An_illustration_of_the_dining_philosophers_problem.png" width=400px />

<sm>fig.1 - An illustration of the dining philosophers problem, src: wikipedia</sm>
