#include <iostream>
#include <fstream>
#include "game.h"
#include "human.h"
#include "bot.h"
#include <limits>

using namespace std;

void Game::choosePlayer()
{
  int choice;
  bool validChoice = false;

  while (!validChoice)
  {
    cout << "Choose your player:" << endl;
    cout << "1. Human" << endl;
    cout << "2. Bot" << endl;

    if (cin >> choice)
    {
      if (choice == 1)
      {
        humanGameplay();
        validChoice = true;
      }
      else if (choice == 2)
      {
        botGameplay();
        validChoice = true;
      }
      else
      {
        cout << "Invalid choice. Please try again." << endl;
      }
    }
    else
    {
      cout << "Invalid choice. Please try again." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
}

void Game::newGame()
{
  cout << "Starting new game..." << endl;
  choosePlayer();
}

void Game::loadGame()
{
  cout << "Loading game..." << endl;
  try
  {
    ifstream file("savedGame.txt");

    if (!file.is_open())
    {
      throw runtime_error("Error opening file");
    }

    // function to read the content of the file to the object
  }
  catch (const exception &e)
  {
    cout << "An error ocurred: " << e.what() << '\n';
  }
}

void Game::setHumanGameSettings(Human &player1, Human &Player2)
{
  pair<int, int> boardSize;
  string name;

  cout << "set the board size" << endl;
  cout << "Enter the number of rows: ";
  cin >> boardSize.first;
  cout << "Enter the number of columns: ";
  cin >> boardSize.second;

  player1.setBoard();
  Player2.setBoard();

  player1.getBoard().setSize(boardSize);
  Player2.getBoard().setSize(boardSize);

  // set names

  cout << "Enter player 1 name: ";
  cin >> name;
  player1.setName(name);

  cout << "Enter player 2 name: ";
  cin >> name;
  Player2.setName(name);

  // set ships

  vector<WarShip> _ships;

  _ships.push_back(WarShip(4, 'A'));

  _ships.push_back(WarShip(3, 'B'));
  _ships.push_back(WarShip(3, 'B'));

  _ships.push_back(WarShip(2, 'C'));
  _ships.push_back(WarShip(2, 'C'));
  _ships.push_back(WarShip(2, 'C'));

  _ships.push_back(WarShip(1, 'D'));
  _ships.push_back(WarShip(1, 'D'));
  _ships.push_back(WarShip(1, 'D'));
  _ships.push_back(WarShip(1, 'D'));

  player1.setShips(_ships);
  Player2.setShips(_ships);

  // settear la orientacion de los barcos

  vector<WarShip> ships1 = player1.getShips();
  vector<WarShip> ships2 = Player2.getShips();

  char orientation;

  for (WarShip &ship : ships1)
  {
    cout << player1.getName() << " enter the orientation of the ship " << ship.getSymbol() << endl;
    cout << "Enter the orientation (H for horizontal, V for vertical): ";
    cin >> orientation;

    ship.setOrientation(orientation);
    cout << "orientation: " << ship.getOrientation() << "\n";
  }

  for (WarShip &ship : ships2)
  {
    cout << Player2.getName() << " enter the orientation of the ship " << ship.getSymbol() << endl;
    cout << "Enter the orientation (H for horizontal, V for vertical): ";
    cin >> orientation;

    ship.setOrientation(orientation);
    cout << "orientation: " << ship.getOrientation() << "\n";
  }

  // set coordinates

  vector<pair<int, int>> coordinates;
  int row, col;

  for (WarShip &ship : ships1)
  {
    cout << player1.getName() << " enter the coordinates of the ship " << ship.getSymbol() << endl;

    for (int i = 0; i < ship.getSize(); i++)
    {
      cout << "Enter the row: ";
      cin >> row;
      cout << "Enter the column: ";
      cin >> col;

      coordinates.push_back(make_pair(row, col));
    }

    ship.setCoordinates(coordinates);
    coordinates.clear();
  }

  for (WarShip &ship : ships2)
  {
    cout << Player2.getName() << " enter the coordinates of the ship " << ship.getSymbol() << endl;
    cout << ship.getSymbol() << "'s orientation is: " << ship.getOrientation() << endl;

    for (int i = 0; i < ship.getSize(); i++)
    {
      cout << "Enter the row: ";
      cin >> row;
      cout << "Enter the column: ";
      cin >> col;

      coordinates.push_back(make_pair(row, col));
    }

    ship.setCoordinates(coordinates);
    coordinates.clear();
  }

  // set squares

  pair<int, int> size = player1.getBoard().getSize();

  player1.getBoard().setSquares({}, ships1, size);
  Player2.getBoard().setSquares({}, ships2, size);
}

void Game::setBotGameSettings(Human &player1, Bot &bot)
{
}

void Game::humanGameplay()
{
  Human player1;
  Human Player2;

  setHumanGameSettings(player1, Player2);

  // draw boards

  cout << player1.getName() << " board:" << endl;
  player1.getBoard().draw();
  cout << endl;

  cout << Player2.getName() << " board:" << endl;
  Player2.getBoard().draw();
  cout << endl;
}

void Game::botGameplay()
{
  Human player1;
  Bot bot;
  setBotGameSettings(player1, bot);
}