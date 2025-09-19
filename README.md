# 🎲 Risk Game (C++ Terminal Version)

This repository contains a **C++ implementation** of the classic **Risk** strategy board game, playable directly from the terminal.  

The project was designed as an **academic exercise** to integrate **data structures** and **algorithmic concepts** such as:

- **Graphs**: to represent the map of territories and their connections.  
- **Lists, arrays, and deques**: to manage players, armies, turns, and movements.  
- **Dijkstra’s algorithm**: to calculate optimal conquest paths.  
- **Huffman Tree**: for game state compression and decompression.  
- **Persistence with text and binary files**: to save and load game sessions.  

---

## 🧩 Project Components

### **Component 1: Game Configuration**
Handles game initialization and turn-based progression.  

- **Command: `inicializar`**  
  - Initializes the game by asking for the number of players, their names/IDs, and distributing initial armies into territories (one per turn).  
  - Example outputs:  
    - `(Juego en curso) The game has already been initialized.`  
    - `(Inicialización satisfactoria) The game has been initialized correctly.`  

- **Command: `turno <player_id>`**  
  - Executes the full turn flow for a player:  
    1. Assign new units to territories.  
    2. Perform attacks (dice rolls, unit losses, and conquests).  
    3. Fortify between neighboring territories.  
  - Validates turn order and game state.  
  - Example outputs:  
    - `(Juego no inicializado) This game has not been initialized correctly.`  
    - `(Juego terminado) This game already had a winner.`  
    - `(Jugador no válido) Player <player_id> is not part of this game.`  
    - `(Jugador fuera de turno) It is not player <player_id>'s turn.`  
    - `(Turno terminado correctamente) Player <player_id>'s turn has ended.`  

- **Command: `salir`**  
  - Ends the execution of the program.  

---

### **Component 2: Game Persistence**
Implements saving and restoring game states, with optional **Huffman-based compression**.  

- **Command: `guardar <filename>`**  
  - Saves the current game state in a plain text file.  
  - Includes players, colors, territories, armies, and cards.  
  - Outputs:
    - `(Juego no inicializado) This game has not been initialized correctly.`
    - `(Comando correcto) The game has been saved successfully.`
    - `(Error al guardar) The game has not been saved correctly.`

- **Command: `guardar_comprimido <filename>`**  
  - Saves the current game state in a **compressed binary file** using Huffman encoding.  
  - Outputs:
    - `(Juego no inicializado) This game has not been initialized correctly.`
    - `(Comando correcto) The game has been successfully encoded and saved.`
    - `(Error al codificar y/o guardar) The game has not been encoded or saved correctly.`

- **Command: `inicializar <filename>`**  
  - Loads a game from a text or compressed binary file.  
  - Outputs:
  -   `(Juego en curso) The game has already been initialized.`
  -   `(Archivo vacío o incompleto) “file_name” does not contain valid information to initialize the game.`

**Binary file structure (`.bin`)**:  
- `n`: number of distinct characters (2 bytes).  
- `ci, fi`: ASCII character and frequency.  
- `w`: file length in characters.  
- `binary_code`: Huffman-compressed data, padded to 8 bits.  

---

### **Component 3: Game Strategies**
Provides decision-making support for players using pathfinding and cost analysis.  

- **Command: `costo_conquista <territory>`**  
  - Calculates the cost and sequence of territories to conquer a given target.  
  - Uses the nearest controlled territory as the starting point.  
  - Output includes path and required units.  

- **Command: `conquista_mas_barata`**  
  - Determines the cheapest possible conquest among all available options.  
  - Output includes the target territory, path, and cost in units.  

---

## 🚀 Compilation and Execution

Ensure **g++** is installed, then compile with:  

```bash
g++ -std=c++11 -o risk *.cpp *.cxx
