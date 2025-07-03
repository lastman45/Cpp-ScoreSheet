#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <cstring>
#include <fstream>

using namespace std;

struct SoccerPlayer
{
    char PlayerName[20];
    int Goals;
    int Assists;
    int YellowCards;
    int RedCards;
};

void displayPlayerStats(SoccerPlayer *Players, int playerCount)
{
    cout << "\nPlayer Statistics Summary:\n";
    int totalGoals = 0, totalAssists = 0, totalYellowCards = 0, totalRedCards = 0;
    for (int i = 0; i < playerCount; i++)
    {
        totalGoals += Players[i].Goals;
        totalAssists += Players[i].Assists;
        totalYellowCards += Players[i].YellowCards;
        totalRedCards += Players[i].RedCards;
    }
    cout << "Total Goals: " << totalGoals << endl;
    cout << "Total Assists: " << totalAssists << endl;
    cout << "Total Yellow Cards: " << totalYellowCards << endl;
    cout << "Total Red Cards: " << totalRedCards << endl;
}

void sortPlayersByGoals(SoccerPlayer *Players, int playerCount)
{
    for (int i = 0; i < playerCount - 1; i++)
    {
        for (int j = 0; j < playerCount - i - 1; j++)
        {
            if (Players[j].Goals < Players[j + 1].Goals)
            {
                swap(Players[j], Players[j + 1]);
            }
        }
    }
}

void searchPlayer(SoccerPlayer *Players, int playerCount)
{
    char searchName[20];
    cout << "\nEnter player name to search: ";
    cin >> searchName;
    bool found = false;
    for (int i = 0; i < playerCount; i++)
    {
        if (strcmp(Players[i].PlayerName, searchName) == 0)
        {
            cout << "\nPlayer Name: " << Players[i].PlayerName << endl;
            cout << "Goals Scored: " << Players[i].Goals << endl;
            cout << "Assists: " << Players[i].Assists << endl;
            cout << "Yellow Cards: " << Players[i].YellowCards << endl;
            cout << "Red Cards: " << Players[i].RedCards << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "\nPlayer not found!" << endl;
    }
}

void savePlayersToFile(SoccerPlayer *Players, int playerCount)
{
    ofstream outFile("players.txt");
    for (int i = 0; i < playerCount; i++)
    {
        outFile << Players[i].PlayerName << " " << Players[i].Goals << " "
                << Players[i].Assists << " " << Players[i].YellowCards << " "
                << Players[i].RedCards << endl;
    }
    outFile.close();
    cout << "Player data saved" << endl;
}

int main()
{
    int playerCount;
    cout << "Enter number of players: ";
    cin >> playerCount;

    SoccerPlayer *Players = new SoccerPlayer[playerCount];

    for (int i = 0; i < playerCount; i++)
    {
        cout << "\nEnter Player Name: ";
        cin >> Players[i].PlayerName;

        do
        {
            cout << "Enter Goals Scored: ";
            cin >> Players[i].Goals;
        } while (Players[i].Goals < 0);

        do
        {
            cout << "Enter Assists: ";
            cin >> Players[i].Assists;
        } while (Players[i].Assists < 0);

        do
        {
            cout << "Enter Yellow Cards: ";
            cin >> Players[i].YellowCards;
        } while (Players[i].YellowCards < 0);

        do
        {
            cout << "Enter Red Cards: ";
            cin >> Players[i].RedCards;
        } while (Players[i].RedCards < 0);
    }

    displayPlayerStats(Players, playerCount);

    sortPlayersByGoals(Players, playerCount);
    cout << "\nPlayers sorted by goals scored:\n";
    for (int i = 0; i < playerCount; i++)
    {
        cout << Players[i].PlayerName << " - Goals: " << Players[i].Goals << endl;
    }

    searchPlayer(Players, playerCount);
    savePlayersToFile(Players, playerCount);

    delete[] Players;
    cout << "\n\nTHANKS FOR USING THE PROGRAM\n";
    getch();
    return 0;
}
