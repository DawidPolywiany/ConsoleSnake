#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Game.h"
using namespace std;

//Screen size variables
int screenSizeX;
int screenSizeY;

Game game;
string defaultFrame; //Empty screen pictures

//Print all objects on screen
string PrintObjects(string frame) {
	for (int i = 0; i < game.lastObjectNumber; i++) {
		string pixelChar = "+"; //Pixel picture in frame
		if (game.allObjects[i].objectName == "Apple") pixelChar = "o";

		int pixelNumber; //Pixel number in frame
		pixelNumber = game.allObjects[i].positionX + game.allObjects[i].positionY * (screenSizeX + 1); //Set pixel number

		frame.replace(pixelNumber, 1, pixelChar); //Print game object
	}

	return frame; //Return frame
}

int main() {
	cout << "Enter your screen size" << "\n";
	cout << "X: "; cin >> screenSizeX; //Set screen size x
	cout << "Y: "; cin >> screenSizeY; //Set screen size y
	screenSizeX -= 1;
	screenSizeY -= 1;
	//Set screen size in game class
	game.screenSizeX = screenSizeX;
	game.screenSizeY = screenSizeY;
	if (screenSizeX < 10 || screenSizeY < 10) cout << "Error: minimum screen size: 10" << "\n"; //If screen size very small

	//Set default screen
	for (int i = 0; i < screenSizeY; i++) {
		for (int j = 0; j < screenSizeX; j++) defaultFrame += "_"; //Set one line
		defaultFrame += "\n"; //Set end line
	}

	game.Start(); //Start function

	//Output screen
	while (true) {
		//Get pressed key
		if (_kbhit()) {
			char key = _getch(); //Get pressed key
			switch (key) {
			case 'w': //Move up
				game.snakeWay = 0;
				break;
			case 'd': //Move right
				game.snakeWay = 1;
				break;
			case 's': //Move down
				game.snakeWay = 2;
				break;
			case 'a': //Move left
				game.snakeWay = 3;
				break;
			}
		}

		if (!game.Update()) break; //Start update function
		string newFrame = PrintObjects (defaultFrame); //Create new frame
		cout << "\n\n" << newFrame; //Output new frame
		Sleep(350); //Sleep on 0.35 seconds
	}

	return 0;
}
