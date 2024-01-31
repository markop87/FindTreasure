/*
    A small game of searching for treasure on the board.
    The player uses arrows and clues to find the treasure
    in as few moves as possible.
*/

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <random>
#include <fstream>
#include <cmath>

//key assignment
#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80

//function to generate a random number
int random_number(int range_bottom, int range_top)
{
    static std::mt19937 gen(time(nullptr)); // seed the generator
    std::uniform_int_distribution<> distr(range_bottom, range_top); //range

    return distr(gen);
}

int main()
{

    char play {'Y'}; // after the game player will be asked does he wants to play again

    while(play == 'Y' || play == 'y')
    {
        int x {11}, y {11}; //variable of the player position on game board
        int pos_x, pos_y {11}; //variable for treasure position on game board

        pos_x = random_number(1, 21); //generate treasure position on the x-axis

        // generate treasure position on the y-axis
        // If position on the x-axis is equal 11,
        // than position on the y axis can't be 11,
        // because (11, 11) is player's starting position.
        if(pos_x == 11)
        {
            while(pos_y == 11)
            {
                pos_y = random_number(1, 21);
            }
        }
        else pos_y = random_number(1, 21);

        int counter {0}; //variable to count player moves.

        //loading high score from text file to variable
        std::ifstream file;
        file.open("highscore.txt");

        int highscore;

        file >> highscore;


        while(x != pos_x || y != pos_y)
        {
            system("cls"); //cleaning screen

            std::cout << "== FIND THE TREASURE ==\n"; //title

            std::cout << "High score: " << highscore << "\n"; //displaying high score

            //displaying the game board
            for(int a = 0; a < 23; a++)
            {
                for(int b = 0; b < 23; b++)
                {
                    if(a == 0 || a == 22) // first and last row of the board
                    {
                        std::cout << "**";
                    }
                    else if(b == 0) // left border of the board
                    {
                        std::cout << "* ";
                    }
                    else if(b == 22) // right border of the board
                    {
                        std::cout << " *";
                    }
                    else if(a == y && b == x) // player's position
                    {
                        std::cout << " X";
                    }
                    else
                        std::cout << "  "; // empty spot
                }

                std::cout << "\n";
            }

            std::cout << "\nMoves: " << counter; // displaying number of player moves
            std::cout << "\nYour position (x, y): " << x << " " << y; // displaying player's current position


            // counting the distance between player and treasure
            double distance = sqrt(pow(x - pos_x, 2) + pow(y - pos_y, 2));
            double last_distance; // variable to save the distance for comparison

            // after first move, if distance is higher than in last move
            // player will get the information that player's moving away from treasure
            // otherwise he will be informed, that player is closer to treasure
            if(counter > 0)
            {
                if(distance > last_distance)
                {
                    std::cout << " - Colder!\n";
                }
                else std::cout << " - Warmer!\n";
            }

            last_distance = distance; // saving the distance for comparison in next move

            int key {0}; // variable to save pressed key

            while(key == 0)
            {
                key = getch();

                if (key && key != 224)
                {
                    //if player pressed wrong button, information will be shown
                    std::cout << "\nNot an arrow: You pressed " << (char) key << " button\n";
                    Sleep(1000);
                }
                else
                {

                    // switch statement for moving player marker
                    // on game board, when player press key
                    switch(key = getch())
                    {
                        case KEY_UP:
                        {
                            if(y != 1)
                            {
                                y--;
                            }
                            break;
                        }
                        case KEY_DOWN:
                        {
                            if(y != 21)
                            {
                                y++;
                            }
                            break;
                        }
                        case KEY_LEFT:
                        {
                            if(x != 1)
                            {
                                x--;
                            }
                            break;
                        }
                        case KEY_RIGHT:
                        {
                            if(x != 21)
                            {
                                x++;
                            }
                            break;
                        }
                    }
                }
            }

            counter++; // counting move
        }


        std::cout << "\n\nYOU WON in " << counter << " moves!\n\n"; //


        //If counter is lower than high score, then result will be saved to text file.
        if(counter < highscore)
        {
            std::cout << "New high score!\n\n";

            std::ofstream myfile;
            myfile.open ("highscore.txt");
            myfile << counter;
            myfile.close();
        }

        Sleep(1000); // 1 second break.

        //question about the next game
        std::cout << "Do you want to play again?\nInput Y or y to play or anything else to quit.\nYour choice: ";
        std::cin >> play;

    }
    return 0;
}
