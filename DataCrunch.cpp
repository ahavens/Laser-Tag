#include "Player.h"
#include <iostream>
#include <fstream>
#include "DataCrunch.h"
using namespace std;
#include <string>
#include <sstream>


DataCrunch:: DataCrunch()
{
    //strings relating to the player
    string line, playid, name, name2, newName, teamAName, teamBName, teamcount, tags, taggerString, taggedString, secondsString, pointsString;
    id = 0;
    tagsInMatch = 0;
    teamAPoints=0;
    teamBPoints=0;
    teamACount=0;
    teamBCount=0;
    tagger = 0;
    tagged = 0;
    seconds = 0;
    points = 0;
}

//Data crunch for team A
void DataCrunch::crunchTeamA(std::ifstream& teamA)
{
    if(teamA.is_open())
    {
        //counter
        int i = 0;
        getline(teamA, teamAName);
        getline(teamA, teamcount);
        teamACount = atoi(teamcount.c_str());

        //initialize the array
        teamAInfo = new Player[teamACount];

        //this will go through each line and find the id and the name
        while(getline(teamA, line))
        {
            //Found I could use a stringstream object to parse the line of strings
            stringstream s(line);
            int j = 0;
            s >> playid;
            while(s >> name)
            {
                //determines if it is the beginning of the name
                if(j == 0)
                {
                    newName += name;
                    j++;
                }
                //otherwise, add on to existing name
                else
                    newName = newName + " " + name;
            }
            //turn string to int
            id = atoi(playid.c_str());

            //goes through each player object in array and set the name and id of the player
            teamAInfo[i].getPlayName(newName);
            teamAInfo[i].setPlayID(id);
            newName.clear();
            i++;
        }
        teamA.close();
    }
    else cout<<"unable to open file";
}

void DataCrunch::crunchTeamB(std::ifstream& teamB)
{
    if(teamB.is_open())
    {
        //counter redone
        int i = 0;
        getline(teamB, teamBName);
        getline(teamB, teamcount);
        teamBCount = atoi(teamcount.c_str());
        //initialize the B array
        teamBInfo = new Player[teamBCount];

        //this will go through each line and find the id and the name
         while(getline(teamB, line))
         {
            //same as first time, used a stringstream to find spaces in the names
            stringstream s(line);
            int j = 0;
            s >> playid;
            while(s >> name)
            {
                if(j == 0)
                {
                    newName += name;
                    j++;
                }
                else
                    newName = newName + " " + name;
            }

            id = atoi(playid.c_str());
            //goes through each player object in array and set the name and id of the player
            teamBInfo[i].getPlayName(newName);
            teamBInfo[i].setPlayID(id);
            newName.clear();
            i++;
        }
        teamB.close();
    }
    else cout<<"unable to open file";



}

void DataCrunch::crunchMatchFile(std::ifstream& matchFile)
{
    //create a 2x2 array for each team to hold the opposite team's information
    for(int i = 0; i < teamACount; i++)
    {
        teamAInfo[i].createArray(teamBCount, teamBInfo);
    }
    for(int i = 0; i < teamBCount; i++)
    {
        teamBInfo[i].createArray(teamACount, teamAInfo);
    }

    if(matchFile.is_open())
    {
        int i = 0;

        //gets the number of tags in match
        getline(matchFile, tags);
        tagsInMatch = atoi(tags.c_str());

        //the evaluation of the match file must happen here
        while(matchFile >> taggerString && i != tagsInMatch)
        {
            //these will get the info from the lines and separate them into specific ints
            matchFile >> taggedString;
            matchFile >> secondsString;
            matchFile >> pointsString;
            //assign the strings to their proper ints
            tagger = atoi(taggerString.c_str());
            tagged = atoi(taggedString.c_str());
            seconds = atoi(secondsString.c_str());
            points = atoi(pointsString.c_str());

            //for loop will go through A and B and check to see if the player tagged someone
            for(int j = 0; j < teamACount; j++)
                {
                    if(tagger == teamAInfo[j].getPlayID())
                    {
                        teamAInfo[j].addPoints(points);
                        teamAInfo[j].timesPlayerTagged();
                        //adds to the created array in the player class here
                        teamAInfo[j].addToTag(tagged);
                    }
                }
            for(int j = 0; j < teamBCount; j++)
            {
                    if(tagger == teamBInfo[j].getPlayID())
                    {
                        teamBInfo[j].addPoints(points);
                        teamBInfo[j].timesPlayerTagged();
                        //adds to the created array in the player class here
                        teamBInfo[j].addToTag(tagged);
                    }
             }
            i++;
        }
    }

    else cout<< "unable to open the file";
    matchFile.close();
}

