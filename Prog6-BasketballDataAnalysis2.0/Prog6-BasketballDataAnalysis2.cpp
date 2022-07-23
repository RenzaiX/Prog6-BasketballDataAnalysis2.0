/* 
---------------------------------------------
Program 6: March Madness Frenzy 2.0

Course: CS 141, Spring 2022. Tues 11am lab
System: Windows using Visual Studio Code
Author: Mykola Turchak
---------------------------------------------
*/

#include <iostream> // For Input and Output
#include <fstream>  // For file input and output
#include <cassert>  // For the assert statement
#include <vector>   // For vectors
#include <sstream>  // For reading in CSV file and splitting by commas

using namespace std;

class Node; // this is the declaration, so that it can be used inside class Game below
            // the definition of the Node class comes after the Game class

class Game
{
public:
    // Default up to Fully-Qualified Constructor
    Game(string region = "N/A", int rankOne = -1, string teamOne = "N/A", int scoreOne = -1,
         int rankTwo = -1, string teamTwo = "N/A", int scoreTwo = -1,
         string winningTeam = "N/A", int roundNumber = -1, int gameNumber = -1)
    {
        this->region = region;
        this->team1Rank = rankOne;
        this->team1Name = teamOne;
        this->team1Score = scoreOne;
        this->team2Rank = rankTwo;
        this->team2Name = teamTwo;
        this->team2Score = scoreTwo;
        this->winningTeam = winningTeam;
        this->roundNum = roundNumber;
        this->gameNum = gameNumber;
        this->subBrackets = NULL;
    }

    // Copy Constructor
    Game(const Game &otherGame)
    {
        this->region = otherGame.region;
        this->team1Rank = otherGame.team1Rank;
        this->team1Name = otherGame.team1Name;
        this->team1Score = otherGame.team1Score;
        this->team2Rank = otherGame.team2Rank;
        this->team2Name = otherGame.team2Name;
        this->team2Score = otherGame.team2Score;
        this->winningTeam = otherGame.winningTeam;
        this->roundNum = otherGame.roundNum;
        this->gameNum = otherGame.gameNum;
        this->subBrackets = otherGame.subBrackets;
    }

    // Getters / Accessor methods
    string getRegion() { return region; }
    int getRoundNum() { return roundNum; }
    string getTeamOneName() { return team1Name; }
    int getTeamOneRank() { return team1Rank; }
    int getTeamOneScore() { return team1Score; }
    string getTeamTwoName() { return team2Name; }
    int getTeamTwoRank() { return team2Rank; }
    int getTeamTwoScore() { return team2Score; }
    string getWinner() { return winningTeam; }
    int getGameNum() { return gameNum; }
    Node *getSubBrackets() { return subBrackets; }

    // Setters / Mutator methods
    void setTeamOneName(string newTeamOneName) { this->team1Name = newTeamOneName; }
    void setTeamTwoName(string newTeamTwoName) { this->team2Name = newTeamTwoName; }
    void setWinner(string newWinner) { this->winningTeam = newWinner; }
    void setSubBrackets(Node *newSubBrackets) { this->subBrackets = newSubBrackets; }

    // Utility function to display the game
    void displayGame()
    {
        cout << "Round " << roundNum << ", Game " << gameNum << ": "
             << team1Name << " vs " << team2Name << ". "
             << "Winner: " << winningTeam << "\n";
    }

private:
    string region;
    int roundNum;
    int gameNum;
    string team1Name;
    string team2Name;
    string winningTeam;
    int team1Rank;
    int team2Rank;
    int team1Score;
    int team2Score;
    Node *subBrackets; // This is a pointer to a Node, in order to represent the subbracts as a linked list
};

// Node class in order to implement linked lists
class Node
{

public:
    Node()
    {
        pNext = NULL;
    }

    Node(Game theSubBracket, Node *thePNext)
    {
        subBracket = theSubBracket;
        pNext = thePNext;
    }

