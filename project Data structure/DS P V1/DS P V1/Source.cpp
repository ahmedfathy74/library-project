#include<iostream>
#include<unordered_map>
#include<string>
#include"Friend.h"
#include<fstream>

using namespace std;


void addFriend(unordered_map<int, Friend> &allUsers, int UserID)
{
	string namee;
	int id;
	cout << "Please enter the name and ID of the friend" << endl;
	cout << "Name :";
	cin >> namee;
	cout << "ID :";
	cin >> id;
	unordered_map<int, Friend>::iterator it;
	it = allUsers.find(UserID);
	it->second.flist[id] = namee;
	cout << "* You have added a new friend successfully! * \n" << endl;

}


void deleteFriend(unordered_map<int, Friend> &allUsers, int UserID)
{
	int id;
	cout << "Please enter the ID of the friend you want to delete : ";
	cin >> id;
	unordered_map<int, Friend>::iterator it;
	it = allUsers.find(UserID);
	unordered_map<int, string>::iterator it2;
	it2 = it->second.flist.find(id);
	if (it2 == it->second.flist.end())
	{
		cout << "You don't have this friend! \n" << endl;
	}
	else
	{
		it->second.flist.erase(it2);
		cout << "**You have deleted a friend!** \n" << endl;
	}

}



void displayInterests(unordered_map<int, Friend> allUser)
{
	cout << "Please enter the id of the friend : ";
	int id;
	cin >> id;
	unordered_map<int, Friend>::iterator it;
	it = allUser.find(id);
	if (it == allUser.end())
	{
		cout << "Wrong ID! \n" << endl;
	}
	else
	{
		for (int i = 0; i < it->second.ilist.size(); i++)
		{

			cout << it->second.ilist[i] << endl;
		}
		cout << endl;
	}

}

void search(unordered_map<int, Friend> allUsers, int UserID)
{
	int ch;
	vector<string>vec, vec2;
	cout << "Press 1 to search by name \nPress 2 to search by certain interest \nPress 3 to search by common friend \nPress 4 to search for users that are not your friends \n";
	cin >> ch;
	int x = 0;

	unordered_map<int, Friend>::iterator it;
	it = allUsers.find(UserID);

	if (ch == 4)
	{
		/*unordered_map<int, string>::iterator it2;
		for (it2 = it->second.flist.begin(); it2 != it->second.flist.end(); it2++)
		{
		vec.push_back(it2->second);
		}
		unordered_map<int, Friend>::iterator it3;
		for (it3 = allUsers.begin(); it3 != allUsers.end(); it3++)
		for (int i = 0; i < vec.size(); i++)
		if (it3->second.name != vec[i])
		cout << it3->second.name << endl;*/

		unordered_map<int, Friend>::iterator it3;
		unordered_map<int, string>::iterator it2;
		for (it3 = allUsers.begin(); it3 != allUsers.end(); it3++){
			vec.push_back(it3->second.name);
		}
		for (it2 = it->second.flist.begin(); it2 != it->second.flist.end(); it2++){
			for (int i = 0; i < vec.size(); i++){
				if (it2->second == vec[i]){
					vec.erase(vec.begin() + i);

				}
				if (it->second.name == vec[i]){
					vec.erase(vec.begin() + i);
				}
			}
		}
		for (int i = 0; i < vec.size(); i++)
		{ 
			cout << vec[i] << endl;
		}
	}
}

void showMyList(unordered_map<int, Friend> allUsers, int UserID)
{
	cout << "*Your list*" << endl;
	cout << "Name" << "   -->   " << "ID" << endl;

	unordered_map<int, Friend>::iterator it;
	it = allUsers.find(UserID);

	unordered_map<int, string>::iterator it2;
	for (it2 = it->second.flist.begin(); it2 != it->second.flist.end(); it2++)
	{
		cout << it2->second << "  -->  " << it2->first << endl;
	}
	cout << endl;
}



void showAll(unordered_map<int, Friend> allUsers)
{
	cout << "*All Users*" << endl;
	cout << "Name" << "   -->   " << "ID" << endl;
	unordered_map<int, Friend>::iterator it;
	for (it = allUsers.begin(); it != allUsers.end(); it++)
	{

		cout << it->second.name << "  -->  " << it->first << endl;
	}
	cout << endl;
}






int main()
{





	cout << "\n\n Welcome to Friends Manager! \n\n";

	unordered_map<int, Friend> allUsers;

	//Getting all the data from the file

	ifstream file;
	file.open("data.txt");



	while (!file.eof())
	{
		Friend f;
		string name;
		int id;
		file >> name >> id;
		f.name = name;

		int i = 0;
		while (true)
		{

			string interest;
			file >> interest;
			if (interest == ".")
			{
				break;
			}
			f.ilist.push_back(interest);
			i++;
		}

		i = 0;
		while (true)
		{

			string friends;
			int friendID;
			file >> friends;
			if (friends == ".")
			{
				break;
			}
			file >> friendID;
			f.flist[friendID] = friends;
			i++;
		}

		allUsers[id] = f;

	}

	cout << "Please enter your ID to log in : \nor Press '0' to create new account: ";
	int input;
	cin >> input;
	int UserID;

	if (input == 0)
	{
		cout << "Please enter your name and ID ";
		string name;
		int id;
		cin >> name;
		cin >> id;
		Friend f;
		f.name = name;
		cout << "Please enter your interests or press 0 to finish :";
		while (true)
		{
			string interest;
			cin >> interest;
			if (interest == "0")
			{
				break;
			}

			f.ilist.push_back(interest);

		}

		allUsers[id] = f;
		UserID = id;

	}

	else
	{
		UserID = input;
	}

	//starting the program and doing the operations which the user want

	while (true)
	{

		int operation;
		cout << "Press 1 to add new friend \nPress 2 to delete friend \nPress 3 to see friend's interests  \nPress 4 to search for friend \nPress 5 to see your list \nPress 6 to see all users \nPress 7 to exit " << endl;
		cin >> operation;

		if (operation == 1)
		{
			addFriend(allUsers, UserID);
		}

		else if (operation == 2)
		{
			deleteFriend(allUsers, UserID);
		}

		else if (operation == 3)
		{
			displayInterests(allUsers);
		}

		else if (operation == 4)
		{
			search(allUsers, UserID);
		}

		else if (operation == 5)
		{
			showMyList(allUsers, UserID);
		}

		else if (operation == 6)
		{
			showAll(allUsers);
		}

		else if (operation == 7)
		{
			break;
		}
		else { cout << "Please enter a valid number" << endl; }

	}


	//Updating the file after finishing all operations

	ofstream newfile;
	newfile.open("dataNew.txt");

	unordered_map<int, Friend>::iterator it;
	for (it = allUsers.begin(); it != allUsers.end(); it++)
	{
		if (it != allUsers.begin())
		{
			newfile << endl;
		}

		newfile << it->second.name << endl;
		newfile << it->first << endl;

		for (int i = 0; i < it->second.ilist.size(); i++)
		{
			newfile << it->second.ilist[i] << endl;
		}
		newfile << "." << endl;


		unordered_map<int, string>::iterator it2;
		for (it2 = it->second.flist.begin(); it2 != it->second.flist.end(); it2++)
		{
			newfile << it2->second << endl;
			newfile << it2->first << endl;

		}
		newfile << ".";


	}

	file.close();
	newfile.close();

	remove("data.txt");
	rename("dataNew.txt", "data.txt");


	return 0;
}