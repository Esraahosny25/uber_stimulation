#include "Town.h"
#include <fstream>
#include <algorithm>


AdjList::AdjList()
{
	ifstream Input;
	Input.open("E:\\input.txt");
	int TotalTowns;
	string TownName, ConnectedNodes, DriverName;
	int dist, NoOfDist, NoOfDrivers;
	vector < pair <string, int> >VectorTemp;
	vector <string> Driver;
	pair <string, int> TempPair;
	Input >> TotalTowns;
	for (int i = 0; i < TotalTowns; i++)
	{
		Input >> TownName;
		Input >> NoOfDist;
		for (int j = 0; j < NoOfDist; j++)
		{
			Input >> ConnectedNodes >> dist;
			TempPair.first = ConnectedNodes;
			TempPair.second = dist;
			VectorTemp.push_back(TempPair);
		}
		Input >> NoOfDrivers;
		for (int j = 0; j < NoOfDrivers; j++)
		{
			Input >> DriverName;
			Driver.push_back(DriverName);
		}

		Town temp;
		temp.Name = TownName;
		temp.DriverList = Driver;
		temp.Connected = VectorTemp;
		Graph[TownName] = temp;
		VectorTemp.clear();
		Driver.clear();
	}

}


AdjList::~AdjList()
{
	//Saving to file
	ofstream Output;
	Output.open("C:\\Users\\marye\\Desktop\\Uber\\Output.txt");
	Output << Graph.size() << endl;
	unordered_map <string, Town> ::iterator it;
	for (it = Graph.begin(); it != Graph.end(); it++)
	{
		Output << (*it).first << endl;
		Output << (*it).second.Connected.size() << endl;
		for (int j = 0; j < (*it).second.Connected.size(); j++)
		{
			Output << (*it).second.Connected[j].first << endl;
			Output << (*it).second.Connected[j].second << endl;
		}
		Output << (*it).second.DriverList.size() << endl;
		for (int j = 0; j < (*it).second.DriverList.size(); j++)
		{
			Output << (*it).second.DriverList[j] << endl;
		}
	}
}


void AdjList::AddGraph(string TownName, vector<string> DriverList, vector<pair<string, int>>ConnectedNodes)
{
	Town temp;
	temp.Name = TownName;
	temp.DriverList = DriverList;
	temp.Connected = ConnectedNodes;
	Graph[TownName] = temp;
	for (int i = 0; i < temp.Connected.size(); i++)
	{


		pair<string, int> temp2;
		temp2.first = temp.Name;
		temp2.second = temp.Connected[i].second;
		Graph[temp.Connected[i].first].Connected.push_back(temp2);


	}
}

void AdjList::DeleteGraph(string Deleted)
{
	Graph.erase(Deleted);
	unordered_map <string, Town > ::iterator it;
	for (it = Graph.begin(); it != Graph.end(); it++)
	{
		for (int j = 0; j < (*it).second.Connected.size(); j++)
		{
			if ((*it).second.Connected[j].first == Deleted)
			{
				(*it).second.Connected.erase((*it).second.Connected.begin() + j);
				break;
			}
		}
	}
}

void AdjList::DisplayNodes()
{
	int i = 0;
	unordered_map <string, Town > ::iterator it;
	for (it = Graph.begin(); it != Graph.end(); it++)
	{
		cout << i + 1 << "." << (*it).first << endl;
		i++;
	}
}

void AdjList::Update() {
	cout << "What do you want to update" << endl;
	cout << "If you want to edit Distance press 1" << endl;
	cout << "If you want to update Name press 2" << endl;
	cout << "If you want to Delete connected node press 3" << endl;
	cout << "If you want to Add new connected node press 4" << endl;
	int choice = 0;
	cout << "enter your choice" << endl;
	cin >> choice;
	if (choice == 1) {
		string Town, connected; int dist;
		cout << "enter the name of the source town" << endl;
		cin >> Town;
		cout << "enter the name of the distenation town" << endl;
		cin >> connected;
		cout << "enter the new distance " << endl;
		cin >> dist;
		UpdateDistance(Town, connected, dist);
	}

	else if (choice == 2) {
		string Town, NewTown;
		cout << "enter the name of the source town" << endl;
		cin >> Town;
		cout << "enter the new Town name" << endl;
		cin >> NewTown;
		//	UpdateTownName(Town, NewTown);
	}
	else if (choice == 2) {
		string Town, connected;
		cout << "enter the name of the source town" << endl;
		cin >> Town;
		cout << "enter the new Town name" << endl;
		cin >> connected;
		DeleteEdge(Town, connected);
	}
	else {
		string Town, connected;
		cout << "enter the name of the source town" << endl;
		cin >> Town;
		cout << "enter the new Town name" << endl;
		cin >> connected;
		cout << "Enter the Distance";
		int dist;
		cin >> dist;
		AddNewEdge(Town, connected, dist);
	}
}

