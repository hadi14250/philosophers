<div align="center">
<a href="https://github.com/hadi14250">
    <img src="github_gifs/spagheti.gif" alt="spaghetti gif" width="150" height="150">
  </a>
  <h3 align="center">Philosophers</h3>
  Puts the Famous Philosophers Problem Into Code
  <br>
  <br>
</div>

<div align="center">
<a href="https://github.com/hadi14250">
    <img src="github_gifs/spagheti.gif" alt="philo gif"  width="600" height="400">
  </a>


</div>

<br>

# Philosophers

A project designed to tackle one of the classic synchronization problems in computer science. The goal was to simulate the dining philosophers problem, which involves coordinating multiple threads with proper synchronization to avoid deadlock and ensures the philosophers do not die.

<br>

## Features

  - 🔄 Concurrency management.
  - 🚦 Deadlock prevention.
  - 🧩 Synchronization primitives.

<br>

## How to run

- Go to root directory and run `make`
- Run `./philo 5 1000 400  400 5`

<br>

The numbers above stand for: <br>
`./philo <<number_of_philosophers>> <<time_to_die>> <<time_to_eat>> <<time_to_sleep>> <<number_of_times_each_philosopher_must_eat]>>`

## Rules
- `number_of_philosophers`: The number of philosophers and also the number
of forks.
- `time_to_die` (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping
- `number_of_times_each_philosopher_must_eat` (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.
-  Each philosopher has a number ranging from 1 to number_of_philosophers.
- Philosopher number 1 sits next to philosopher number number_of_philosophers.
Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.

<br>
