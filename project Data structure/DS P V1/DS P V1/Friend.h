#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>

using namespace std;

class Friend
{
	
public:

	string name;
	vector<string> ilist;
	unordered_map<int, string>flist;
	Friend();
	~Friend();
};