    // ideally these should be private, but we are making them public to make the code a bit simpler
    Game subBracket;
    Node *pNext;
};

//--------------------------------------------------------------------------------
// Display welcome message, introducing the user to the program
void displayWelcomeMessage()
{
    cout << "Program 6: March Madness Frenzy 2.0\n"
         << "CS 141, Spring 2022, UIC\n"
         << "\n"
         << "This program reads in data from NCAA Basketball Tournaments (aka March Madness). "
         << "It uses the hierarchy of the brackets (implemented via linked lists) to allow you "
         << "to see the path taken to the championship, and evaluate the resulting brackets if "
         << "some games had a different outcome.\n"
         << endl;
} // end displayWelcomeMessage()

//--------------------------------------------------------------------------------
// Read in the game data and store in a vector
void readInGameData(string filename, vector<Game> &games)
{

    string region, teamOne, teamTwo, winningTeam;
    int rankOne, rankTwo, roundNumber, gameNumber, scoreOne, scoreTwo;

    ifstream inStream;
    inStream.open(filename);
    assert(inStream.fail() == false);

    string row;
    getline(inStream, row); // read in header from file, and ignore

    // read in each line of the file
    while (getline(inStream, row))
    {
        stringstream s_stream(row); // create stringstream from the row

        // separate the line by commas into each column
        int colNum = 0;
        while (s_stream.good())
        {
            string columnVal;
            getline(s_stream, columnVal, ','); // get first string delimited by comma

            // use the substring to fill in the appropriate part of the BillboardRecord
            switch (colNum)
            {
            case 0:
                region = columnVal;
                break;
            case 1:
                rankOne = stoi(columnVal);
                break;
            case 2:
                teamOne = columnVal;
                break;
            case 3:
                if (columnVal != "")
                {
                    scoreOne = stoi(columnVal);
                }
                else
                {
                    scoreOne = -1;
                }
                break;
            case 4:
                rankTwo = stoi(columnVal);
                break;
            case 5:
                teamTwo = columnVal;
                break;
            case 6:
                if (columnVal != "")
                {
                    scoreTwo = stoi(columnVal);
                }
                else
                {
                    scoreTwo = -1;
                }
                break;
            case 7:
                winningTeam = columnVal;
                break;
            case 8:
                roundNumber = stoi(columnVal);
                break;
            case 9:
                gameNumber = stoi(columnVal);
                break;
            default: // should not get here, because there are only 10 columns
                cout << "More columns in the file than expected... Exiting program" << endl;
                exit(0);
                break;
            }
            colNum++;
        }
        // Create instance of the class using the column values
        Game oneGame;
        oneGame = Game(region, rankOne, teamOne, scoreOne, rankTwo, teamTwo, scoreTwo, winningTeam, roundNumber, gameNumber);
        // and add it to the vector
        games.push_back(oneGame);

    } // end while(getline(instream, row))

} // end readInGameData() function

//--------------------------------------------------------------------------------
// Identify the sub-brackets for each game and modify the class instances in the vector accordingly
void determineSubBrackets(vector<Game> &games)
{

    // Nested loop to find the sub-brackets for each game
    // We go in reverse, starting at round 1 and going up to round 6
    //      Note - this is so that when we add subbrackets for round 6, the subbrackets for the games
    //             in round 5 have been determined, and so on and so forth
    for (int i = games.size() - 1; i >= 0; i--)
    {
        for (int j = games.size() - 1; j >= 0; j--)
        {
            // Check that we are not looking at the same game
            if (i == j)
            {
                continue;
            }
            // games[j] is a sub-bracket of games[i] if it is from the previous round,
            // and if the winning team from games[j] is one of the teams in games[i]
            if ((games.at(j).getRoundNum() == (games.at(i).getRoundNum() - 1)) &&
                (games.at(j).getWinner() == games.at(i).getTeamOneName() || games.at(j).getWinner() == games.at(i).getTeamTwoName()))
            {
                // TO DO: Add games[j] to the linked list of sub-brackets for games[i]
                // ...
                Node* pITemp = games[i].getSubBrackets();
                games[i].setSubBrackets(new Node(games[j],pITemp));
            }
        }
    }

} // end of determineSubBrackets() function

