<p><a target="_blank" href="https://app.eraser.io/workspace/3FFjXxAjj3rc21NewYLR" id="edit-in-eraser-github-link"><img alt="Edit in Eraser" src="https://firebasestorage.googleapis.com/v0/b/second-petal-295822.appspot.com/o/images%2Fgithub%2FOpen%20in%20Eraser.svg?alt=media&amp;token=968381c8-a7e7-472a-8ed6-4a6626da5501"></a></p>

# TETRIS-GAME
_Fun, classic retro game!_

![last-commit](https://img.shields.io/github/last-commit/NicolasSerranoGarcia/Tetris-game?style=flat&logo=git&logoColor=white&color=0080ff "")

![repo-top-language](https://img.shields.io/github/languages/top/NicolasSerranoGarcia/Tetris-game?style=flat&color=0080ff "")

![repo-language-count](https://img.shields.io/github/languages/count/NicolasSerranoGarcia/Tetris-game?style=flat&color=0080ff "")

---

## Table of Contents
- [﻿Overview](#overview) 
- [﻿Getting Started](#getting-started) 
    - [﻿Prerequisites](#prerequisites) 
    - [﻿Installation](#installation) 
    - [﻿Usage](#usage) 
    - [﻿Testing](#testing) 
- [﻿Project Structure](#project-structure) 
- [﻿Features](#features) 
- [﻿Contributing](#contributing) 
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
This project is open source, and by no means it is aimed to benefit me in any financial way. The motivation behind this project is solely a desire to learn and overcome new obstacles. Feel free to fork the project and make any changes you find useful. You can also contact me via any of my socials if you need any information related to the project. I'm open to talk!

### Testing
This project has no QA testing. Every aspect has been designed and implemented correctly, but things go off very easily. If you encounter any unexpected behavior during your gameplay, you can report it via any of the socials listed [﻿here](linktr.ee/NicolasSerrano). You can also open a pull request if your goal is to fix it yourself. Please note that problems may arise if you try to execute this program outside of the requirements listed at the beginning. 

---

## Project Structure
The project follows a simple structure. A loop will run indefinitely until the program (window) is closed. Inside the loop, there are two main functions: 

- First, the program checks all the events that have been triggered since the last loop run. Each event is taken care individually until there are no events left. 
- Then, the program takes care of the rendering and the logic.
There are 4 different scenes. The user can change between scenes by pressing certain buttons, keys or loosing the game. The structure holds for each of the scenes, but each method will execute different code depending on which scene the program is on. There are auxiliary classes that use functionalities from SDL such as Image, Font or Button. Next is a UML diagram of the classes inside the program

![UML Diagram](https://app.eraser.io/workspace/2igz1dmaEs6voAcQUhTD?origin=share "")

---

## Features
Here is a list of features and functionalities that enhance the user experience:

- Distinct scenes that add ambient to the program: an opening scene, a settings scene, a gameplay scene and a death scene. The death scene lets you go to the opening scene, play again or open the settings.
![Scene photos](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExajE1bGJqYXMwdW82N3NhdDl2dHlhazM0eGx4Nzk5c3V5NWNpaGs2bSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/ccRrcecpw9PaM/giphy.gif "")

Gameplay features: 

- The next three figures to be played can be visualized while playing.
![Scene photos](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExajE1bGJqYXMwdW82N3NhdDl2dHlhazM0eGx4Nzk5c3V5NWNpaGs2bSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/ccRrcecpw9PaM/giphy.gif "")

- A figure can be swapped with another saved previously
![Scene photos](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExajE1bGJqYXMwdW82N3NhdDl2dHlhazM0eGx4Nzk5c3V5NWNpaGs2bSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/ccRrcecpw9PaM/giphy.gif "")

- A figure can be dropped to the bottom of the game board instantly (fast drop)
![Scene photos](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExajE1bGJqYXMwdW82N3NhdDl2dHlhazM0eGx4Nzk5c3V5NWNpaGs2bSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/ccRrcecpw9PaM/giphy.gif "")

- The figures can be rotated clockwise and anticlockwise
![Scene photos](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExajE1bGJqYXMwdW82N3NhdDl2dHlhazM0eGx4Nzk5c3V5NWNpaGs2bSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/ccRrcecpw9PaM/giphy.gif "")

Miscellaneous features:

- The key binds associated with each action can be changed inside the settings. They are saved locally, so the next time the program is opened they are automatically loaded.
![Scene photos](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExajE1bGJqYXMwdW82N3NhdDl2dHlhazM0eGx4Nzk5c3V5NWNpaGs2bSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/ccRrcecpw9PaM/giphy.gif "")

- There are sound effects and background music. The volume of both of them can be controlled inside the settings, using two sliders. There is also a radio used to skip, rewind and stop the music. There are 44 songs chosen randomly and automatically if the radio is ignored  
- There is a slider to scroll through the settings. The mouse wheel can also be used for this purpose
![Scene photos](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExajE1bGJqYXMwdW82N3NhdDl2dHlhazM0eGx4Nzk5c3V5NWNpaGs2bSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/ccRrcecpw9PaM/giphy.gif "")

- There is a countdown that triggers when the settings is closed to let the user prepare to resume the game
![Scene photos](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExajE1bGJqYXMwdW82N3NhdDl2dHlhazM0eGx4Nzk5c3V5NWNpaGs2bSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/ccRrcecpw9PaM/giphy.gif "")

- The stats of the best game are shown in the opening scene. The top 5 is saved locally, so the program can be closed without loosing the progress
![Scene photos](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExajE1bGJqYXMwdW82N3NhdDl2dHlhazM0eGx4Nzk5c3V5NWNpaGs2bSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/ccRrcecpw9PaM/giphy.gif "")

- The textures set an atmosphere for the gameplay
![Scene photos](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExajE1bGJqYXMwdW82N3NhdDl2dHlhazM0eGx4Nzk5c3V5NWNpaGs2bSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/ccRrcecpw9PaM/giphy.gif "")

Here is a list of other (micro) features that further enhance the gameplay experience:

- Inside the settings, the buttons that are partially shown cannot be triggered on the zones that are not visible
![Scene photos](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExajE1bGJqYXMwdW82N3NhdDl2dHlhazM0eGx4Nzk5c3V5NWNpaGs2bSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/ccRrcecpw9PaM/giphy.gif "")

- When a key bind button is pressed, other buttons and sliders can still be triggered. The pressed button will still be waiting for a key to be pressed.
![Scene photos](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExajE1bGJqYXMwdW82N3NhdDl2dHlhazM0eGx4Nzk5c3V5NWNpaGs2bSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/ccRrcecpw9PaM/giphy.gif "")

- When in the settings, the figures of the current gameplay are not shown to prevent cheating
![Scene photos](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExajE1bGJqYXMwdW82N3NhdDl2dHlhazM0eGx4Nzk5c3V5NWNpaGs2bSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/ccRrcecpw9PaM/giphy.gif "")

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
Check the [﻿issues page](#) and look for labels like `good first issue`.
Feel free to open a discussion or issue if you have an idea or question!

---

Thanks for reading and enjoy this project!



<!--- Eraser file: https://app.eraser.io/workspace/3FFjXxAjj3rc21NewYLR --->