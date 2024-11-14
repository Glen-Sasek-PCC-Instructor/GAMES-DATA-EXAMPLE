#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Example command for reference, does not use this program
// tail -n+2 games.tsv | cut -d$'\t' -f7,2 | sort -t$'\t' -k2 -n -r | uniq | head | column -t -s $'\t'

using namespace std;

struct GameData {
    int appID; // 1
    string name;
    string releaseDate;
    string estimatedOwners;
    int peakCCU;
    int requiredAge;
    float price;
    int discountDLCCount;
    string aboutTheGame;
    string supportedLanguages; // 10
    string fullAudioLanguages;
    string reviews;
    string headerImage;
    string website;
    string supportUrl;
    string supportEmail;
    bool windows;
    bool mac;
    bool xlinux;
    int metacriticScore; // 20
    string metacriticUrl;
    float userScore;
    int positive;
    int negative;
    int scoreRank;
    int achievements;
    int recommendations;
    string notes;
    int avgPlaytimeForever;
    int avgPlaytimeTwoWeeks;
    int medianPlaytimeForever;
    int medianPlaytimeTwoWeeks;
    string developers;
    string publishers;
    string categories;
    string genres;
    string tags;
    string screenshots;
    string movies;
};

// Function to parse a line of data into a GameData struct
GameData parseLine(const string& line) {
    GameData gameData;
    stringstream ss(line);
    string field;
    
    // Extract each field and populate the struct (in the same order as the TSV)
    getline(ss, field, '\t'); 
    try {
        gameData.appID = stoi(field);
    } catch (exception &e) {
        gameData.appID = 0;
    }

    getline(ss, field, '\t'); gameData.name = field;
    getline(ss, field, '\t'); gameData.releaseDate = field;
    getline(ss, field, '\t'); gameData.estimatedOwners = field;

    getline(ss, field, '\t'); 
    try {
        gameData.peakCCU = stoi(field);
    } catch (exception &e) {
        gameData.peakCCU = 0;
    }

    getline(ss, field, '\t');
    try {
        gameData.requiredAge = stoi(field);
    } catch (exception &e) {
        gameData.requiredAge = 0;
    }

    getline(ss, field, '\t');
    try {
        gameData.price = stoi(field);
    } catch (exception &e) {
        gameData.price = 0;
    }

    getline(ss, field, '\t');
    try {
        gameData.discountDLCCount = stoi(field);
    } catch (exception &e) {
        gameData.discountDLCCount = 0;
    }

    getline(ss, field, '\t'); gameData.aboutTheGame = field;
    getline(ss, field, '\t'); gameData.supportedLanguages = field;
    getline(ss, field, '\t'); gameData.fullAudioLanguages = field;
    getline(ss, field, '\t'); gameData.reviews = field;
    getline(ss, field, '\t'); gameData.headerImage = field;
    getline(ss, field, '\t'); gameData.website = field;
    getline(ss, field, '\t'); gameData.supportUrl = field;
    getline(ss, field, '\t'); gameData.supportEmail = field;
    getline(ss, field, '\t'); gameData.windows = (field == "TRUE");
    getline(ss, field, '\t'); gameData.mac = (field == "TRUE");
    getline(ss, field, '\t'); gameData.xlinux = (field == "TRUE");
    getline(ss, field, '\t'); // 20
    try {
        gameData.metacriticScore = stoi(field);
    } catch (exception &e) {
        gameData.metacriticScore = 0;
    }

    getline(ss, field, '\t'); gameData.metacriticUrl = field;
    getline(ss, field, '\t');
    try {
        gameData.userScore = stoi(field);
    } catch (exception &e) {
        gameData.userScore = 0;
    }

    getline(ss, field, '\t');
    try {
        gameData.positive = stoi(field);
    } catch (exception &e) {
        gameData.positive = 0;
    }

    getline(ss, field, '\t');
    try {
        gameData.negative = stoi(field);
    } catch (exception &e) {
        gameData.negative = 0;
    }

    getline(ss, field, '\t');
    try {
        gameData.scoreRank = stoi(field);
    } catch (exception &e) {
        gameData.scoreRank = 0;
    }

    getline(ss, field, '\t');
    try {
        gameData.achievements = stoi(field);
    } catch (exception &e) {
        gameData.achievements = 0;
    }

    getline(ss, field, '\t'); //27
    try {
        gameData.recommendations = stoi(field);
    } catch (exception &e) {
        gameData.recommendations = 0;
    }

    getline(ss, field, '\t'); gameData.notes = field;
    getline(ss, field, '\t');
    try {
        gameData.avgPlaytimeForever = stoi(field);
    } catch (exception &e) {
        gameData.avgPlaytimeForever = 0;
    }

    getline(ss, field, '\t'); //30
    try {
        gameData.avgPlaytimeTwoWeeks = stoi(field);
    } catch (exception &e) {
        gameData.avgPlaytimeTwoWeeks = 0;
    }

    getline(ss, field, '\t');
    try {
        gameData.medianPlaytimeForever = stoi(field);
    } catch (exception &e) {
        gameData.medianPlaytimeForever = 0;
    }

    getline(ss, field, '\t');
    try {
        gameData.medianPlaytimeTwoWeeks = stoi(field);
    } catch (exception &e) {
        gameData.medianPlaytimeTwoWeeks = 0;
    }

    getline(ss, field, '\t'); gameData.developers = field;
    getline(ss, field, '\t'); gameData.publishers = field;
    getline(ss, field, '\t'); gameData.categories = field;
    getline(ss, field, '\t'); gameData.genres = field;
    getline(ss, field, '\t'); gameData.tags = field;
    getline(ss, field, '\t'); gameData.screenshots = field;
    getline(ss, field, '\t'); gameData.movies = field;

    return gameData;
}

// Function to read TSV file
vector<GameData> readTSVFile(const string& filename) {
    vector<GameData> games;
    ifstream file(filename);
    string line;

    // Skip the header line
    getline(file, line);

    cout << "READING:\t" << filename << endl;

    // Read each line and parse it
    while (getline(file, line)) {
        games.push_back(parseLine(line));
        cout << games.size() << endl << "\033[1A";
    }

    cout << endl;
    
    return games;
}

// Function to display data (for verification)
void displayData(const vector<GameData>& games) {
    const int MAX_ROWS = 10;
    for (int i = 0; i < MAX_ROWS; i++ ) {
        cout << "AppID: " << games[i].appID << ", Name: " << games[i].name 
                  << ", Release Date: " << games[i].releaseDate << "\n";
        // Add more fields as needed for full output
    }
}

int main() {
    string filename = "games.tsv";
    vector<GameData> games = readTSVFile(filename);

    // Display data to verify correctness
    displayData(games);

    return 0;
}
