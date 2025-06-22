<div id="top"></div>

<div align="center">

# TETRIS-GAME

<em>Fun, classic retro game!</em>

<!-- BADGES -->
<img src="https://img.shields.io/github/last-commit/NicolasSerranoGarcia/Tetris-game?style=flat&logo=git&logoColor=white&color=0080ff" alt="last-commit">
<img src="https://img.shields.io/github/languages/top/NicolasSerranoGarcia/Tetris-game?style=flat&color=0080ff" alt="repo-top-language">
<img src="https://img.shields.io/github/languages/count/NicolasSerranoGarcia/Tetris-game?style=flat&color=0080ff" alt="repo-language-count">

</div>

---

## Table of Contents

- [Overview](#overview)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Testing](#testing)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

---

## Overview

**Tetris-game** is a modern take on the classic Tetris game, developed in C++ using the SDL2 library as a rendering engine. This project was designed completely by me, and offers a solid foundation for understanding game mechanics and scene management.

### Key Features

- 🎮 **Gameplay Mechanics:** Core Tetris rules implemented for a faithful experience.
- ⏱️ **Real-Time Interaction:** Smooth response to user input for seamless gameplay.
- 🛠️ **Modular Architecture:** Easy to maintain and expand with new features.
- 🌌 **Scene Management:** Efficient handling of scene transitions and updates.
- ✍️ **Keybind mapping:** Keybinds can be changed for a better experience.
- ↩️ **Many more:** Play to try all the features!

---

## Getting Started

### Prerequisites

Before building and running the game, make sure you have:

- **OS:** Ubuntu 20.04+ (or similar Linux distro)
- **Compiler:** g++ (GCC) 9.3.0 or later
- **Libraries:** SDL2, SDL2_ttf, SDL_Image, SDL_Mixer

### Installation
To install the required libraries on Ubuntu:

```bash
sudo apt update
sudo apt install build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
```

To clone the repo locally:
```bash
git clone https://github.com/NicolasSerranoGarcia/Tetris-game.git
cd Tetris-game
```

To compile the game into an executable:

```bash
make
```
Note: The executable will be named "tetris" and will be located on the repo clone

To run the game:
```bash
./tetris
```

### Usage

This project is open source, and by no means it is aimed to benefit me in a financial way. The motivation behind this project is solely a desire to learn and overcome new obstacles. Feel free to fork the project and make any changes you find useful. You can also contact me via any of my socials if you need any information related to the project. I'm open to talk!

### Testing

This project has no QA testing. Every aspect has been designed and implemented correctly, but things go off very easily. If you encounter any unexpected behavior during your gameplay, you can report it via any of the socials listed [here](linktr.ee/NicolasSerrano). You can also open a pull request if your goal is to fix it yourself. Please note that problems may arise if you try to execute this program outside of the requirements listed at the beginning. 

---

## Project Structure

The project follows a simple structure, consisting of an opening screen, settings screen, gameplay screen and death screen. Each of them is triggered by the user when interacting with the program. 
<!-- Insert images of the scenes when they are finished-->

---

## Contributing

Thank you for considering contributing to this project!

Here’s a simple guide to help you get started:

### 🧭 1. Fork the repository

Click the **Fork** button at the top right of the page, then clone your fork locally:

```bash
git clone https://github.com/your-username/your-repo.git
cd your-repo
```

### 🌱 2. Create a new branch for your changes

```bash
git checkout -b my-feature-branch
```

### 🔨 3. Make your changes

Implement your changes. Please keep the code clean and follow the existing style if possible.

### 🧪 4. Test your changes

Make sure everything works as expected.  

### ✅ 5. Commit and push

```bash
git add .
git commit -m "Add feature: [your short description here]"
git push origin my-feature-branch
```

### 🚀 6. Open a Pull Request

Go to your fork on GitHub and click **"Compare & Pull Request"**.  
Provide a clear title and description of your changes.

### 💡 Not sure where to start?

Check the [issues page](#) and look for labels like `good first issue`.  
Feel free to open a discussion or issue if you have an idea or question!

---

## License
