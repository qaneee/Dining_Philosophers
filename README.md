# Dining Philosophers Problem 🍝

## Overview

The Dining Philosophers Problem is a classic synchronization problem used to illustrate the challenges of concurrent programming. It involves a scenario with five philosophers who alternate between thinking and eating. The philosophers share a circular table with five forks, one between each pair of philosophers. In order to eat, a philosopher needs both the fork on their left and the fork on their right. The problem demonstrates possible solutions to avoid deadlock and starvation in concurrent systems.

## Problem Statement

- There are **N philosophers** sitting at a round table.
- Each philosopher alternates between **thinking** and **eating**.
- To eat, a philosopher needs **both forks** (one on each side).
- **Forks are shared** between adjacent philosophers.
- No two adjacent philosophers can eat simultaneously (to avoid fork conflicts).
- The challenge is to design a solution so that all philosophers can eat without getting stuck in a deadlock or experiencing starvation.

### Running the Program

1. Clone this repository:
    ```bash
    git clone https://github.com/qaneee/Dining_Philosophers.git
    cd Dining_Philosophers
    ```

2. Run the main script (update for your language):
    ```bash
    make
    ./philo [philo_number] [time_to_die] [time_to_eat] [time_to_sleep]
    ```
    You can also add how many times each philosopher has to eat
    
3. Customize parameters, such as number of philosophers or execution mode, via command-line arguments or configuration files as described in the implementation.

## Example Output

```
Philosopher 1 is thinking
Philosopher 1 has taken a fork 
Philosopher 1 has taken a fork
Philosopher 1 is eating
Philosopher 2 is thinking
...
```
