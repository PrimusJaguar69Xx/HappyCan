#include "UserIndex.h"

UserIndex::UserIndex() {
	IndexFilename = nullptr;
	Index.emplace_back();
}


// defines IndexFilename, creates the first Index entry and sets NextUser to 0

int UserIndex::OpenFile(const char* filename) {
	IndexFilename = filename;

	IndexFile.open(filename, std::fstream::in);
	if (!IndexFile.good() || !IndexFile) {
		if (IndexFile.fail())
			return ERROR_FILE_OPEN_FAIL;
		else if (IndexFile.eof())
			return ERROR_FILE_OPEN_EOF;
		else
			return ERROR_FILE_OPEN;
	}
	return SUCCESS;
}

// Loads all elements found in the open 

int UserIndex::LoadFile() {


	//Checks too see if the file is ready to be read
	if (!IndexFile.is_open()) {
		return ERROR_FILE_NOT_OPEN;
	}
	else if (!IndexFile.good()) {
		return ERROR_FILE_NOT_GOOD;
	}
	else if (IndexFile.eof()) {
		return ERROR_FILE_OPEN_EOF;
	}



	// Gets the amount of users in the file
	char tempIndexUsersQuantity[USERDATA_MAX_LENGTH];
	IndexFile.getline(tempIndexUsersQuantity, USERDATA_MAX_LENGTH, '\n');
	IndexUsersQuantity = atoi(tempIndexUsersQuantity);

	if (Index.size() < 1) {
		Index.emplace_back();
	}

	for (int nCounter = 0; nCounter < IndexUsersQuantity; nCounter++) {
		if (IndexFile.eof()) 
			break;

		// Sorts the different parameters in to their respective slots
		for (int i = 0; i < USERDATA_FORMAT_N_ELEMENTS; i++) {
			switch (i) {

			case USERDATA_FORMAT_INDEX_NUMBER:

				char temp_1[USERDATA_MAX_LENGTH];
				IndexFile.getline(temp_1, USERDATA_MAX_LENGTH, '|');
				Index.at(nCounter).index_number = atoi(temp_1);

				break;

			case USERDATA_FORMAT_USERNAME:

				IndexFile.getline(Index.at(nCounter).username, REDDIT_USERNAME_MAX_LENGTH, '|');

				break;

			case USERDATA_FORMAT_PASSWORD:

				IndexFile.getline(Index.at(nCounter).password, REDDIT_PASSWORD_MAX_LENGTH, '|');

				break;

			case USERDATA_FORMAT_EXIST:

				char temp_2[USERDATA_MAX_LENGTH];
				IndexFile.getline(temp_2, USERDATA_MAX_LENGTH, '\n');
				Index.at(nCounter).exist = atoi(temp_2);

				break;

			default:
				// Would only get to this point if the amount of elements in UserData and the amount of cases dont line up...
				Print("retarded programmer...");

				break;
			}
		}

		if (IndexFile.eof())
			break;

		Index.emplace_back();
	}


	if (!IndexFile.good() || !IndexFile) {
		if (IndexFile.fail())
			return ERROR_FILE_OPEN_FAIL;
		else if (IndexFile.eof())
			return SUCCESS;
		else
			return ERROR_FILE_OPEN;
	}
	return SUCCESS;
}

int UserIndex::CloseFile() {
	if (!IndexFile.is_open()) {
		return ERROR_FILE_NOT_OPEN;
	}
	
	IndexFile.close();

	if (IndexFile.fail()) {
		return ERROR_FILE_FAIL;
	}
	return SUCCESS;
}


int UserIndex::RemoveExistingUsers() {
	if (Index.size() <= 0) {
		return ERROR_INDEX_EMPTY;
	}
	for (int i = Index.size() - 1; i >= 0; i--) {
		if (Index.at(i).exist == true) {
			Index.erase(Index.begin() + i);
		}
	}

	return SUCCESS;
}


int UserIndex::CloseIndex() {
	Index.~vector();
	return SUCCESS;
}

UserIndex::~UserIndex() {
	CloseFile();
	CloseIndex();
}