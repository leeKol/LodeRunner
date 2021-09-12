C++ OOP - Course Project
Remake of the "Lode Runner" game

This project is an implementation of the game Lode Runner.
The player has to collect all the coins in the game board while being careful of the enemies and thus win a stage. There are 4 stages to win in order to win the game.
When the game starts running, the game menu appears and the user must select a mode from 3 options.
Clicking on the "How To Play" button will display the game instructions on the screen. In this mode, clicking the arrow button will return it to the game menu.
Clicking on the "New Game" button will start the game itself, the game board of the first stage appears and the user can start playing.
Moving the knight is by using the arrows on the keyboard (up, down, right, left) and to digging a hole is by using the keys X (hole to the right of the knight) and Z (hole to the left of the knight),
note that a hole cannot be dug under the ladder. If an enemy falls into a hole it will be stuck in it for a few seconds after which it will return to above the hole and continue to move.
If the knight falls into a hole he is disqualified. It is possible to walk over a hole when there is a figure in it.
The movement of the knight and the enemies will not happen in the following situations:
Moving to a wall or floor, ascending not on a ladder, attempt to cross the borders of the board. If there is no floor, the figure will fall and that will stop only if it lands on a floor, ladder, or rope.
When the knight is eaten by an enemy or when he enters a hole, the stage restarts and the number of life decreases by one.
The knight can take gifts that are scattered on the stage board, and they give him extra life, extra time, extra score, protection from enemies and a bad gift that will add an enemy to the stage.
There are four stages (there can be more), when the knight has collected all the coins the stage is over and the next stage starts.
If the game was completed successfully (all the stages completed) a victory message will appear. If the player runs out of life then the game stops and a loss message will appear.
In both situations the user will return to the game menu and can choose what it wants next.
The menu also has an "Exit" button through which the user can end the program. In addition, the user can terminate the program at any time by clicking on the X button of the window.

Design:
1) Resources class- Singleton class, a class that provides all the resources of the program - music, sounds, images and fonts.
2) StateManager class- The program state manager, including a main function that is responsible for managing the various program states: 
		     menu state, game state, game instruction state. Contains members of all types of states.
3) Menu class- Responsible for the game menu, holds a vector of buttons, contains Button-type objects.
4) Button class- Responsible for a menu button.
5) GameInstructions class- Responsible for the game instruction state.
6) GameController class- Opens the stage file, reads it, and also closes it at the end. Manages the game board, and the course of the game.
7) GameObject class- A class that describes an object in the game. Includes members that describe the object.
8) MovingObject class- A class that describes a moving object in the game, inherits from the GameObject class.
9) Player class- Describes the player and is responsible for its implementation. Includes members that describe the player's condition, its score, its life number. Inherits from the MovingObject department.
10) Enemy class- A class that will bequeath to the classes of the three types of enemies. Inherits from the MovingObject department.
11) SmartEnemy class- A class that describes the enemy that moves smartly - moves towards the player. It has a unique movement function. Inherits from the Enemy class.
12) HorizontalEnemy class- A class that describes the enemy that moves horizontally left and right, has a unique movement function. Inherits from the Enemy class.
13) RandomEnemy class-  A class that describes the enemy that moves randomly has a unique movement function. Inherits from the Enemy class.
14) StaticObject class- A class that describes a static object in the game, inherits from the GameObject class.
15) Present class- A class that describes a gift in the game, inherits from the StaticObject class.
16) TimePresent class- A class describing a gift of extra time in the game. Inherits from the Present class.
17) LifePresent class- A class describing a gift of extra life in the game. Inherits from the Present class.
18) ScorePresent class- A class describing a gift of extra score in the game. Inherits from the Present class.
19) BadPresent class- A class describing a bad gift of an extra enemy in the game. Inherit from the Present class.
20) ShieldPresent class- A class describing a gift of a shield from enemies in the game. Inherit from the Present class.
21) Ladder class- A class describing a ladder in a game. Inherits from the StaticObject class.
22) Rope class- A class describing a rope in the game. Inherits from the StaticObject class.
23) Floor class- A class describing a floor in the game. Inherits from the Static Object class.
24) Coin class- A class describing a coin in the game. Inherits from the StaticObject class.
25) Hole class- A class describing a hole in the game. Inherits from the StaticObject class.

