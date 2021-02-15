#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>
using namespace std;

class Town
{
public:
	string Name;
	vector <string>  DriverList;
	vector <pair < string, int >> Connected;
	Town();
	~Town();
};

class AdjList
{
public:
	unordered_map <string, Town> Graph;
	void AddGraph(string, vector <string>, vector<pair<string, int>>);
	void DeleteGraph(string);
	void DisplayNodes();
	void Update();
	int SearchInConnected(string Name, string Town);
	void UpdateDistance(string Town, string Connected, int NewDist);
	void UpdateTownName(string Town, string NewTown);
	void DeleteEdge(string Town, string Connected);
	void AddNewEdge(string Town, string Connected, int dist);
	void AddDriverToNode(string DriverName, string TownName);
	void Dijkestra(string src, string destination, int& totaldist);
	Town mini(map<string, int>dist, map<string, bool>visited);
	vector<string>FindPath(string src, string dest, map<string, string>prev);
	int FindTotalDistance(string location, string destination);
	void Dijkestra(string src, map<string, int>& dist);
	void showThePath(vector<string>);
	//void FloydWarshal(int);
	//void PrintSolusion(vector < vector<int>>dist);
	AdjList();
	~AdjList();
};

class Driver
{

public:

	string name;
	string phone_number;
	string car_name;
	string car_licence;
	string car_colour;
	string preferred_destination;

	Driver();
	~Driver();
};
class MapOfDrivers :public AdjList
{

public:
	unordered_map <string, Driver> Drivers;
	void Get_Data();
	void assign_driver(string pickup_location, string destination);
	void show_driverInfo(Driver,Town);
	
	MapOfDrivers();
	~MapOfDrivers();

};
class customer2 :public MapOfDrivers
{
public:
	unordered_map< string, string> x;
	customer2();
	~customer2();
	void login();
	void addinformation();
	void locat_dest();
	
	/*void print_one_cust(int index);
	void print_all_cust();*/
};
