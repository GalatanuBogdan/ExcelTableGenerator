# Reservation Management Console Application

## Description
This C++ console application is designed to facilitate the management of reservations for specific individuals. While an Excel application might have limitations in generating reservation layouts for extended periods, this console application aims to bridge that gap by providing an efficient solution.


## Features
- Create and manage reservations for individuals.
- Generate reservation layouts for extended time frames
- There exists some parameters that can easily be modified
```cpp
#define STARTING_DAY 12
#define STARTING_MONTH 9
#define STARTING_YEAR 2022
#define ENDING_YEAR 2025

vector<string> persons = { "Beatrice", "Mariana", "Irina", "Carmen", "Alina"};
vector<string> availableHours = { "07:00","07:30","08:00","08:30","09:00","09:30","10:00","10:30","11:00","11:30","12:00","12:30","13:00","13:30","14:00","14:30","15:00","15:30","16:00","16:30","17:00","17:30","18:00","18:30","19:00","19:30","20:00","20:30","21:00","21:30","22:00" };
```
- More employees can be added and for each employee, a sheet will be created

## Getting Started
To use this application, follow these steps:

1. **Prerequisites:** Ensure you have a C++ compiler installed on your machine.
2. **Installation:** Clone this repository to your local machine.
3. **Compilation:** Compile the main source file using your C++ compiler. For example:
   ```bash
   g++ main.cpp -o reservation_app

## Actual Result
![](https://github.com/GalatanuBogdan/ExcelTableGenerator/blob/main/result.jpg)


