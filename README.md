*This project was created as part of the 42 curriculum by amyrodri and cassunca.*

# cub3d

## 📖 Description

**cub3d** is a graphical project inspired by early 3D games like *Wolfenstein 3D*.
The goal is to implement a basic raycasting engine using the MiniLibX library, rendering a 3D environment from a 2D map.

In this project, we built a real-time rendering engine capable of:

* Displaying textured walls using raycasting
* Handling player movement and rotation
* Managing different wall orientations (North, South, East, West)
* Rendering a minimap for spatial awareness
* Implementing interactive elements such as doors and secret passages

Additionally, we introduced a **custom theme based on secret codes**, including:

* Fibonacci sequences with missing values (hidden clues)
* Binary encoding spelling “FIB”
* Morse code representations
* Base64 encoded elements referencing the project theme

These elements act as **visual easter eggs** embedded into the textures, reinforcing the concept of hidden information and puzzles.

---

## 🖥️ Title Screen

The project includes an **interactive title screen** displayed before the game starts.

This screen allows the user to:

* Start the game
* Exit the game
* Interact with the interface using mouse input
* Experience a more complete and polished game flow
* Secret easter eggs

The title screen was designed to simulate a simple game menu, improving usability and presentation beyond the base project requirements.

---

## ⚙️ Instructions

### 📦 Requirements

* Linux / macOS
* `gcc`
* `make`
* MiniLibX library

---

### 🔨 Compilation

Clone the repository and run:

```bash
make
```

---

### ▶️ Execution

Run the program with a valid `.cub` map file:

```bash
./cub3d maps/example.cub
```

---

### 🎮 Controls

| Key           | Action           |
| ------------- | ---------------- |
| W / A / S / D | Move player      |
| ← / →         | Rotate camera    |
| Mouse         | Look around      |
| SPACE         | Open/close doors |
| ESC           | Exit             |

---

## 🧠 Technical Overview

### 🧱 Raycasting Engine

The core of the project is a **raycasting algorithm** that:

* Casts one ray per vertical screen column
* Detects wall intersections using DDA (Digital Differential Analysis)
* Calculates distance to render perspective-correct walls
* Applies textures based on wall orientation

---

### 🗺️ Map System

The map is parsed from a `.cub` file and includes:

* Walls (`1`)
* Empty spaces (`0`)
* Player spawn (`N`, `S`, `E`, `W`)
* Doors (`D`)
* Secret doors (`S`)

A flood fill algorithm ensures the map is closed and valid.

---

### 🚪 Doors System

We implemented a door system using a custom structure:

* Doors have an **open state (0.0 → 1.0)**
* Smooth animation is handled frame-by-frame
* Collision depends on how open the door is
* Secret doors (`S`) are present in the map but **cannot be opened directly**, allowing for puzzle-based extensions

---

### 🧭 Minimap

A circular minimap displays:

* Nearby walls
* Doors and secret areas
* Player position and direction

---

### 🎨 Textures & Theme

All textures were designed around a **“secret codes / hidden knowledge”** theme:

* Fibonacci sequence with missing values
* Binary encoding
* Morse code representations
* Base64 references
* Locked doors with visual indicators (metal door)

These elements encourage exploration and interpretation.

---

## 📚 Resources

### 📖 Learning Resources

* Lode Vandevenne — Raycasting Tutorial
  https://lodev.org/cgtutor/raycasting.html

* Permadi Raycasting Tutorial
  https://permadi.com/1996/05/ray-casting-tutorial/

* MiniLibX Documentation (42)

---

### 🤖 AI Usage

Artificial Intelligence tools (ChatGPT) were used during the development process for:

* Debugging logic issues (raycasting, doors, minimap)
* Structuring and organizing code under 42 constraints
* Texture ideas
* Providing guidance on implementing features like:
  * Door systems
  * Secret doors
  * Collision handling
* Assisting in writing documentation (this README)

All core logic, implementation, and integration were developed and validated by the authors.

---

## 🚀 Final Notes

This project explores the fundamentals of 3D rendering using minimal tools and emphasizes:

* Mathematical reasoning
* Memory management
* Structured problem solving

The addition of an **interactive title screen** and a **hidden code-based theme** enhances both usability and player experience, going beyond the original project requirements.

---