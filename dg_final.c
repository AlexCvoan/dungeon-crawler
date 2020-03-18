#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>

int map_x=10, map_y=20, trap_x, trap_y, player_x, player_y, enemy_x, enemy_y;   /* the coordinates of the player, trap and enemy */
char field[50][50], gm_choice[15], name[15];
int keepPlaying, gameOver, enemy_contor = 0, gameMode = 2, difficulty;

void script();   /* The initial setup of the program and the instructions. */
void traps();   /* The function which generates randomly the coordinates of the traps */
void enemy();    /* The basic AI which make the enemy follow the player */
void render();   /* The display function, which prints the game board with all of it's variables */
void control();  /* The function which detects key presses, in order to control the player's characters */
void logic();    /* The function which determines when the player will lose, or win the game. Also, this function allows the user to try again, if he fails. */


int main()
{
    script();
    	do {
            keepPlaying = 0;   /* Variable which determines if the game will start again, after the player loses. If the player will choose to play again, this variable will get the value 1, which fulfills the condition of the loop */
            gameOver = 0;    /* Variable which determines if the game is lost. ( the player's character falls over a trap or collide with the enemy, or the borders of the map.) */
            player_x = 1;
            player_y = 1;

            srand(time(NULL));
            int random = rand() % 100;  /* generating a random variable, which will be used as a seed for the current game session, in order to generate the traps */

            while((enemy_y<4)||(enemy_x>6)||(enemy_x<1)||(enemy_y<1)||((enemy_x==1)&&(enemy_y==1)))
           {
            enemy_x = rand() % (map_x-2);
            enemy_y = rand() % (map_y-2);
           }

            while (gameOver!=1)
            {
                srand(random);
                render();
                logic();
                control();
                enemy_contor++; /* this variable is used to set the difficulty in the enemy mode. */
            }

	} while (keepPlaying==1);

	return 0;
}

void script()
{
    char traps_option[] = "traps", enemies_option[] = "enemy";  /* strings used to test the user's choice in the script function */
    char gm_choice[15];

	printf("\n\n              Dungeon Crawler");
	printf("\n\n    Hello Adventurer! What is your name? ");

	gets(name);

	printf("\n  Okay, %s, now you should know what you have to do in order to get to the treasure marked with X on the map. \n  First of all, your character is noted with %c. You control your movement with WASD. \n  You have two options: have traps on the map or an enemy that follows you. What do you choose?   (traps/enemy)  ",name,153);
	while ((strcmp(gm_choice,traps_option)!=0) && (strcmp(gm_choice, enemies_option) != 0))   /* testing the response of the user and declining it if it's different than the two options given. */
	{
		gets(gm_choice);
		if ((strcmp(gm_choice,traps_option) != 0) && (strcmp(gm_choice, enemies_option) != 0))
			printf("\n   I'm afraid you have to choose between traps and enemy.  ");
	}

	if (strcmp(gm_choice, traps_option) == 0)		gameMode = 1;  /* comparing the user's response to the predefined strings in order to determine the game-mode */
	if (strcmp(gm_choice, enemies_option) == 0)		gameMode = 2;
	if (gameMode == 2)
	{
		printf("\n  We are almost ready to start. You have chosen to face %s. Now, choose the difficulty, from 1, being the easiest, to 3, being the hardest.  ", gm_choice);
		while ((difficulty < 1) || (difficulty > 3))
		{
			scanf("%d", &difficulty);
			if ((difficulty < 1) || (difficulty > 3))
				printf("\n   I'm afraid you have to choose from 1, being the easiest, to 3, being the hardest.  ");
		}
	}

	switch (difficulty) {  /* this variable switch is done in order to make it easier for the program to run at the given difficulty, in the enemy mode. more details in the enemy function */
	case 1: difficulty = 3;
		break;
	case 3: difficulty = 1;
		break;
	}

	printf("\n  We shall begin.   \n\n\n\n");

	Sleep(1000);
}

void traps()
{
    trap_x=0;
    trap_y=0;
    while((trap_x<2)||(trap_x>map_x-2))
		trap_x = rand() % (map_x-1);
    while((trap_y<2)||(trap_y>map_y-3))
		trap_y = rand() % (map_y-1);
}

void enemy()
{
        if(enemy_contor%4!=0)
            if (enemy_contor % difficulty == 0)  /* at each turn of the game, the enemy_contor will increase. In the easiest difficulty level, the enemy will move after every 3 moves of the player's character. The difficulty introduced by the user was 1 (the easiest) and was inversed to 3, so the condition will be true every 3 turns.*/
                if (player_x < enemy_x)		enemy_x--;         /* this four conditions test the position of the enemy and the player's character, in order to move the enemy towards the player. */
                else if (player_x > enemy_x)	enemy_x++;
                else if (player_y < enemy_y)	enemy_y--;
                else if (player_y > enemy_y)	enemy_y++;
}


void render()
{
    system("cls");
    int i,j;
    for(i=0;i<map_x;i++)
        for(j=0;j<map_y;j++)
            field[i][j]=176;
    for(i=1;i<map_x-1;i++)
        {
            field[i][0]=186;
            field[i][map_y-1]=186;
        }
    for(j=1;j<map_y-1;j++)
        {
            field[0][j]=205;
            field[map_x-1][j]=205;
        }
    field[map_x-1][0]=200;
    field[0][0]=201;
    field[0][map_y-1]=187;
    field[map_x-1][map_y-1]=188;

    field[map_x-2][map_y-2]='X';
    field[player_x][player_y]=153;

    if(gameMode==1)
        {
            for(i=0;i<20;i++)
            {
                traps();
                field[trap_x][trap_y]='T';
            }
        }
        else
        {
            enemy();
            field[enemy_x][enemy_y]='E';
        }

    printf("\n        Dungeon Crawler       \n\n\n     ");
    for(i=0;i<map_x;i++)
    {
        for(j=0;j<map_y;j++)
            printf("%c",field[i][j]);
        printf("\n     ");
    }
    printf("\n     Go get that treasure!\n\n    You can press Esc at any time to close the game.\n");

}

void control()
{
	char dir;

	if(gameOver!=1)
        dir = getch();

	switch (dir) {
	case 'd':
		player_y++;
		break;
	case 'a':
		player_y--;
		break;
	case 'w':
		player_x--;
		break;
	case 's':
		player_x++;
		break;
	case 27:
		gameOver = 1;
		break;
	default:
		break;
	}
}

void logic()
{
	if ((player_x == 0) || (player_x == map_x-1) || (player_y == 0) || (player_y == map_y-1) || ((field[player_x][player_y] == 'T')&&(gameMode==1))||(((player_x==enemy_x)&&(player_y==enemy_y))&&(gameMode==2)))
	{
		printf("\n                      Game Over\n\n   If you want to try again, press Enter. If not, press any other key...");

		if (getch() == 13) {
			gameOver = 1;
			keepPlaying = 1;
		}
		else
			gameOver = 1;
	}

	if ((player_x==map_x-2)&&(player_y==map_y-2))
	{


		printf("\n    Congratulations, %s, you won!",name);
		printf("\n  Press any key to exit...");
		getch();

		gameOver = 1;
	}
}
