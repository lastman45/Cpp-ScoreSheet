# ⚽ Soccer Player Scoresheet Manager

A command-line C++ application for tracking and managing soccer player statistics, including goals, assists, and disciplinary cards. Supports data entry, sorting, searching, and file persistence.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Compilation](#compilation)
- [Usage](#usage)
- [Program Walkthrough](#program-walkthrough)
- [Data Structure](#data-structure)
- [Function Reference](#function-reference)
- [Output File Format](#output-file-format)
- [Known Limitations & Notes](#known-limitations--notes)
- [Future Improvements](#future-improvements)

---

## Overview

The Soccer Player Scoresheet Manager allows a coach, analyst, or administrator to input statistics for a squad of players and immediately get a team summary, a ranked leaderboard by goals scored, a player lookup tool, and a saved record to disk. All interaction is through the terminal/console.

---

## Features

- **Multi-player data entry** — Input stats for any number of players in a single session
- **Input validation** — Rejects negative values for goals, assists, and cards
- **Team statistics summary** — Calculates and displays total goals, assists, yellow cards, and red cards across the entire squad
- **Goals leaderboard** — Sorts players in descending order by goals scored using Bubble Sort
- **Player search** — Look up any individual player by name and display their full stat line
- **File export** — Saves all player data to a plain-text file (`players.txt`) for record-keeping
- **Dynamic memory allocation** — Player array is sized at runtime based on user input

---

## Requirements

| Requirement | Details |
|---|---|
| **Compiler** | Any C++ compiler supporting C++11 or later (e.g., `g++`, `clang++`, MSVC) |
| **OS** | Windows (uses `<conio.h>` for `getch()`) |
| **Standard Libraries** | `<iostream>`, `<cstring>`, `<fstream>`, `<stdio.h>` |
| **Platform-specific** | `<conio.h>` — Windows only (see [Known Limitations](#known-limitations--notes)) |

---

## Compilation

### Windows (using g++ / MinGW)

```bash
g++ -o scoresheet Scoresheet.cpp
```

### Windows (using MSVC via Developer Command Prompt)

```bash
cl Scoresheet.cpp /Fe:scoresheet.exe
```

### Run the program

```bash
./scoresheet        # Linux/macOS (after porting)
scoresheet.exe      # Windows
```

---

## Usage

The program is fully interactive. Upon launch, follow the on-screen prompts:

```
Enter number of players: 3

Enter Player Name: Messi
Enter Goals Scored: 12
Enter Assists: 8
Enter Yellow Cards: 1
Enter Red Cards: 0

Enter Player Name: Ronaldo
Enter Goals Scored: 10
Enter Assists: 5
Enter Yellow Cards: 2
Enter Red Cards: 0

Enter Player Name: Neymar
Enter Goals Scored: 7
Enter Assists: 11
Enter Yellow Cards: 3
Enter Red Cards: 1
```

After all players are entered, the program automatically:

1. Displays the **team statistics summary**
2. Prints the **goals leaderboard** (sorted high to low)
3. Prompts for a **player name search**
4. **Saves** all data to `players.txt`
5. Exits after a keypress

---

## Program Walkthrough

### Step 1 — Enter Player Count

The program asks how many players to record. A dynamic array is allocated on the heap to hold exactly that many `SoccerPlayer` structs.

### Step 2 — Enter Player Data

For each player, the program collects:
- **Name** (up to 19 characters, no spaces — uses `cin >>`)
- **Goals scored** (validated: must be ≥ 0)
- **Assists** (validated: must be ≥ 0)
- **Yellow cards** (validated: must be ≥ 0)
- **Red cards** (validated: must be ≥ 0)

If a negative number is entered for any stat, the prompt repeats until a valid value is given.

### Step 3 — Team Summary

Displays aggregate totals for the whole squad:

```
Player Statistics Summary:
Total Goals: 29
Total Assists: 24
Total Yellow Cards: 6
Total Red Cards: 1
```

### Step 4 — Sorted Leaderboard

Players are sorted by goals (descending) using Bubble Sort and printed:

```
Players sorted by goals scored:
Messi - Goals: 12
Ronaldo - Goals: 10
Neymar - Goals: 7
```

### Step 5 — Player Search

You are prompted to enter a player name. An exact case-sensitive string match is performed using `strcmp`. If found, the player's full stat line is displayed:

```
Enter player name to search: Messi

Player Name: Messi
Goals Scored: 12
Assists: 8
Yellow Cards: 1
Red Cards: 0
```

If no match is found:

```
Player not found!
```

### Step 6 — Save & Exit

All player data is written to `players.txt` in the working directory. The program then waits for a keypress (`getch()`) before exiting.

---

## Data Structure

Each player's data is stored in a `SoccerPlayer` struct:

```cpp
struct SoccerPlayer
{
    char PlayerName[20];  // Player's name (max 19 chars + null terminator)
    int Goals;            // Total goals scored
    int Assists;          // Total assists
    int YellowCards;      // Yellow card count
    int RedCards;         // Red card count
};
```

An array of `SoccerPlayer` structs is dynamically allocated at runtime:

```cpp
SoccerPlayer *Players = new SoccerPlayer[playerCount];
```

Memory is freed with `delete[] Players` before the program exits.

---

## Function Reference

### `void displayPlayerStats(SoccerPlayer *Players, int playerCount)`

Iterates through all players, accumulates totals for each stat category, and prints a team-wide summary to `stdout`.

**Parameters:**
- `Players` — Pointer to the player array
- `playerCount` — Number of players in the array

---

### `void sortPlayersByGoals(SoccerPlayer *Players, int playerCount)`

Performs an in-place descending Bubble Sort on the player array, ordered by the `Goals` field. The array is sorted in-place; the original order is not preserved.

**Parameters:**
- `Players` — Pointer to the player array
- `playerCount` — Number of players in the array

**Time complexity:** O(n²) — suitable for small squads

---

### `void searchPlayer(SoccerPlayer *Players, int playerCount)`

Prompts the user for a name and performs a linear search through the array using `strcmp` for exact matching. Prints full stats if found, or a "not found" message otherwise. Search is **case-sensitive**.

**Parameters:**
- `Players` — Pointer to the player array
- `playerCount` — Number of players in the array

---

### `void savePlayersToFile(SoccerPlayer *Players, int playerCount)`

Opens (or creates) `players.txt` in the current working directory and writes all player records, one per line, in space-delimited format. Overwrites the file if it already exists.

**Parameters:**
- `Players` — Pointer to the player array
- `playerCount` — Number of players in the array

**Output file:** `players.txt` (see format below)

---

## Output File Format

The file `players.txt` is created in the current working directory. Each line represents one player with space-separated values:

```
PlayerName Goals Assists YellowCards RedCards
```

**Example:**

```
Messi 12 8 1 0
Ronaldo 10 5 2 0
Neymar 7 11 3 1
```

> ⚠️ **Note:** Player names containing spaces will break the file format and also cannot be entered via `cin >>`. Names should be single words or hyphenated (e.g., `Van-Dijk`).

---

## Known Limitations & Notes

| Issue | Details |
|---|---|
| **Windows-only (`<conio.h>`)** | The `getch()` call at the end of `main()` uses `<conio.h>`, which is not available on Linux or macOS. Replace with `std::cin.get()` for cross-platform compatibility. |
| **No-space names only** | `cin >>` stops at whitespace, so names like `"John Doe"` must be entered as `"JohnDoe"` or `"John_Doe"`. |
| **Case-sensitive search** | `strcmp` is exact; searching `"messi"` will not find `"Messi"`. |
| **Fixed name buffer** | `PlayerName` is fixed at 20 characters. Names longer than 19 characters will be silently truncated and may cause undefined behaviour. |
| **No input recovery on non-numeric entry** | If a user types a letter where a number is expected (e.g., goals), `cin` enters a fail state and the loop may behave unexpectedly. |
| **Bubble Sort for large datasets** | The O(n²) sort is fine for a typical squad (11–25 players) but would be inefficient for large datasets. |
| **File overwrite without warning** | `players.txt` is always overwritten without confirmation. |

---

## Future Improvements

- **Cross-platform support** — Replace `getch()` with a portable alternative
- **Space-separated names** — Use `cin.getline()` or `std::getline()` to support full names
- **Case-insensitive search** — Convert both strings to lowercase before comparing
- **Input stream error handling** — Clear `cin` fail state on invalid (non-numeric) input
- **Load from file** — Add a function to read `players.txt` back into the array at startup
- **Delete / edit player** — Allow modifying or removing an existing player's record
- **Per-player points system** — Calculate a performance score (e.g., goals × 3 + assists × 1 − red cards × 3)
- **Menu-driven interface** — Replace the fixed execution flow with a looping menu for a better user experience

---

## License

This project is not currently licensed. All rights reserved by the original author unless otherwise stated.
