# C++ Chess Game

A chess game project implemented in C++ using SDL3 and miniaudio

<img src="readme_files\chess_game.png" width="500" alt="chess_game">


# 📋Features
- Local Game 1v1 (on the same machine)
- Graphic implementation using SDL3
- Audio implementation using miniaudio
- All rules are correctly implemented and working
- A sidebar showing turns and the last 15 played moves
# 📦 Project tree

```
├── font
│   └── arial.ttf
├── include
│   ├── Bishop.h
│   ├── DrawMoves.h
│   ├── King.h
│   ├── Knight.h
│   ├── LegalMove.h
│   ├── Movement.h
│   ├── Pawn.h
│   ├── Piecetypes.h
│   ├── Promotion.h
│   ├── Queen.h
│   ├── Rendering.h
│   ├── Rook.h
│   ├── SidebarMoves.h
│   ├── SpecialMoves.h
│   └── Struct.h
├── pieces
│   ├── black-bishop.png
│   ├── black-king.png
│   ├── black-knight.png
│   ├── black-pawn.png
│   ├── black-queen.png
│   ├── black-rook.png
│   ├── white-bishop.png
│   ├── white-king.png
│   ├── white-knight.png
│   ├── white-pawn.png
│   ├── white-queen.png
│   └── white-rook.png
├── readme_files
│   └── chess_game.png
├── sounds
│   ├── chess_victory.wav
│   ├── eat_sound.wav
│   ├── movement_sound.wav
│   └── stall_draw_sound.wav
├── .gitignore
├── README.md
└── main.cpp
```

# 🔨 Installation
1. Go to [https://github.com/aAnthony030/Chess/releases/tag/v1.0.0](https://github.com/aAnthony030/Chess/releases/tag/v1.0.0) and download the attachment file
2. Unzip the folder
3. Open the main.exe file
4. If you get a warning from windows go over it
5. Enjoy the game :)

# 🎮 How to play
- Click on a piece to select it
- To move the selected piece click on an highlighted square
- To deselect a piece click any not-highlighted square
- All standard chess moves are included
    - Castling
    - En Passant
    - Piece promotion
    - Check, checkmate, draw, stall
    
# 🚀 Things to improve in the future
- [ ] Insert a restart button
- [ ] Insert AI opponent for making it playable single player
- [ ] Insert timer

----------
Made with ❤️ <small><small>(and sweat)</small></small> by [@aAnthony030](https://github.com/aAnthony030)