int AdjList::SearchInConnected(string Name, string Town)
{
	for (int i = 0; i < Graph[Town].Connected.size(); i++)
	{
		if (Graph[Town].Connected[i].first == Name)
			return i;
	}
}

void AdjList::UpdateDistance(string Node, string Connected, int dist) {
	int ConnectedNodeIndex = SearchInConnected(Connected, Node);
	Graph[Node].Connected[ConnectedNodeIndex].second = dist;
}
void AdjList::UpdateTownName(string TownName, string NewTown)
{
	Town temp = Graph[TownName];
	temp.Name = NewTown;
	Graph.erase(TownName);
	Graph[NewTown] = temp;
}

void AdjList::DeleteEdge(string Town, string Connected)
{
	int ConnectedNodeIndex = SearchInConnected(Connected, Town);
	Graph[Town].Connected.erase(Graph[Town].Connected.begin() + ConnectedNodeIndex);
	ConnectedNodeIndex = SearchInConnected(Town, Connected);
	Graph[Connected].Connected.erase(Graph[Connected].Connected.begin() + ConnectedNodeIndex);

}

void AdjList::AddNewEdge(string Town, string Connected, int dist)
{
	pair < string, int > temp;
	temp.first = Connected;
	temp.second = dist;
	Graph[Town].Connected.push_back(temp);
	temp.first = Town;
	Graph[Connected].Connected.push_back(temp);

}

void AdjList::AddDriverToNode(string DriverName, string TownName)
{
	Graph[TownName].DriverList.push_back(DriverName);
}

int inf = 9999;
Town AdjList::mini(map<string, int>dist, map<string, bool>visited)
{
	string min_node_name = "";
	int min_val = inf;
	unordered_map<string, Town>::iterator it;
	for (it = Graph.begin(); it != Graph.end(); ++it)
	{
		if (dist[it->first] != inf && visited[it->first] == false && dist[it->first] < min_val)
		{
			min_val = dist[it->first];
			min_node_name = it->first;
		}
	}return Graph[min_node_name];
}




int AdjList::FindTotalDistance(string location, string destination)
{
	int totaldist;
	Dijkestra(location, destination, totaldist);
	return totaldist;
}

vector<string >AdjList::FindPath(string location, string destination, map<string, string>prev)
{

	vector<string>path;
	path.push_back(destination);
	while (prev[destination] != location)
	{
		path.push_back(prev[destination]);
		destination = prev[destination];
	}
	path.push_back(location);
	return path;
}
void AdjList::Dijkestra(string src, string destination,
	int& totaldist)
{
	vector<string> path;
	map<string, string>prev;
	map<string, int>dist;
	map<string, bool>visited;

	unordered_map<string, Town>::iterator it;
	//seting distance to infinity
	for (it = Graph.begin(); it != Graph.end(); ++it)
	{
		dist[it->first] = inf;
	}
	//setting visited nodes to false
	for (it = Graph.begin(); it != Graph.end(); ++it)
	{
		visited[it->first] = false;
	}
	dist[src] = 0;
	
	Town min_node;
	for (int i = 0; i < Graph.size(); ++i)
	{
		min_node = mini(dist, visited);
		for (int j = 0; j < min_node.Connected.size(); ++j)
		{
			if (dist[min_node.Connected[j].first] > (dist[min_node.Name] + min_node.Connected[j].second))
			{
				dist[min_node.Connected[j].first] = dist[min_node.Name] + min_node.Connected[j].second;
				prev[min_node.Connected[j].first] = min_node.Name;
			}
		}
		visited[min_node.Name] = true;

	}totaldist = dist[destination];
	path = FindPath(src, destination, prev);
	showThePath(path);

}

void AdjList::Dijkestra(string src, map<string, int>& dist)
{

	map<string, bool>visited;


	unordered_map<string, Town>::iterator it;
	//seting distance to infinity
	for (it = Graph.begin(); it != Graph.end(); ++it)
	{
		dist[it->first] = inf;
	}
	//setting visited nodes to false
	for (it = Graph.begin(); it != Graph.end(); ++it)
	{
		visited[it->first] = false;
	}
	dist[src] = 0;
	Town min_node;
	for (int i = 0; i < Graph.size(); ++i)
	{
		min_node = mini(dist, visited);
		for (int j = 0; j < min_node.Connected.size(); ++j)
		{
			if (dist[min_node.Connected[j].first] > (dist[min_node.Name] + min_node.Connected[j].second))
			{
				dist[min_node.Connected[j].first] = dist[min_node.Name] + min_node.Connected[j].second;

			}
		}
		visited[min_node.Name] = true;

	}

}



