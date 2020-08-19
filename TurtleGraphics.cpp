//Implementation file for Assign6 class
// Gergely Sajdik A00976672 1.0

#include "TurtleGraphics.h"
#include <array>
#include <iostream>
using namespace std;

//method to display the floor onto the screen
void TurtleGraphics::displayFloor() const {
	for (auto &rows : m_Floor) {
		for (auto &floorSpotDrawn : rows) {
			if (floorSpotDrawn == true) {
				cout << "*";
			}
			else {
				cout << " ";
			}
		}
	}
}

//method to set up the floor to all blanks/false
TurtleGraphics::TurtleGraphics(void) {
	for (auto &rows : m_Floor) {
		for (auto &floorSpotDrawn : rows) {
			floorSpotDrawn = false;
		}
	}
}

void TurtleGraphics::processTurtleMoves(const array<int, ARRAY_SIZE> & cmds) {
	
	//all members to be used
	Directions facingDirection = STARTING_DIRECTION;
	Cmds cmdsEnum = Cmds::PEN_UP;
	int row = STARTING_ROW;
	int column = STARTING_COL;
	bool pen = STARTING_PEN_POSITION;
	int cmdsPosition = 0;
	bool endProgram = false;

		while (endProgram == false) {

			//switch statement to check the enum with casting the integer obtained from the command array
			switch (static_cast<Cmds>(cmds[cmdsPosition])) {

			//raises the pen from the table
			case Cmds::PEN_UP:
				pen = false;
				break;

			//puts the pen onto the table
			case Cmds::PEN_DWN:
				pen = true;
				break;

			//changes the direction the turtle is facing
			case Cmds::TURN_RIGHT:
				switch (facingDirection) {
				case Directions::NORTH:
					facingDirection = Directions::EAST;
					break;
				case Directions::EAST:
					facingDirection = Directions::SOUTH;
					break;
				case Directions::SOUTH:
					facingDirection = Directions::WEST;
					break;
				case Directions::WEST:
					facingDirection = Directions::NORTH;
					break;
				}
				break;

			//changes the direction the turtle is facing
			case Cmds::TURN_LEFT:
				switch (facingDirection) {
				case Directions::NORTH:
					facingDirection = Directions::WEST;
					break;
				case Directions::EAST:
					facingDirection = Directions::NORTH;
					break;
				case Directions::SOUTH:
					facingDirection = Directions::EAST;
					break;
				case Directions::WEST:
					facingDirection = Directions::SOUTH;
					break;
				}
				break;
			
			//moves the turtle the correct amount of spots and checks for out of bounds
			case Cmds::MOVE:
				cmdsPosition++;
				if (cmds[cmdsPosition] > 0) {
					switch (facingDirection) {
					case Directions::NORTH:
						for (int i = 0; i < cmds[cmdsPosition] && row > 0; --row, i++){
							if (pen == true) {
								m_Floor.at(row).at(column) = true;
							}
						}
						break;
					case Directions::EAST:
						for (int i = 0; i < cmds[cmdsPosition] && column < (NCOLS - 1); ++column, i++) {
							if (pen == true) {
								m_Floor.at(row).at(column) = true;
							}
						}
						break;
					case Directions::SOUTH:
						for (int i = 0; i < cmds[cmdsPosition] && row < (NROWS - 1); ++row, i++)
							if (pen == true) {
								m_Floor.at(row).at(column) = true;
							}
						break;
					case Directions::WEST:
						for (int i = 0; i < cmds[cmdsPosition] && column > 0; --column, i++) {
							if (pen == true) {
								m_Floor.at(row).at(column) = true;
							}
						}
						break;
						
					}
				}
				break;

			//displays the turtles work on the screen
			case Cmds::DISPLAY:
				displayFloor();
				break;

			//if there is a 9 with no 5 before it then the loop will stop
			case Cmds::END_OF_DATA:
				endProgram = true;
				break;

			//standard default
			default:
				break;
			}

		//get ready for next spot in array
		cmdsPosition++;
	}
}