// displays the menu options for the user
void displayMenu()
{
    cout << endl
         << "Select a menu option:" << endl
         << "   1. See the sub-brackets of one game" << endl
         << "   2. Display the path of the winning team to the championship" << endl
         << "   3. Undo the championship game for a given number of rounds" << endl
         << "   4. Exit" << endl
         << "Your choice --> ";
}


void printPath(Node * head, string winner)
{   
    
    //checks for the base case when head is NULL
    if(head == NULL)
    {
        return;
    }
    // print current node
    else if(head->subBracket.getWinner() == winner)
    {
        head->subBracket.displayGame();
    }
    //printPath(next)
    printPath(head->pNext, winner);

}

string returnNewWinner(Node * head, string winner, int round)
{   

    // print current node

    if(head == NULL)
    {
        return "";
    }
    if(head->subBracket.getTeamOneName() == winner && round == head->subBracket.getRoundNum())
    {   
        return head->subBracket.getTeamTwoName();
    }
    else if(head->subBracket.getTeamTwoName() == winner && round == head->subBracket.getRoundNum())
    {
        return head->subBracket.getTeamOneName();
    }

    returnNewWinner(head->pNext, winner, round);
}

void replaceWinner(Node * head, string oldWinner, string newWinner, int round)
{
    //checks for the base case when head is NULL
    if(head == NULL)
    {
        return;
    }
    // print current node
    if(head->subBracket.getWinner() == oldWinner && head->subBracket.getRoundNum() >= round)
    {
        head->subBracket.setWinner(newWinner);
    }

    if(head->subBracket.getTeamOneName() == oldWinner && head->subBracket.getRoundNum() > round)
    {
        head->subBracket.setTeamOneName(newWinner);
    }

    if(head->subBracket.getTeamTwoName() == oldWinner && head->subBracket.getRoundNum() > round)
    {
        head->subBracket.setTeamTwoName(newWinner);
    }
    //printPath(next)
    replaceWinner(head->pNext, oldWinner, newWinner, round);
}

void printRoundSixPath(vector <Game> games, string winner)
{   
    for(int i = games.size()-1; i>= 0;i--)
    {
        // cout << "games[i].getWinner(): " << games[i].getWinner() << " winner: " << winner << endl;
        if(games[i].getWinner() == winner)
        {
            games[i].displayGame();
        }
    }

}

string returnNewWinnerRoundSic(vector <Game> games, string winner, int round)
{   

    // print current node
    for(int i = 0; i < games.size(); i++)
    {
        if(games[i].getTeamOneName() == winner && round == games[i].getRoundNum())
        {   
            return games[i].getTeamTwoName();
        }
        else if(games[i].getTeamTwoName() == winner && round == games[i].getRoundNum())
        {
            return games[i].getTeamOneName();
        }
    }

    

}

void undoRoundSix(vector <Game> games, string oldWinner, string newWinner, int round )
{   
    for(int i = 0; i < games.size(); i++)
    {
        if(games[i].getWinner() == oldWinner && games[i].getRoundNum() >= round)
        {
            games[i].setWinner(newWinner);
        }
        if(games[i].getTeamOneName() == oldWinner && games[i].getRoundNum() > round)
        {
            games[i].setTeamOneName(newWinner);
        }
        if(games[i].getTeamTwoName() == oldWinner && games[i].getRoundNum() > round)
        {
            games[i].setTeamTwoName(newWinner);
        }
    }
    
}


