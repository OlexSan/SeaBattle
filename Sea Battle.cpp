#include <iostream>
#include <vector>
#include <time.h>

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

class Coords
{
public:
	Coords(User* user):Coords(user, 0, 0) {}
	Coords(User* user, int x, int y)
	{
		this->user = user;
		this->x = x;
		this->y = y;
	}
	int getX() { return x; }
	int getY() { return y; }

private:
	int x;
	int y;
	User* user;
};


class Player : public User
{
public:
	int getScore();

};

int Player::getScore()
{
	return 0;
}

class Computer : public User
{
public:
	int getScore();
};

int Computer::getScore()
{
	return 0;
}

//Головний клас гри
class SeaBattle : public Game
{
public:
	SeaBattle();
	void initGame();
	void createMap();
	void repaint();
	void update();
	bool Contain(vector<Coords>& vec, int x, int y);
private:
	Step step;
	Player* player;
	Computer* computer;
	User* vinner;
	//Координати кораблів
	vector<Coords> coordPlayer;
	vector<Coords> coordComputer;
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
	createMap();
}

bool SeaBattle::Contain(vector<Coords>& vec, int x, int y)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i].getX() == x && vec[i].getY() == y) {
			return true;
		}
	}
	return false;
}


void SeaBattle::createMap()
{
	//Генеруємо кораблі гравця
	for (size_t i = 0; i < SHIPS; i++)
	{
		for (size_t i = 0; i < SHIPS_LENGTH; i++)
		{
			int temp_x = rand() % WIDTH, temp_y = rand() % HEIGHT;
			bool flag = true;
			while (flag)
			{
				flag = false;
				if (Contain(coordPlayer, temp_x, temp_y)) {
					temp_x = rand() % WIDTH;
					temp_y = rand() % HEIGHT;
					flag = true;
				}
			}
			coordPlayer.push_back(Coords(player, temp_x, temp_y));
		}
	}

	//Генеруємо кораблі комп'ютера
	for (size_t i = 0; i < SHIPS; i++)
	{
		for (size_t i = 0; i < SHIPS_LENGTH; i++)
		{
			int temp_x = rand() % WIDTH, temp_y = rand() % HEIGHT;
			bool flag = true;
			while (flag)
			{
				flag = false;
				if (Contain(coordComputer, temp_x, temp_y)) {
					temp_x = rand() % WIDTH;
					temp_y = rand() % HEIGHT;
					flag = true;
				}
			}
			coordComputer.push_back(Coords(player, temp_x, temp_y));
		}
	}
}

void SeaBattle::repaint()
{
	system("cls");
	cout << "Score: " << player->getScore() << "\t" << "  Score: " << computer->getScore() << endl;
	//Малюємо верхню частину карти
	cout << "  ";
	for (size_t i = 0; i < WIDTH; i++)
		cout << i;
	cout << "        ";
	for (size_t i = 0; i < WIDTH; i++)
		cout << i;
	cout << endl;

	//Малюємо основну частину карти
	for (size_t i = 0; i < HEIGHT; i++)
	{
		cout << i << "|";
		for (size_t j = 0; j < WIDTH; j++)
		{
			if (Contain(coordPlayer, j, i)) {
				cout << "$";
			}
			else
				cout << " ";
		}
		cout << "|     ";
		cout << i << "|";
		for (size_t j = 0; j < WIDTH; j++)
		{
			cout << " ";
		}
		cout << "|     ";
		cout << endl;
	}
	//Малюємо нижню частину карти
	cout << " ";
	for (size_t i = 0; i < WIDTH + 2; i++)
		cout << "#";
	cout << "      ";
	for (size_t i = 0; i < WIDTH + 2; i++)
		cout << "#";
	cout << endl;
}

void SeaBattle::update()
{
	repaint();
}



int main()
{
	srand(time(NULL));
	SeaBattle game;
	while (inGame) {
		game.update();
	}

}