//LOW VERBOSITY WORKS
void DataCrunch::outPuttoFileLow(std::ofstream& outputFile)
{
    Player objectA;
    Player objectB;

    teamAPoints = objectA.returnTeamPoints(teamAInfo, teamACount);
    teamBPoints = objectB.returnTeamPoints(teamBInfo, teamBCount);

    if(teamAName < teamBName)
    {
        outputFile << teamAName << ": " << teamAPoints << " points" << '\n';
        outputFile << teamBName << ": " << teamBPoints << " points"<< '\n';
    }
    else
    {
        outputFile << teamBName << ": " << teamBPoints << " points" << '\n';
        outputFile << teamAName << ": " << teamAPoints << " points"<< '\n';
    }


    if(teamAPoints > teamBPoints)
    {
        outputFile<< "Overall Winners: " << teamAName;
    }
    else outputFile<< "Overall Winners: " << teamBName;

    //delete the arrays
    delete[] teamBInfo;
    delete[] teamAInfo;
    //outputFile.close();
}

//MEDIUM VERBOSITY WORKS
void DataCrunch::outPuttoFileMedium(std::ofstream& outputFile)
{
    Player objectA;
    Player objectB;
    //organize team based on tags
    objectA.organizeTeamArray(teamAInfo, teamACount);
    objectB.organizeTeamArray(teamBInfo, teamBCount);
    //calculate team points
    teamAPoints = objectA.returnTeamPoints(teamAInfo, teamACount);
    teamBPoints = objectB.returnTeamPoints(teamBInfo, teamBCount);
    //finds who has the higest score
    int highestScoreA = objectA.highestScore(teamAInfo, teamACount);
    int highestScoreB = objectB.highestScore(teamBInfo, teamBCount);

    //determines if teamA is higher alphabetically and if so, prints it first
    if(teamAName < teamBName)
    {
        outputFile << teamAName;
        outputFile << '\n';
        //prints out the number of tags a player has
        for(int i = 0; i <teamACount; i++)
            {
                outputFile << teamAInfo[i].showName() << " had a total of " << teamAInfo[i].getTagged() << " tag(s)" << '\n';
            }

        outputFile << '\n';
        outputFile<<'\n';

        outputFile << teamBName;
        outputFile<<'\n';

        //prints out number of tags a player has
        for(int i = 0; i <teamBCount; i++)
        {
            outputFile<<teamBInfo[i].showName() << " had a total of " << teamBInfo[i].getTagged() << " tag(s)" << '\n';
        }

        outputFile << '\n';
        outputFile << '\n';

        //determines highest score for teamA
        for(int i = 0; i < teamACount; i++)
        {
            if(i == highestScoreA)
            {
                outputFile << "Best Score from " << teamAName << ": " << teamAInfo[i].showName() << " (" << teamAInfo[i].getPoints() << ")";
                outputFile << '\n';
            }
        }
        //determines higest score for teamB
        for(int i = 0; i < teamBCount; i++)
        {
            if(i == highestScoreB)
            {
                outputFile << "Best Score from " << teamBName << ": " << teamBInfo[i].showName() << " (" << teamBInfo[i].getPoints() << ")";
                outputFile << '\n';
            }
        }

        outputFile << teamAName << " : " << teamAPoints << " points" << '\n';
        outputFile << teamBName << " : " << teamBPoints << " points" << '\n';


    }

    //repeats above, but this time, assuming teamBName is higher alphabetically
    else
    {
        outputFile << teamBName;
        outputFile << '\n';

        for(int i = 0; i <teamBCount; i++)
            {
                outputFile << teamBInfo[i].showName() << " had a total of " << teamBInfo[i].getTagged() << " tag(s)" << '\n';
            }

            outputFile << '\n';
            outputFile<<'\n';

            outputFile << teamAName;
            outputFile<<'\n';

            for(int i = 0; i <teamACount; i++)
            {
                outputFile << teamAInfo[i].showName() << " had a total of " << teamAInfo[i].getTagged() << " tag(s)" << '\n';
            }
            outputFile << '\n';
            outputFile << '\n';

            for(int i = 0; i < teamBCount; i++)
            {
                if(i == highestScoreB)
                {
                    outputFile << "Best Score from " << teamBName << ": " << teamBInfo[i].showName() << " (" << teamBInfo[i].getPoints() << ")";
                    outputFile << '\n';
                }
            }
            for(int i = 0; i < teamACount; i++)
            {
                if(i == highestScoreA)
                {
                    outputFile << "Best Score from " << teamAName << ": " << teamAInfo[i].showName() << " (" << teamAInfo[i].getPoints()<< ")";
                    outputFile << '\n';
                }
            }

            outputFile << teamBName << " : " << teamBPoints << " points" << '\n';
            outputFile << teamAName << " : " << teamAPoints << " points" << '\n';
        }

        if(teamBPoints > teamAPoints)
        {
            outputFile << "Overall Winners: " << teamBName;
        }
        else
        {
            outputFile << "Overall Winners: " << teamAName;
        }
        outputFile << '\n';

        //delete the team arrays
        delete[] teamBInfo;
        delete[] teamAInfo;
    //outPutFile.close();
}

