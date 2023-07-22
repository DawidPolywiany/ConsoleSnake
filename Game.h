#ifndef GAME
#define GAME
#include <iostream>
using namespace std;

class Game {
public:
	//Game object class
	class GameObject {
	public:
		int positionX; //Object position x
		int positionY; //Object position y
		string objectName; //Object name
	};

	int screenSizeX; //Screen size x
	int screenSizeY; //Screen size y
	int maxObjectsCount; //Max count objects in allObjects list
	int lastObjectNumber = 0; //Game objects count in allObjects list
	GameObject* allObjects; //All game objects list
	int snakeWay = 0; //Where is the snake moving

	//This function start with program
	void Start() {
		srand(time(0)); //Random setting
		maxObjectsCount = screenSizeX * screenSizeY + 1; //Set max count number
		allObjects = new GameObject[maxObjectsCount]; //Create allObject list

		apple = Create(rand() % screenSizeX, rand() % screenSizeY, "Apple"); //Create apple
		snakeHead = Create(screenSizeX / 2, screenSizeY / 2, "SnakeHead"); //Create snake head
		for (int i = 1; i <= 5; i++) Create(snakeHead->positionX, snakeHead->positionY + i, "Snake"); //Create skenake body
	}

	//This function start every frame
	bool Update() {
		GameObject snakeEnd = allObjects[lastObjectNumber - 1];

		//Snake body move
		for (int i = lastObjectNumber - 1; i > 1; i--) {
			allObjects[i].positionX = allObjects[i - 1].positionX; //X
			allObjects[i].positionY = allObjects[i - 1].positionY; //Y
		}

		//Snake head move
		switch (snakeWay) {
		case 0: //Move up
			snakeHead->positionY--;
			break;
		case 1: //Move right
			snakeHead->positionX++;
			break;
		case 2: //Move down
			snakeHead->positionY++;
			break;
		case 3: //Move left
			snakeHead->positionX--;
			break;
		}

		//Teleport
		if (snakeHead->positionX < 0) snakeHead->positionX = screenSizeX - 1; //Vector x
		else if (snakeHead->positionX > screenSizeX - 1) snakeHead->positionX = 0;
		if (snakeHead->positionY < 0) snakeHead->positionY = screenSizeY - 1; //Vector y
		else if (snakeHead->positionY > screenSizeY - 1) snakeHead->positionY = 0;

		if (ReturnTouch(snakeHead)->objectName == "Apple") {
			//Set new position apple
			apple->positionX = rand() % screenSizeX;
			apple->positionY = rand() % screenSizeY;
			Create(snakeEnd.positionX, snakeEnd.positionY, "Snake"); //Create new snake body object
		}
		else if (ReturnTouch(snakeHead)->objectName == "Snake") return false; //Game over

		if (lastObjectNumber >= maxObjectsCount) return false; //If snake is very long

		return true; //Continue
	}
private:
	//Game variables
	GameObject* apple;
	GameObject *snakeHead;

	//Create new game object
	GameObject* Create(int positionX = 0, int positionY = 0, string objectName = "NoName") {
		GameObject gameObject; //Create new game object

		//Set game object variables
		gameObject.positionX = positionX;
		gameObject.positionY = positionY;
		gameObject.objectName = objectName;
		
		lastObjectNumber++; //Increase the number of objects
		allObjects[lastObjectNumber - 1] = gameObject; //Set new object in allObjects list
		return &allObjects[lastObjectNumber - 1]; //Return link on new object
	}

	//Return object that was touched
	GameObject* ReturnTouch(GameObject* gameObject) {
		for (int i = 0; i < lastObjectNumber; i++) {
			if (gameObject->objectName != allObjects[i].objectName) { //If object have different name
				//If object position equals target object position
				if (gameObject->positionX == allObjects[i].positionX && gameObject->positionY == allObjects[i].positionY) return &allObjects[i];
			}
		}
		return gameObject; //If object is not touched
	}
};

#endif