List of project files:
Resources.cpp + Resources.h - contains the implementation of the Resources class.
StateManager.cpp + StateManager.h - contains the implementation of the StateManager class .
Menu.cpp + Menu.h - contains the implementation of the Menu class.
Button.cpp + Button.h - contains the implementation of the Button class.
GameInstructions.cpp + GameInstructions.h - contains the implementation of the GameInstructions class.
GameController.cpp + GameController.h - Contains the implementation of the GameController class.
GameObject.cpp + GameObject.h - contains the implementation of the GameObject class.
MovingObject.cpp + MovingObject.h - contains the implementation of the MovingObject class.
Player.cpp + Player.h - contains the implementation of the Player class.
 Enemy.cpp + Enemy.h - contains the implementation of the Enemy class .
SmartEnemy.cpp + SmartEnemy.h - contains the implementation of the SmartEnemy class.
HorizontalEnemy.cpp + HorizontalEnemy.h - contains the implementation of the HorizontalEnemy class.
RandomEnemy.cpp + RandomEnemy.h - contains the implementation of the RandomEnemy class.
StaticObject.cpp + StaticObject.h - contains the implementation of the StaticObject class.
Present.cpp + Present.h - contains the implementation of the Present class.
TimePresent.cpp + TimePresent.h - contains the implementation of the TimePresent class.
LifePresent.cpp + LifePresent.h - contains the implementation of the LifePresent class.
ScorePresent.cpp + ScorePresent.h - contains the implementation of the ScorePresent class.
BadPresent.cpp + BadPresent.h - contains the implementation of the BadPresent class.
ShieldPresent.cpp + ShieldPresent.h - contains the implementation of the ShieldPresent class.
Ladder.cpp + Ladder.h - contains the implementation of the Ladder class.
Rope.cpp + Rope.h - contains the implementation of the Rope class.
Floor.cpp + Floor.h - contains the implementation of the Floor class.
Coin.cpp + Coin.h - contains the implementation of the Coin class.
Hole.cpp + Hole.h - contains the implementation of the Hole class.
main.cpp - implementation of the main  function of the program.
Macros.h - A file that contains all the constants we have in the program.
TextureNames.txt- contains the names of all the textures in the game.
SoundNames.txt - contains the names of all the sounds in the game.
1.txt + 2.txt + 3.txt + 4.txt - stage files.
_. png - The textures of the object with the appropriate name.
_ .wav - The sounds of the program in the appropriate name.

Main data structures:
The game board is stored in a unique_ptr two-dimensional vector that points on StaticObject-type objects. Allows holding all the objects on the board that inherit from the StaticObject class.
In the same way, there is such a vector that holds in it the enemies of all kinds.

Notable algorithms:
Smart enemy movement algorithm - gets the knight's current position on the board, it calculates the distance of the smart enemy from the knight according to horizontal and vertical distance.
First, it checks if the enemy is in the same line as the knight, and then checks which of the distances is shorter and according to this, it decides whether its movement will be horizontal or vertical (up, down, right, or left), considering the limitations of movement in the board.

Known bugs:
The smart enemy "shakes" while the knight is not moving, and in the transition from a ladder to a rope.
Stage file format:
Each stage will be received from a separate fixed name format file- numberlevel. For example, the name of the first stage file is "1", etc.
These files should be of txt type.

Other notes:
The player and enemies will start a stage only on a floor and in an empty cell. You can fall from a rope when you press the down key and also from a ladder when the keys are to the right or left.
It is not possible to jump to a ladder that is in the air, ie to press the key up and climb on it.
You can walk over a full hole.
A player is disqualified when entering a hole. The hole only serves as a trap for enemies and it is not possible to fall through it down.
For the sake of gameplay, it is not possible to dig a hole under a ladder.
We did not make the enemies faster than the player because in our eyes the gameplay is good and also at equal speed the game is challenging.
Several collisions have sounds. At the end of a game by losing or winning there are different backgrounds and animations. There is a special animation in the disqualification.
The moving figures in the game turn their faces according to the direction they are going (mirroring).