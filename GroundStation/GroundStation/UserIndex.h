#pragma once

#include <fstream>
#include <iostream>

#include <vector>
#include <stdlib.h>

#include "Interface.h"


#define REDDIT_USERNAME_MAX_LENGTH 20
#define REDDIT_PASSWORD_MAX_LENGTH 16

#define USERDATA_MAX_LENGTH 36

#define USERDATA_FORMAT_INDEX_NUMBER 0
#define USERDATA_FORMAT_USERNAME 1
#define USERDATA_FORMAT_PASSWORD 2
#define USERDATA_FORMAT_EXIST 3
#define USERDATA_FORMAT_N_ELEMENTS 4


typedef struct{
	int index_number;
	char username[REDDIT_USERNAME_MAX_LENGTH];
	char password[REDDIT_PASSWORD_MAX_LENGTH];
	bool exist = false;
} UserData;



class UserIndex {
private:
	const char* IndexFilename;
	int IndexUsersQuantity;
	std::ifstream IndexFile;

	std::vector<UserData> Index;


public:
	UserIndex(); // defines IndexFilename, creates the first Index entry and sets NextUser to 0
	~UserIndex();

	int OpenFile(const char* filename); 
	int LoadFile(); 
	int PeakFile(); // Prints first two values, a value in the middle of the vector and the two last elements (if the vector size is bigger than 5) else
	int CloseFile();

	int CloseIndex();

	int NumOfExsistingUsers() {
		return Index.size();
	}

	int RemoveExistingUsers(); // Extremly inefficent as it is using a vector
};