// Description: This function reads data from a file for a number of basketball teams, sorts the basketball teams by College, by Mascot,
// 							and by Wins and writes the teams' data to an output file in the sorted orders. Then the function closes the files and
// 							deletes the heap memory.
// Filename: PROG3
// Names: Kierin Noreen & Cater Mooring
// Date: September 24, 2018
// Gonzaga University, CPSC 122, Dr. Yerion



#include <string>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

const int MAXSIZE = 5;
const int NUMTEAMS = 5;

struct BasketballTeam
{
	string college;
  string mascotName;
	int wins;
	int losses;
	double averagePointsPerGame;
};

// Description: This function opens an input file to read from
// Pre: The infile is not opened
// Post: The infile is opened and ready to be read from
void openInputFile(ifstream& infile);

// Description: This function opens an output file to print to
// Pre: The outfile is not opened
// Post: The outfile is opened and ready to be printed to
void openOutputFile(ofstream& outfile);

// Description: This function reads a teams data from a file and stores that data individually
// Pre: The infile is opened and the struct oneTeam is empty
// Post: The infile is read from and the data is stored in the struct oneTeam
void readBasketballTeam(ifstream& infile, BasketballTeam& oneTeam);

// Description: This file prints the read basketball information to an output file while also arranging it specifically.
// Pre: oneTeam has data stored in it and outfile is opened.
// Post: The read information has been printed to an output file.
void printBasketballTeam(BasketballTeam& oneTeam, ofstream& outfile);

// Description: This function reads in all of the data for all of the teams in the input file and stores all of the data individually
// Pre: The infile is opened, the array of structs teams[] is created, and numberOfTeams is created and empty
// Post: The infile has been read, the array of structs teams[] is filled to the numberOfTeams which was stored with
// 			 the number of teams read from the file
void readManyBasketballTeams(ifstream& infile, BasketballTeam teams[], int& numberOfTeams);

// Description: This function prints headers to the output file then calls the function to print the teams.
// Pre: The array of structs teams[] is able to be read, and the number of teams is known, and the output file has been opened.
// Post: The headers and basketball teams have been printed to the output file.
void printManyBasketballTeams(BasketballTeam teams[], int numberOfTeams, ofstream& outfile);

// Description: This function reads the data of multiple basketball teams and sorts the teams aplphabetically by the name
// 							of the college
// Pre: The array of structs teams holds all the data for each team and is not sorted and numberOfTeams holds the number of teams
// Post: The array of structs teams is sorted aplphabetically by the name of the college and the numberOfTeams is still the number of teams
void bubbleSortCollege(BasketballTeam*& teams, int numberOfTeams);

// Description: This function makes it possible for other functions to swap information contined in a read file.
// Pre: The teams array is created and able to be changed directly, int i has been passed through to be used again.
// Post: When called, this function will now be able to swap variables depending on what type of swap was wanted (letter, size, etc)
void swap(BasketballTeam*& teams, int i);

// Description:  This function reads the data of multiple basketball teams and sorts the teams aplphabetically by the type
// 							of the mascott
// Pre: The array of structs teams holds all the data for each team and is not sorted and numberOfTeams holds the number of teams
// Post: The array of structs teams is sorted aplphabetically by the type of the mascot and the numberOfTeams is still the number of teams
void bubbleSortMascot(BasketballTeam*& teams, int numberOfTeams);

// Description: This function reads the data of multiple basketball teams and sorts the teams by most number of wins
// Pre: The array of structs teams holds all the data for each team and is not sorted and numberOfTeams holds the number of teams
// Post: The array of structs teams is sorted by most wins and the numberOfTeams is still the number of teams
void bubbleSortWins(BasketballTeam*& teams, int numberOfTeams);

int main()
{
  int numberOfTeams;
	BasketballTeam oneTeam;
  BasketballTeam* teams;
  teams = new BasketballTeam[NUMTEAMS];

	ifstream infile;
  ofstream outfile;

	openInputFile(infile);
  openOutputFile(outfile);
	readManyBasketballTeams(infile, teams, numberOfTeams);
	bubbleSortCollege(teams, numberOfTeams);
	printManyBasketballTeams(teams, numberOfTeams, outfile);
	bubbleSortMascot(teams, numberOfTeams);
	printManyBasketballTeams(teams, numberOfTeams, outfile);
	bubbleSortWins(teams, numberOfTeams);
	printManyBasketballTeams(teams, numberOfTeams, outfile);
  infile.close();
  outfile.close();
  delete [] teams;

	return 0;
}

// Description: This function opens an input file to read from
// Pre: The infile is not opened
// Post: The infile is opened and ready to be read from
void openInputFile(ifstream& infile)
{
	infile.open("inteams.dat");
	if (infile.fail())
	{
		cout << "Error opening file named inteams.dat" << endl;
		exit(1); // the only time this is allowed
	}
}

// Description: This function opens an output file to print to
// Pre: The outfile is not opened
// Post: The outfile is opened and ready to be printed to
void openOutputFile(ofstream& outfile)
{
  outfile.open("outteams.dat");
  if (outfile.fail())
  {
    cout << "Error opening file name outteams.dat" << endl;
    exit(1); // the only time this is allowed
  }
}