/*void customer2::search_customer_info(string nam) {


	if (x.find(nam) != x.end())
		cout << x[nam];

	else {
		cout << "the name not found";
	}

}*/



void customer2::addinformation() {
	string name;
	string phone;


	cout << "enter the name";  getline(cin, name);

	cout << "enter phone";
	cin.ignore(); getline(cin, phone);
	x.insert(make_pair(name, phone));

}






customer2::customer2()
{
	string name;
	string phone;
	ifstream myfile;
	myfile.open("customer2.txt");
	if (myfile.is_open()) {
		for (int i = 0; i < x.size(); i++) {

			getline(myfile, name);
			getline(myfile, phone);
			x.insert(make_pair(name, phone));

		}
	}
	myfile.close();
}





customer2::~customer2()
{
	unordered_map< string, string>::iterator it;

	ofstream myfile;
	myfile.open("customer2.txt", ios::app);
	if (myfile.is_open()) {
		myfile << x.size() << '\n';
		it = x.begin();
		while (it != x.end()) {
			myfile << it->first << '\n' << it->second << '\n';
			it++;
		}cout << " THANK YOU, enjoy your trip " << endl;;
	}
	else {
		cout << "error in saving data **" << endl;
	}
	myfile.close();
}
void customer2::login()
{

	string name;
	while (1)
	{
		cout << "Enter The User Name";
		cin >> name;
		if (x.find(name) != x.end())
		{
			locat_dest();
			//Driver
		}
		else {
			cout << "please register first " << endl;
		}
	}
}

void customer2::locat_dest() {
	int back;
	int locatnum, destnum;
	string locat, dest;
	cout << " please enter the town of your current location:" << endl;
	DisplayNodes();
	cin >> locatnum;
	unordered_map <string, Town> ::iterator it = Graph.begin();
	for (int i = 1; i < locatnum; i++) {
		it++;
		}
	locat = it->first;
	cout << "where do you want to go:" << endl;
	DisplayNodes();
	cin >> destnum;
	it = Graph.begin();
	for (int i = 1; i < destnum; i++) {
		it++;
	}
	dest = it->first;
	assign_driver(locat, dest);
	back = FindTotalDistance(locat, dest);
	cout << "Total Distance from you location to destination is " << back<<endl;
	


}




Driver::Driver()
{


}


Driver::~Driver()
{
}
Town::Town() {

}

Town::~Town()
{
}

MapOfDrivers::MapOfDrivers() {
}

MapOfDrivers::~MapOfDrivers()
{
}

bool sortByVal(const pair<string, int>& a,
	const pair<string, int>& b)
{
	return (a.second < b.second);
}

void MapOfDrivers::Get_Data() {
	ifstream driver_file;
	driver_file.open("Driver.txt");
	Driver d;

	while (!driver_file.eof()) {
		driver_file >> d.name;

		driver_file >> d.phone_number;

		driver_file >> d.car_name;

		driver_file >> d.car_licence;

		driver_file >> d.car_colour;

		driver_file >> d.preferred_destination;

		Drivers[d.name] = d;
	}
}
void MapOfDrivers::assign_driver(string pickup_location, string destination) {
	map <string, int> dist;
	map <string, int>::iterator it = dist.begin();
	vector<pair<string, int>> vec_dist;
	map<string, int> ::iterator it2;
	for (it2 = dist.begin(); it2 != dist.end(); it2++)
	{
		vec_dist.push_back(make_pair(it2->first, it2->second));
	}
	sort(vec_dist.begin(), vec_dist.end(), sortByVal);
	Town TheTown;
	Driver TheDriver;
	for (int i = 0; i < vec_dist.size(); i++) {
		TheTown = Graph[vec_dist[i].first];

		for (int j = 0; j < TheTown.DriverList.size(); j++) {
			TheDriver = Drivers[TheTown.DriverList[j]];
			if (TheDriver.preferred_destination == destination) {
				show_driverInfo(TheDriver, TheTown);
				return;
			}
		}
	}
}
void MapOfDrivers::show_driverInfo(Driver TheDriver,Town TheTown) {
	cout << "Driver " << TheDriver.name <<"will come and pick you he is in "<<TheTown.Name <<" now" << endl;
	cout << " Car is " << TheDriver.car_colour<<"with number "<< TheDriver.car_licence << endl;
	cout << "The Driver's phone number is " << TheDriver.phone_number << endl;
	

}
void AdjList::showThePath(vector<string>v) {
	cout << "the path to your destination is : " << endl;
	for (int i = v.size()-1; i >=0 ; i--){
		cout<< v[i] << " ";
	}
	cout << endl;
}