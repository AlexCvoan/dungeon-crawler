# dungeon-crawler
Basic dungeon crawler, in the console, written in C


The program I’ve made represents a small game, in which the user must collect the treasure marked on the map. In his way, he will face either an enemy, which will follow the player’s character at a difficulty chosen by the user, or a bunch of traps. The game will show the message “Game Over!” if the player hits the walls of the map, a trap or the enemy, giving the user an option to try again. If the player succeds and touches the treasure, the game will end. 

The game starts by executing the script() function. This function is responsible with informing the user about the way the game works, and also with setting the game mode ( traps or enemy) and the difficulty (the difficulty variable, with values from 1 to 3, used only in the enemy mode, will influence the gameplay by “allowing” the enemy to move at different paces; this variable will be used along another variable, enemy_contor)

After the script function, the rest of the code will run in a do…while loop, in order to gave the user the option to try again, in case of failure. This is done with the variable keepPlaying, which will be set to 1 if the user chooses to try again.

In the do…while block of instructions, the variables keepPlaying and gameOver will be set to 0. The variable gameOver is used later on to test if the user makes any mistakes. Next, the coordinates of the player’s character are set to 1, so the character will appear on the map in the left-upper corner. The variable random will be initialized with a random value; this variable will be used later on to generate the random coordinates of the traps. The coordinates of the enemy will also be generated randomly, but with some conditions so the enemy will not be in a disadvantageous position, due to the random generated coordinates.

A while loop will be used next, with the condition “gameOver!=1”. The first function called is render(). This function is used to print the game’s map on the console. In this function, if the gameMode is set to 1, the function traps() will be called. This function is used to generate the random coordinates of the traps. If the gameMode is set to 2, the function enemy() will be called. This function will change the enemy’s coordinates, in order for the enemy to follow the player on the map. This change of coordinates will happen at different paces, based on the difficulty chosen by the user in the script() function. If the lowest difficulty is selected, the enemy will move every time enemy_contor is divisible by 3. In the medium difficulty, the enemy will move every time enemy_contor is divisible by 2 and in the hardest difficulty, the enemy will move every turn.  

Then, the function logic() is called. This function tests if the player’s character touches the walls of the map, the traps or the enemy. In this case, the variable gameOver will be set to 1, resulting in the end of the loop. Also, in this case, this function will ask the user to press a certain key if he wants to play again. If this key is pressed, the variable keepPlaying will be set to 1. If the player’s character touches the treasure, a message will be printed on the screen and the game will end. 

The next function called in this loop is the function control(), which is used to change the player’s character coordinates, by registering the keyboard presses and using a switch statement to determine which coordinate will be changed, when one of the WASD keys is pressed.

The last instruction in this while loop is the incrementation of the enemy_contor variable.

