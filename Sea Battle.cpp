#include <iostream>
#include <vector>
#include <time.h>
#include <windows.h>

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
	PLAYER,
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
//Клас координат для зберігання в вектор
class Coords
{
public:
	Coords(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	int getX() { return x; }
	int getY() { return y; }

private:
	int x;
	int y;
};

//Клас гравця
class Player : public User
{
public:
	int getScore() {
		return score;
	}
	void addScore(int score) {
		this->score += score;
	}
	int getSteps() {
		return steps;
	}
	void addStep(int step) {
		steps += step;
	}
private:
	int score = 0;
	int steps = 0;
};
//Клас комп'ютера
class Computer : public User
{
public:
	int getScore() {
		return score;
	}
	void addScore(int score) {
		this->score += score;
	}
	int getSteps() {
		return steps;
	}
	void addStep(int step) {
		steps += step;
	}
private:
	int score = 0;
	int steps = 0;
};

//Головний клас гри
class SeaBattle : public Game
{
public:
	SeaBattle();
	void initGame();
	void createMap();
	void repaint();
	void Step();
	void checkVinner();
	void showVinnerInfo(Player& pl);
	void showVinnerInfo(Computer& pc);
	void update();
	bool Contain(vector<Coords>& vec, int x, int y);
	~SeaBattle()
	{
		delete player;
		delete computer;
	}
private:
	enum Step step;
	Player* player;
	Computer* computer;
	//Координати кораблів
	vector<Coords> coordPlayer;
	vector<Coords> coordComputer;
	//Координати ходів
	vector<Coords> coordPlayerStep;
	vector<Coords> coordComputerStep;
};

SeaBattle::SeaBattle()
{
	//Ініціалізація гри
	initGame();
}
//Ініціалізація основних об'єктів гри для її запуску
void SeaBattle::initGame()
{
	step = PLAYER;
	player = new Player();
	computer = new Computer();
	createMap();
}
//Перевірка на вмістимість координат в векторі
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
//Генерація кораблів для обох сторін
void SeaBattle::createMap()
{
	//Генеруємо кораблі гравця
	for (size_t i = 0; i < SHIPS; i++)
	{
		for (size_t i = 0; i < SHIPS_LENGTH; i++)
		{
			int temp_x = rand() % WIDTH, 
				temp_y = rand() % HEIGHT;
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
			coordPlayer.push_back(Coords(temp_x, temp_y));
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
			coordComputer.push_back(Coords(temp_x, temp_y));
		}
	}
}
//Малюємо карту, метод викликається постійно
void SeaBattle::repaint()
{
	system("cls");
	cout << "Score: " << player->getScore() << "\t" << "  Score: " << computer->getScore() << endl;
	//Малюємо верхню частину карти
	cout << "yx";
	for (size_t i = 0; i < WIDTH; i++)
		cout << i;
	cout << "      yx";
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
				if (!Contain(coordComputerStep, j, i))
					cout << "*";
				else
					cout << "x";
			}
			else if (Contain(coordComputerStep, j, i))
				cout << "o";
			else
				cout << " ";
		}

		cout << "|     ";
		cout << i << "|";

		for (size_t j = 0; j < WIDTH; j++)
		{
			if (Contain(coordComputer, j, i)) {
				if (!Contain(coordPlayerStep, j, i))
					cout << " ";
				else
					cout << "x";
			}
			else if (Contain(coordPlayerStep, j, i))
				cout << "o";
			else
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
//Робимо хід в залежності від значення змінної step
void SeaBattle::Step()
{
	if (step == PLAYER) {
		int temp_X;
		int temp_Y;
		cout << "Ваш хід..." << endl;
		//cout << coordComputer[0].getX() << " " << coordComputer[0].getY() << endl;

		do {
			cout << ">x = "; cin >> temp_X;
			cout << "\n>y = "; cin >> temp_Y;

			if (Contain(coordPlayerStep, temp_X, temp_Y))
				cout << "Помилка, ви робили даний хід" << endl;
			else if (temp_X >= WIDTH || temp_Y >= HEIGHT)
				cout << "Помилкові координати" << endl;

		} while (temp_X >= WIDTH || temp_Y >= HEIGHT || Contain(coordPlayerStep, temp_X, temp_Y));

		if (Contain(coordComputer, temp_X, temp_Y)) {
			player->addScore(5);
			Sleep(200);
			Beep(800, 200);
		}
		else {
			Sleep(200);
			Beep(200, 300);
		}

		player->addStep(1);
		coordPlayerStep.push_back(Coords(temp_X, temp_Y));
		step = COMPUTER;
	}
	else {
		cout << "Хід комп'ютера..." << endl;
		Sleep(250);
		int temp_x = rand() % WIDTH, 
			temp_y = rand() % HEIGHT;

		while (Contain(coordComputerStep, temp_x, temp_y))
		{
			temp_x = rand() % WIDTH;
			temp_y = rand() % HEIGHT;
		}

		if (Contain(coordPlayer, temp_x, temp_y)) {
			computer->addScore(5);
			Sleep(200);
			Beep(800, 200);
		}
		else {
			Sleep(200);
			Beep(200, 300);
		}

		computer->addStep(1);
		coordComputerStep.push_back(Coords(temp_x, temp_y));
		step = PLAYER;
	}
}
//Виведення інформації про переможця (гравця)
void SeaBattle::showVinnerInfo(Player& pl)
{
	system("cls");
	cout << "Вітаю з перемогою!" << endl;
	cout << "Рахунок: " << player->getScore() << endl;
	cout << "Кількість ваших ходів: " << player->getSteps() << endl;
	cout << "Кількість ходів комп'ютера: " << computer->getSteps() << endl;
}
//Виведення інформації про переможця (комп'ютера)
void SeaBattle::showVinnerInfo(Computer& pc)
{
	system("cls");
	cout << "Поразка :(" << endl;
	cout << "-Наступного разу пощастить!-" << endl;
	cout << "Рахунок комп'ютера: " << computer->getScore() << endl;
	cout << "Кількість ходів комп'ютера: " << computer->getSteps() << endl;
	cout << "Кількість ваших ходів: " << player->getSteps() << endl;
}
//Перевірка переможця, якщо одна з сторін набрала потрібну кількість балів, 
//встановлюється значення змінної inGame = ture і виводиться інформація про переможця
void SeaBattle::checkVinner()
{
	if (player->getScore() >= SHIPS * SHIPS_LENGTH * 5) {
		inGame = false;
		showVinnerInfo(*player);
	}
	else if (computer->getScore() >= SHIPS * SHIPS_LENGTH * 5) {
		inGame = false;
		showVinnerInfo(*computer);
	}
}
//Метод постійно обновляє гру поки вона активна
void SeaBattle::update()
{
	checkVinner();
	if (inGame) {
		repaint();
		Step();
	}
}



int main()
{
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	SeaBattle game;
	while (inGame) {
		game.update();
	}

}
