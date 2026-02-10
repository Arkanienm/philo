*This project has been created as part of the 42 curriculum by amurtas*

# **Description**
The philosopher project of 42 consists in making philosophers eat, sleep, and think without anyone dying of hunger. The main difficulty was to manage concurrent access to fourchettes (shared resources) to avoid Data Races, while preventing Deadlocks.

# **Compilation , Execution :**

## **Here is how to compile and run the project:**

* ### **Compilation :**

```bash
make
```

* ### **Execution :**

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat
```

```bash
./philo 4 800 200 200 7
```

# **Resources**

I found several resources on the internet but the main ones are codequoi for threads and mutex , gemini for the struct of the project and how pthread etc work .
