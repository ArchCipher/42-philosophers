# <p align="center"> Philosophers - Dining Philosophers Problem </p>

**42 Project | Threading & Synchronization**  
**Objective:** Solve the classic dining philosophers problem using threads and mutexes, ensuring no deadlocks or data races.

---

## Overview

**Philosophers** is a concurrency project that solves the classic dining philosophers problem. Multiple philosophers sit around a table, alternating between thinking, eating, and sleeping. The challenge is to prevent deadlocks and ensure all philosophers can eat without starvation.

---

## Skills Demonstrated

- **Threading:** Creating and managing threads with `pthread`
- **Mutexes:** Synchronization primitives for shared resource protection
- **Deadlock Prevention:** Avoiding circular wait conditions
- **Race Condition Prevention:** Thread-safe data access
- **Timing:** Precise timing with `gettimeofday()` and `usleep()`
- **State Management:** Tracking philosopher states and meal counts
- **Monitoring:** Detecting death conditions and simulation end

---

## Project Structure

```
philosophers/
├── philo/                   # Mandatory version (threads + mutexes)
│   ├── src/
│   │   ├── philo.c         # Main program and initialization
│   │   ├── threads.c        # Thread creation and management
│   │   ├── routine.c        # Philosopher routine (think/eat/sleep)
│   │   ├── monitor.c        # Death monitoring
│   │   ├── parser.c         # Argument parsing
│   │   └── philo_utils.c    # Utility functions
│   ├── philo.h              # Header file
│   └── Makefile
├── philo_bonus/             # Bonus version (processes + semaphores)
└── en.subject.pdf           # Project subject
```

**Key Components:**
- **Thread Management:** Creates one thread per philosopher
- **Mutex Locks:** Protects forks (shared resources)
- **Monitor Thread:** Checks for philosopher death
- **Timing System:** Tracks simulation time and philosopher states

---

## Problem Description

**The Dining Philosophers Problem:**
- N philosophers sit around a circular table
- Each philosopher needs 2 forks to eat
- There are N forks (one between each pair of philosophers)
- Philosophers alternate between thinking, eating, and sleeping
- Goal: Prevent deadlock and ensure all philosophers can eat

**Solution Approach:**
- Use mutexes to represent forks
- Implement deadlock prevention (e.g., odd/even philosopher strategy)
- Monitor philosopher states to detect death
- Ensure thread-safe printing and state updates

---

## Program Arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Example:**
```bash
./philo 5 800 200 200
# 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep

./philo 5 800 200 200 7
# Same as above, but each philosopher must eat 7 times
```

---

## Features

### Mandatory
- Thread-based implementation
- Mutex synchronization
- Deadlock prevention
- Death detection
- Thread-safe logging
- Optional meal limit

### Bonus (In Progress)
- Process-based implementation
- Semaphore synchronization
- Additional features

---

## Technical Implementation

### Deadlock Prevention

**Strategy:** Odd/Even Philosopher Approach
- Odd-numbered philosophers pick up left fork first, then right
- Even-numbered philosophers pick up right fork first, then left
- This prevents circular wait (deadlock condition)

### State Management

Each philosopher cycles through states:
1. **Thinking** - Waiting for forks
2. **Eating** - Holding two forks, consuming meal
3. **Sleeping** - Resting after eating

### Monitoring

A separate monitoring thread checks:
- Time since last meal for each philosopher
- Death condition (time_to_die exceeded)
- Meal count completion (if specified)

---

## Compilation & Usage

```bash
# Build mandatory version
cd philo && make

# Run simulation
./philo 5 800 200 200

# Build bonus version
cd philo_bonus && make
```

---

## Testing

The project has been tested with:
- **[42-philosophers-tester](https://github.com/dantonik/42-philosophers-tester)** - Comprehensive test suite
- **[Philosophers Visualizer](https://nafuka11.github.io/philosophers-visualizer/)** - Visual representation of philosopher states and actions
- Various philosopher counts (1, 2, 5, 31, 131)
- Edge cases (single philosopher, large counts)
- Timing validation
- Deadlock detection

---

## Key Challenges & Solutions

### 1: Deadlock Prevention
**All philosophers picking up left fork simultaneously causes deadlock**

I implemented odd/even strategy to break circular wait

### 2: Race Conditions
**Multiple threads accessing shared data simultaneously**
I use mutexes to protect shared resources (forks, state, printing). In bonus part I used semaphores to achieve the same.

### 3: Precise Timing
**Ensuring accurate timing for eating, sleeping, death detection**
I used `gettimeofday()` for timestamps, and careful `usleep()` usage with while loop

### 4: Thread-Safe Printing
**Problem:** Multiple threads printing simultaneously causes garbled output  
**Solution:** Use mutex-protected printing function

---

*This project demonstrates mastery of concurrent programming, synchronization primitives, and solving classic computer science problems.*