// ----------------------------------------------------------------------
// Main() function of the program
int main()
{
    // Vector to hold tournament games
    vector<Game> games;

    displayWelcomeMessage();

    // Prompt user for the name of the file with the data
    string fileName;
    cout << "Enter the name of the file with the data for the NCAA tournament: ";
    cin >> fileName;

    // Read in the data from the file into a vector
    readInGameData(fileName, games);
    // Also identify sub-brackets for each game
    determineSubBrackets(games);

    // TO DO: Handle the different menu options
    // ...
    bool isrunning = true; // Boolean variable for checking the condition of while loop

    while (isrunning)
    {
        displayMenu();
        int menu;
        cin >> menu;

        if (menu == 1)
        {
            int gameRound;
            cout << "Enter the round number of the game: ";
            cin >> gameRound;

            string winningTeam;
            cout << "Enter the winning team of the game: ";
            cin.ignore(); // to ignore space
            getline(cin, winningTeam);

            bool matchCheck = false;

            for (int i = 0; i < games.size(); i++)
            {
                if (winningTeam == games[i].getWinner() && games[i].getRoundNum() == gameRound)
                {
                    matchCheck = true;
                    cout << endl << "The game is:" << endl;
                    games[i].displayGame();

                    Node *pTemp = games[i].getSubBrackets();
                    if(pTemp == NULL)
                    {
                        cout << endl << endl << "This game does not have any sub-brackets." << endl;
                    }
                    else
                    {
                        cout << endl << "Sub-brackets of this game are:" << endl;

                        while(pTemp != NULL)
                        {   
                            pTemp->subBracket.displayGame();
                            pTemp = pTemp->pNext;
                        }
                    }
                        
                }
            }

            if (matchCheck == false)
            {
                cout << "Sorry, no games matching that round number and winning team were found." << endl;
            }
        }

        else if (menu == 2)
        {
            string winner = games[0].getWinner();
            int count = 1;

            cout << "Path to the championship:" << endl;
            for(int i = games.size()-1; i>= 0;i--)
            {
                Node *pWinner = games[i].getSubBrackets();
                printPath(pWinner, winner);
            }
            games[0].displayGame();
        }

        else if(menu == 3)
        {
            cout << "Enter the number of rounds that you would like to undo (max of 6 allowed):";
            int undoCount;
            cin >> undoCount;

            while (undoCount <= 0 || undoCount >= 7)
            {
                cout << endl << "Invalid entry. Try again.\n";
                cout << "Enter the number of rounds that you would like to undo (max of 6 allowed):";
                cin >> undoCount;
            }
            
            string oldWinner = games[0].getWinner();
            int index = 6 - undoCount + 1;
            string newWinner;
            
            if(undoCount == 1)
            {   
                newWinner = returnNewWinnerRoundSic(games,oldWinner, index);
                undoRoundSix(games, oldWinner, newWinner, index);
                printRoundSixPath(games,newWinner);
            }
            else
            {
                for(int i = games.size()-1; i>= 0;i--)
                {
                    Node *pWinner = games[i].getSubBrackets();
                    newWinner = returnNewWinner(pWinner, oldWinner, index);
                    if(newWinner != "")
                    {
                        break;
                    }
                }

                for(int i = games.size()-1; i>= 0;i--)
                {
                    Node *pTemp = games[i].getSubBrackets();
                    replaceWinner(pTemp, oldWinner, newWinner, index);
                    printPath(pTemp, newWinner);
                }

                if(games[0].getTeamTwoName() == oldWinner)
                {
                    games[0].setTeamTwoName(newWinner);
                }
                else if(games[0].getTeamOneName() == oldWinner)
                {
                    games[0].setTeamOneName(newWinner);
                }
            }
            games[0].setWinner(newWinner);
            games[0].displayGame();

        }

        else if (menu == 4)
        {
            // Sets the while loop to false and break out
            isrunning = false;
            cout << "Exiting program..." << endl;
            break;
        }
        // If user input is invalid (not 1-4) then run the loop again
        else
        {
            cout << "Invalid value.  Please re-enter a value from the menu options below." << endl;
            continue;
        }
    }

    return 0;
} // end main()