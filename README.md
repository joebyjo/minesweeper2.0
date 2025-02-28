# Minesweeper 2.0  
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) ![SFML](https://img.shields.io/badge/SFML-green?style=for-the-badge&logo=sfml&logoColor=white&logoSize=auto) ![Visual Studio Code](https://img.shields.io/badge/Visual%20Studio%20Code-0078d7.svg?style=for-the-badge&logo=visual-studio-code&logoColor=white)

Welcome to **Minesweeper 2.0**! A thrilling twist on the classic **Minesweeper** game, now enhanced with **powerups** to help you flag mines, reveal safe tiles, and strategize your way to victory.

---

## 📦 Installation Instructions  
To get the game up and running, follow these simple steps:

1. Install [SFML](https://www.sfml-dev.org/index.php).
2. Compile the program and run the game using `make`.
3. After compilation, run `minesweeper.out` to play.

---

## 🎮 How to Play  
The objective is simple: clear the grid of hidden squares without triggering any mines. Here’s how you can navigate the game:

### **1. Reveal Tiles**:
- Left-click on a tile to reveal it.
- If the tile contains a number, it indicates how many mines are adjacent.
- If the tile is empty, it will automatically reveal surrounding empty tiles until a number is encountered.
- Clicking on a mine ends the game.

### **2. Flag Tiles**:
- Right-click to place a flag on a tile where you suspect a mine is hidden.
- Right-click again to remove the flag.

### **3. Powerups**:  
Powerups randomly appear on the grid, and you can collect them by clicking on their tile. They provide unique abilities to assist you:

- **Flag Surrounding Mines**: Automatically flags all mines surrounding a revealed tile.
- **Reveal All Mines Temporarily**: Briefly displays the locations of all mines. Use this time wisely to plan your next moves!

### **4. Game Over Conditions**:
- You reveal a mine (Game Over).
- You successfully uncover all non-mined tiles (Victory!).

**Pro Tip**: If you're new to Minesweeper, check out [this article](https://en.wikipedia.org/wiki/Minesweeper_(video_game)) to learn the classic rules!

---

## 📸 Images  
Here’s a preview of the game in action:

### **Starting Screen**  
![starting screen](assets/readme/starting_screen.png)

### **Difficulty Screen**  
![difficulty screen](assets/readme/difficulty_screen.png)

### **In-Game Screen**  
![game screen](assets/readme/game_screen.png)

### **Lose Screen**  
![lose screen](assets/readme/lose_screen.png)

---

## 🚀 Features

- **Interactive Powerups**: Add strategy to the game with randomly appearing powerups.
- **Customizable Difficulty**: Choose your preferred difficulty level.
- **Smooth User Experience**: Clean UI powered by SFML for optimal gameplay.

---

## 🛠️ Contributing  
Feel free to open issues and submit pull requests if you want to contribute to the project! Here's how you can contribute:

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Commit your changes and push to your fork.
4. Create a pull request to the main repository.

---

## 💬 Feedback  
Your feedback is invaluable! If you have suggestions or ideas to improve the game, please open an issue or submit a pull request.

---

Happy gaming! Enjoy Minesweeper 2.0. 🕹️
