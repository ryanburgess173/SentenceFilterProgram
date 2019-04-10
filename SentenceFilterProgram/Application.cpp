/*
	Johnathan R. Burgess, 3/24/2019
	Sentence Filter Project
*/
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

string GetData(string inputFile);
string MakeCorrections(string contents);
string WriteFilteredData(string outputFileName, string correctedData);

// just main
int main() {
	cout << "Hello! This is just a quick filter program that will remove capital" << endl
		<< "letters everywhere in a file except for the first letter of each sentence." << endl;
	cout << "Please enter the name of your input file: ";
	string inputFile;
	cin >> inputFile;

	string content = GetData(inputFile);

	string correctedContent = MakeCorrections(content);

	cout << "Now enter the name of your output file where you would like the newly" << endl
		<< "filtered data to be placed: ";
	string outputFile;
	cin >> outputFile;

	string resultMessage = WriteFilteredData(outputFile, correctedContent);

	cout << resultMessage << endl;
	
	system("pause");
	return 0;
}

// this function gets our data and returns it as a giant string from the file.
string GetData(string inputFile){
	fstream file;
	file.open(inputFile, ios::in);
	string fileContents;

	// tests to see if the file.open fails
	if (file.fail()) {
		cout << "The input file specified does not exist." << endl;
	}

	string input;
	while (file >> input) {
		fileContents += input;
		fileContents += " ";
	}
	file.close();
	return fileContents;
}

// This function of our application will fix capital letters and lowercase letters.
string MakeCorrections(string contents) {
	string correctedContents = contents;
	for (int i = 0; i < correctedContents.size(); i++) {
		if (correctedContents[i] == '.') {
			correctedContents[i + 2] = toupper(correctedContents[i + 2]);
		}
		else if (correctedContents[i] == ' ') {
			if (correctedContents[i - 1] != '.') {
				correctedContents[i + 1] = tolower(correctedContents[i + 1]);
			}
		}
	}
	correctedContents[0] = toupper(correctedContents[0]);

	// this piece will just add newline characters where appropriate :)
	int spaceCount = 0;
	for (int i = 0; i < correctedContents.size(); i++) {
		if (correctedContents[i] == ' ') {
			spaceCount++;
		}
		if (spaceCount >= 8) {
			correctedContents.insert(i, "\n");
			spaceCount = 0;
		}
	}

	return correctedContents;
}

// this function will write the newly filtered data to a new file
string WriteFilteredData(string outputFileName, string correctedData){

	// open the file for writing
	fstream file;
	file.open(outputFileName, ios::out);

	// this being "true" wouldn't make much sense but here it is anyways
	if (file.fail()) {
		return "\nFile could not be written to.\n";
	}

	file << correctedData;

	file.close();

	return "\nSuccess. File Created.\n";
}