// Description: This function reads a teams data from a file and stores that data individually
// Pre: The infile is opened and the struct oneTeam is empty
// Post: The infile is read from and the data is stored in the struct oneTeam
void readBasketballTeam(ifstream& infile, BasketballTeam& oneTeam)
{
	infile >> oneTeam.college;
  infile >> oneTeam.mascotName;
	infile >> oneTeam.wins;
	infile >> oneTeam.losses;
	infile >> oneTeam.averagePointsPerGame;
}

// Description: This file prints the read basketball information to an output file while also arranging it specifically.
// Pre: oneTeam has data stored in it and outfile is opened.
// Post: The read information has been printed to an output file.
void printBasketballTeam(BasketballTeam& oneTeam, ofstream& outfile)
{
  outfile << right << setw(5) << " ";
  outfile << left << setw(12) << oneTeam.college;
	outfile << left << setw(10) << oneTeam.mascotName;
	outfile << right << setw(8) << oneTeam.wins;
	outfile << right << setw(8) << oneTeam.losses;
	outfile << right << setw(8) << fixed << setprecision(1) << oneTeam.averagePointsPerGame;
  outfile << endl;
}

// Description: This function reads in all of the data for all of the teams in the input file and stores all of the data individually
// Pre: The infile is opened, the array of structs teams[] is created, and numberOfTeams is created and empty
// Post: The infile has been read, the array of structs teams[] is filled to the numberOfTeams which was stored with
// 			 the number of teams read from the file
void readManyBasketballTeams(ifstream& infile, BasketballTeam teams[], int& numberOfTeams){
	infile >> numberOfTeams;
	for (int i = 0; i < numberOfTeams; i++) {
		readBasketballTeam(infile, teams[i]);
	}
}

// Description: This function prints headers to the output file then calls the function to print the teams.
// Pre: The array of structs teams[] is able to be read, and the number of teams is known, and the output file has been opened.
// Post: The headers and basketball teams have been printed to the output file.
void printManyBasketballTeams(BasketballTeam teams[], int numberOfTeams, ofstream& outfile)
{
  outfile << endl << endl << setw(13) << "College" << setw(10) << "Mascot";
  outfile << setw(5) << " " << setw(8) << "Wins" << setw(9) << "Losses" << setw(6) << "PPG" << endl << endl;
  for (int i = 0; i < numberOfTeams; i++)
  {
    printBasketballTeam(teams[i], outfile);
  }
  outfile << endl << endl;
}

// Description: This function reads the data of multiple basketball teams and sorts the teams aplphabetically by the name
// 							of the college
// Pre: The array of structs teams holds all the data for each team and is not sorted and numberOfTeams holds the number of teams
// Post: The array of structs teams is sorted aplphabetically by the name of the college and the numberOfTeams is still the number of teams
void bubbleSortCollege(BasketballTeam*& teams, int numberOfTeams)
{
  bool hasSwapped = false;
  int pass = 1;
  while (!hasSwapped && (pass < numberOfTeams))
  {
    for(int i = 0; i < (numberOfTeams - pass); i++)
    {
      if(teams[i].college[0] > teams[i + 1].college[0])
      {
        swap(teams, i);
        hasSwapped = false;
      }
    }
    pass++;
  }
}

// Description: This function makes it possible for other functions to swap information contined in a read file.
// Pre: The teams array is created and able to be changed directly, int i has been passed through to be used again.
// Post: When called, this function will now be able to swap variables depending on what type of swap was wanted (letter, size, etc)
void swap(BasketballTeam*& teams, int i)
{
  BasketballTeam first = teams[i];
  teams[i] = teams[i + 1];
  teams[i + 1] = first;
}

// Description:  This function reads the data of multiple basketball teams and sorts the teams aplphabetically by the type
// 							of the mascott
// Pre: The array of structs teams holds all the data for each team and is not sorted and numberOfTeams holds the number of teams
// Post: The array of structs teams is sorted aplphabetically by the type of the mascot and the numberOfTeams is still the number of teams
void bubbleSortMascot(BasketballTeam*& teams, int numberOfTeams)
{
  bool hasSwapped = false;
  int pass = 1;
  while (!hasSwapped && (pass < numberOfTeams))
  {
    for(int i = 0; i < (numberOfTeams - pass); i++)
    {
      if(teams[i].mascotName[0] > teams[i + 1].mascotName[0])
      {
        swap(teams, i);
        hasSwapped = false;
      }
    }
    pass++;
  }
}

// Description: This function reads the data of multiple basketball teams and sorts the teams by most number of wins
// Pre: The array of structs teams holds all the data for each team and is not sorted and numberOfTeams holds the number of teams
// Post: The array of structs teams is sorted by most wins and the numberOfTeams is still the number of teams
void bubbleSortWins(BasketballTeam*& teams, int numberOfTeams)
{
  bool hasSwapped = false;
  int pass = 1;
  while (!hasSwapped && (pass < numberOfTeams))
  {
    for(int i = 0; i < (numberOfTeams - pass); i++)
    {
      if(teams[i].wins < teams[i + 1].wins)
      {
        swap(teams, i);
        hasSwapped = false;
      }
    }
    pass++;
  }
}
