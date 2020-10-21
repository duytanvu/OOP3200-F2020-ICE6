/*
 * Duy Tan Vu - 100750366
 * OOP3200 - F2020 - ICE 06
 * Date: October 21st, 2020
 */

#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <cstdlib>

#include "GameObject.h"
#include "Vector3D.h"

int main()
{
	// A map contains pairs of key-value, key is a string and the value is a GameObject object
	std::map<std::string, GameObject*> gameObject;

	auto* ship = new GameObject("Ship", 0, 3.0f, 4.0f);
	auto* enemy = new GameObject("Enemy", 1, 10.0f, 20.0f);
	auto* space_station = new GameObject("SpaceStation", 2, 100.0f, 200.0f);

	gameObject[ship->GetName()] = ship;
	gameObject[enemy->GetName()] = enemy;
	gameObject[space_station->GetName()] = space_station;

	// Loop through all key-value pairs in gameObject and print them out
	for (const auto& game_object : gameObject)
	{
		std::cout << "Key  : " << game_object.first << std::endl;
		std::cout << "Value: \n" << game_object.second->ToString() << std::endl;
	}

	// Calculate and display the dinstance between ship and enemy
	auto distance = Vector2D<float>::Distance(gameObject["Ship"]->GetPosition(), gameObject["Enemy"]->GetPosition());
	std::cout << "Distance between " << gameObject["Ship"]->GetName() << " and " << gameObject["Ship"]->GetName() << " is " << std::to_string(distance) << "\n\n";

	// Start output to GameObject.txt file
	std::ofstream outfile("GameObject.txt", std::ios::out);

	outfile << gameObject["Ship"]->ToFile() << std::endl;
	outfile << gameObject["Enemy"]->ToFile() << std::endl;
	outfile << gameObject["SpaceStation"]->ToFile() << std::endl;
	outfile.close();	// Close the file after writing to it

	// Banner indicating end of output, and start input
	std::cout << "------------------------------\n"
		<< "END OF OUTPUT, START INPUT\n"
		<< "------------------------------\n\n";

	std::ifstream infile;
	std::string fileName = "GameObject.txt";

	if (infile.is_open())
	{
		int id;
		float x, y;
		std::string name;
		
		while (!infile.fail())
		{
			infile >> id >> name;
			infile.ignore(1, ' ');
			infile.ignore(1, '(');
			infile >> x;
			infile.ignore(1, ',');
			infile.ignore(1, ' ');
			infile >> y;
			infile.ignore(1, ')');
			//infile.ignore();

			auto* temp_object = new GameObject(name, id, x, y);

			gameObject[name + " 02"] = temp_object;
		}
		infile.close();
	}

	// Show all key-value pairs in game object using a loop
	for (const auto& game_object : gameObject)
	{
		std::cout << "Key  : " << game_object.first << std::endl;
		std::cout << game_object.second->ToString() << std::endl;
		std::cout << "Value: \n" << game_object.second->ToString() << std::endl;
	}

	std::cout << "------------------------------\n"
		<< "END OF INPUT\n"
		<< "------------------------------\n";
	
	return 0;
}

