#include <iostream>
#include <vector>

using namespace std;

//Константні значення 
const int HEIGHT = 10;
const int WIDTH = 10;
const int SHIPS = 5;
const int SHIPS_LENGTH = 3;
//Стан гри
bool inGame = true;
//Енумерація теперішнього ходу
enum Step
{
	PLAYER = 0,
	COMPUTER
};

//Абстрактний клас гри
class Game
{
public:
	virtual void initGame() = 0;
	virtual void createMap() = 0;
	virtual void repaint() = 0;
	virtual void update() = 0;
};
//Абстрактний клас гравців
class User
{
public:
	virtual int getScore() = 0;
};

//Головний клас гри
class SeaBattle : public Game
{
public:
	SeaBattle();
	void initGame();
	void createMap();
	void repaint();
	void update();
private:
	Step step;
	User* player;
	User* computer;
	User* vinner;
	//Координати кораблів
	vector<vector<int>> coordPlayer;
	vector<vector<int>> coordComputer;
	//Координати ходів
	vector<vector<int>> coordPlayerStep;
	vector<vector<int>> coordComputerStep;
};

SeaBattle::SeaBattle()
{
	//Ініціалізація гри
	initGame();
}

void SeaBattle::initGame()
{
	step = PLAYER;
	player = new Player();
	computer = new Computer();
	vinner = nullptr;
	cout << "Морський бій: " << endl;
	createMap();
}

void SeaBattle::createMap()
{
	for (size_t i = 0; i < WIDTH; i++)
		cout << "#";
	cout << "    ";
	for (size_t i = 0; i < WIDTH; i++)
		cout << "#";
}

class Player : public User
{
public:
	int getScore();

};

class Computer : public User
{
public:
	int getScore();
};




int main()
{
	SeaBattle game;
	while (inGame) {
		game.update();
	}

}
