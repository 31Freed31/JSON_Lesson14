#include <iostream>
#include <fstream>
#include "json.hpp"
#include <vector>

using json = nlohmann::json;
using namespace std;

void findActor(const json& movies, const string& actor_name) {
    bool found = false;

    for (auto& movie : movies.items()) {
        string movie_title = movie.key();
        json movie_info = movie.value();

        for (auto& cast : movie_info["main_cast"]) {
            if (cast["actor"].get<string>().find(actor_name) != string::npos) {
                cout << "Movie: " << movie_title << " | Role: " << cast["character"] << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "Actor not found!" << endl;
    }
}

int main() {
    ifstream file("movies.json");
    json movies;

    if (file.is_open()) {
        file >> movies;
        file.close();
    }
    else {
        cerr << "Could not open the file!" << endl;
        return 1;
    }

    string actor_name;
    cout << "Enter actor's name: ";
    getline(cin, actor_name);

    findActor(movies, actor_name);

    return 0;
}
