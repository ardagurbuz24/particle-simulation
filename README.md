## Physics Engine

## Features
- **Hybrid Architecture:** Direct access to C functions using the Python `ctypes` library.
- **Dynamic Physics:** Real-time simulation of gravity, friction, and collision physics.
- **Interactive Elements:**
  - **Left Click:** Magnetic attraction (pulls particles toward the cursor).
  - **GUI Button:** Instant particle explosion effect.
- **Real-time Control:** Adjustable gravity strength via a Python slider.

## Requirements
- C Compiler (GCC recommended)
- SDL2 Library
- Python 3.x
- CustomTkinter

## Setup and Execution

### 1. Compile the C Library
Convert the C code into a shared library (.so) that Python can communicate with:
```bash
gcc -fPIC -shared -o particle_lib.so main.c -lSDL2
```
### 2. Prepare the Python Environment

Install the required Python packages:
```Bash
pip install customtkinter
```

### 3. Run the Simulation
```Bash
python3 gui_controller.py
```