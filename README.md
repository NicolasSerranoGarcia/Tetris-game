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
- [Features](#features)
- [Contributing](#contributing)

---

## Overview

**Tetris-game** is a modern take on the classic Tetris game, developed in C++ using the SDL2 library as a rendering engine. This project was designed by me, and offers a solid foundation for understanding game mechanics and scene management.

### Key Features

- 🎮 **Gameplay Mechanics:** Core Tetris rules implemented for a faithful experience.
- ⏱️ **Real-Time Interaction:** Smooth response to user input for seamless gameplay.
- 🛠️ **Sounds and Music:** With volume control and a radio to choose songs.
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
<!-- Insert the excalidraw schema and maybe a UML diagram-->

---

## Features

Here is a list of features and functionalities that enhance the user experience:

<!-- Do every gif or video as if you were a bot inside a tutorial of an official game (imagine fortnite or an installation guide gif) -->

- Distinct scenes that add ambient to the program: an opening scene, a settings scene, a gameplay scene and a death scene. The death scene lets you go to the opening scene, play again or open the settings.

<!--Inert photo of each scene -->

- You can visualize the next three figures, swap a figure that you have saved previously, drop a figure directly (fast drop), rotate figures clockwise and anticlockwise...

<!-- Insert a gif of using all the functionalities -->

- You can change the key binds associated to each action, inside the settings. They are saved locally, so if you have personalized key binds they will be saved the next time you play

<!-- Insert a gif of changing the key binds, and maybe closing the program and opening it again to show -->

- There are sound effects and background music. The volume of both of them can be controlled inside the settings, using two sliders. There is also a radio used to skip, rewind and stop the music. There are 44 songs chosen randomly and automatically if the radio is ignored
<!-- Insert a video with audio of using the radio -->

- There is a slider in the settings scene to scroll through all the configuration. The mouse wheel can also be used for this purpose
<!-- Insert gif of using the mouse wheel and the slider -->

- There is a countdown that triggers when the settings is closed to let the user prepare to resume the game
<!-- show the countdown -->
  

- The stats of the best game are shown in the opening scene. They are saved locally, so the program can be closed without loosing the progress

<!-- Show an example of this -->

- The textures set an atmosphere for the gameplay

<!-- Show the textures -->

Here is a list of other (micro) features that further enhance the gameplay experience:


- Inside the settings, the buttons that are partially shown cannot be triggered on the zones that are not visible

<!-- show an example of pressing a button-->

- When a key bind button is pressed, other buttons and sliders can still be triggered. The pressed button will still be waiting for a key to be pressed.

<!-- Show a gif of this -->

- When in the settings, the figures of the game are not shown to prevent cheating
<!-- Show an example of closing and opening the settings -->


---

## Contributing

Thank you for considering contributing to this project!

Here’s a simple guide to help you get started:

### 1. Fork the repository

Click the **Fork** button at the top right of the page, then clone your fork locally:

```bash
git clone https://github.com/your-username/your-repo.git
cd your-repo
```

### 2. Create a new branch for your changes

```bash
git checkout -b my-feature-branch
```

### 3. Make your changes

Implement your changes. Please keep the code clean and follow the existing style if possible.

### 4. Test your changes

Make sure everything works as expected.  

### 5. Commit and push

```bash
git add .
git commit -m "Add feature: [your short description here]"
git push origin my-feature-branch
```

### 6. Open a Pull Request

Go to your fork on GitHub and click **"Compare & Pull Request"**.  
Provide a clear title and description of your changes.

### 💡 Not sure where to start?

Check the [issues page](#) and look for labels like `good first issue`.  
Feel free to open a discussion or issue if you have an idea or question!

---

Thanks for reading and enjoy this project!
