# MPI Student Marks & Attendance

A small **C++ MPI (Message Passing Interface)** program that demonstrates basic point-to-point communication between three processes, modeled as a university system that exchanges student marks and attendance data.

## Overview

The program simulates a small distributed system with three roles:

| Rank | Role | Responsibility |
|------|------|----------------|
| 0 | University Server | Holds total classes and student marks |
| 1 | Counselor System | Holds classes attended by the student |
| 2 | Attendance Processor | Computes final attendance percentage |

The program is split into two parts, separated by an `MPI_Barrier` to keep processes synchronized.

### Part 1 — Student Marks
- Process **0** sends the student marks (`75`) to Process **1** using `MPI_Send`.
- Process **1** receives the marks with `MPI_Recv` and prints them.

### Part 2 — Student Attendance
- Process **0** sends `totalClasses` (`48`) to Process **2**.
- Process **1** sends `classesAttended` (`36`) to Process **2**.
- Process **2** receives both values and prints the calculated attendance percentage:
  `(classesAttended / totalClasses) * 100`

## Prerequisites

- **Windows**
- **MS-MPI** installed (Microsoft MPI). Default install path is:
  - Headers: `C:/Program Files (x86)/Microsoft SDKs/MPI/Include`
  - Libs:    `C:/Program Files (x86)/Microsoft SDKs/MPI/Lib/x64`
- **MSVC** build tools (`cl.exe`) on `PATH`, e.g. via *Developer Command Prompt for VS* or the *MSBuild* tools.
- **Visual Studio Code** (optional, recommended) with the C/C++ extension — a ready-to-use build task is included in `.vscode/tasks.json`.

## Build

### Option A — Using VS Code
1. Open this folder in VS Code.
2. Press **Ctrl+Shift+B** (or `Terminal → Run Build Task...`).
3. Choose **Build and Run MPI** — it will compile `main.cpp` and link against `msmpi.lib`.
4. To also launch the program, run the **Run MPI Program** task, which invokes `mpiexec -n 4 main.exe`.

### Option B — From the command line
Open a *Developer Command Prompt for VS* in the project folder and run:

```bat
cl.exe main.cpp /I"C:/Program Files (x86)/Microsoft SDKs/MPI/Include" /EHsc /link /LIBPATH:"C:/Program Files (x86)/Microsoft SDKs/MPI/Lib/x64" msmpi.lib
```

This produces `main.exe`.

## Run

The program requires **at least 3 processes**. The provided task runs it with 4:

```bat
mpiexec -n 4 main.exe
```

### Sample Output

```
Process 0 (University Server) sent student marks: 75
Process 1 (Counselor System) received student marks: 75
Process 0 (University Server) sent total classes: 48
Process 1 (Counselor System) sent classes attended: 36
Process 2 (Attendance Processor) calculated attendance: 75%
```

The order of the lines may vary between runs since processes execute in parallel.

## Project Structure

```
.
├── main.cpp              # MPI source code
├── .vscode/
│   └── tasks.json        # VS Code build/run tasks
├── .gitignore            # Excludes build artifacts and node modules
└── README.md
```

## MPI Calls Used

- `MPI_Init` / `MPI_Finalize` — initialize and shut down the MPI environment.
- `MPI_Comm_rank` / `MPI_Comm_size` — get process rank and total process count.
- `MPI_Send` / `MPI_Recv` — point-to-point message passing.
- `MPI_Barrier` — synchronize all processes before the next phase.