//HIGH VERBOSITY WORKS, NEED TO ORGANIZE IT THOUGH
void DataCrunch::outPuttoFileHigh(std::ofstream& outputFile)
{
    Player objectA;
    Player objectB;

    //Sort array by who has the highest number of tags
    objectA.organizeTeamArray(teamAInfo, teamACount);
    objectB.organizeTeamArray(teamBInfo, teamBCount);

    //created a temporary array for each team that I can sort alphabetically
    Player *tempA = new Player[teamACount];
    for(int i = 0; i < teamACount; i++)
        tempA[i] = teamAInfo[i];
    Player *tempB = new Player[teamBCount];
    for(int i = 0; i < teamBCount; i++)
        tempB[i] = teamBInfo[i];

    Player tempplayer;
    //need to sort array alphabetically
    for (int i=0; i< (teamACount -1); i++)    // element to be compared
        {
           for(int j = (i+1); j < teamACount; j++)   // rest of the elements
              {
                 if(tempA[i].showName() > tempA[j].showName())         // descending order
                  {
                            tempplayer= tempA[i];          // swap
                            tempA[i] = tempA[j];
                            tempA[j] = tempplayer;
                  }
               }
         }
     for (int i=0; i< (teamBCount -1); i++)    // element to be compared
        {
           for(int j = (i+1); j < teamBCount; j++)   // rest of the elements
              {
                 if(tempB[i].showName() > tempB[j].showName())          // descending order
                  {
                            tempplayer= tempB[i];          // swap
                            tempB[i] = tempB[j];
                            tempB[j] = tempplayer;
                  }
               }
         }

    teamAPoints = objectA.returnTeamPoints(teamAInfo, teamACount);
    teamBPoints = objectB.returnTeamPoints(teamBInfo, teamBCount);

    //determines order to print team by alphabetical order
    if(teamAName < teamBName)
    {
        int tag;
        outputFile << teamAName << '\n';

        //prints out the number of times the player tagged someone
        for(int i = 0; i < teamACount; i++)
        {
            for(int j = 0; j < teamBCount; j++)
            {
                //goes into the 2x2 array created to determine how many times this player tagged that player
                tag = teamAInfo[i].returnTagInfo(tempB[j].getPlayID());
                outputFile << teamAInfo[i].showName() << " tagged " << tempB[j].showName() << " " << tag << " times" << '\n';
            }
            //prints out number of total tags player had
            outputFile << teamAInfo[i].showName() << " had a total of " << teamAInfo[i].getTagged() << " tag(s)" << '\n';
        }

        outputFile << teamAName << " : " << teamAPoints << " points" << '\n' << '\n';

        outputFile << teamBName << '\n';
        for(int i = 0; i < teamBCount; i++)
        {
            for(int j = 0; j < teamACount; j++)
            {
                //goes into the 2x2 array created to determine how many times this player tagged that player
                tag = teamBInfo[i].returnTagInfo(tempA[j].getPlayID());
                outputFile << teamBInfo[i].showName() << " tagged " << tempA[j].showName() << " " << tag << " times" << '\n';
            }
            //prints out number of total tags player had
            outputFile << teamBInfo[i].showName() << " had a total of " << teamBInfo[i].getTagged() << " tag(s)" << '\n';
        }

        outputFile << teamBName << " : " << teamBPoints << " points" << '\n' << '\n';

        if(teamBPoints > teamAPoints)
            outputFile << "Winners " << teamBName;
        else
            outputFile << "Winners " << teamAName;
    }
    else
    {
        int tag;
        outputFile << teamBName << '\n';
        //prints out the number of times the player tagged someone
        for(int i = 0; i < teamBCount; i++)
        {
           for(int j = 0; j < teamACount; j++)
            {
               tag = teamBInfo[i].returnTagInfo(tempA[j].getPlayID());
               outputFile << teamBInfo[i].showName() << " tagged " << tempA[j].showName() << " " << tag << " times" << '\n';
             }
           outputFile << teamBInfo[i].showName() << " had a total of " << teamBInfo[i].getTagged() << " tag(s)" << '\n';
        }
        outputFile << teamBName << " : " << teamBPoints << " points" << '\n' << '\n';


        outputFile << teamAName << '\n';
        for(int i = 0; i < teamACount; i++)
        {
            for(int j = 0; j < teamBCount; j++)
             {
                tag = teamAInfo[i].returnTagInfo(tempB[j].getPlayID());
                outputFile << teamAInfo[i].showName() << " tagged " << tempB[j].showName() << " " << tag << " times" << '\n';
             }
            outputFile << teamAInfo[i].showName() << " had a total of " << teamAInfo[i].getTagged() << " tag(s)" << '\n';
        }
        outputFile << teamAName << " : " << teamAPoints << " points" << '\n' << '\n';

    }

    if(teamBPoints > teamAPoints)
       outputFile << "Winners : " << teamBName;
    else
       outputFile << "Winners : " << teamAName;

    delete[] tempA;
    delete[] tempB;
    delete[] teamBInfo;
    delete[] teamAInfo;

}

