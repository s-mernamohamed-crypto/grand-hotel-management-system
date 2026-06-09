#include "FileManager.h"
#include "Helper.h"
#include <fstream>
#include <sstream>

void FileManager::SaveAll(const vector<Room>& rooms, const vector<Reservation>& res, const vector<User*>& users, const vector<EventReservation>& events) {
    ofstream rFile("rooms.txt");
    for (const auto& room : rooms) rFile << room.toFileString() << "\n";
    rFile.close();

    ofstream resFile("reservations.txt");
    for (const auto& r : res) resFile << r.toFileString() << "\n";
    resFile.close();

    ofstream uFile("users.txt");
    for (const auto* u : users) {
        if (u != nullptr) {
            uFile << u->toFileString() << "\n";
        }
    }
    uFile.close();

    ofstream evFile("events.txt");
    for (const auto& ev : events) evFile << ev.toFileString() << "\n";
    evFile.close();
}

void FileManager::LoadRooms(vector<Room>& rooms) {
    ifstream inFile("rooms.txt");
    if (inFile) {
        string line;
        while (getline(inFile, line)) {
            cleanString(line);
            if (line.empty()) continue;
            stringstream ss(line);
            string num, type, status, price;
            getline(ss, num, ','); getline(ss, type, ','); getline(ss, status, ','); getline(ss, price);
            Room r(stoi(num), type, stod(price));
            r.setRoomStatus(status);
            rooms.push_back(r);
        }
        inFile.close();
    }
    else {
        for (int i = 1; i <= 300; i++) {
            if (i <= 100) rooms.push_back(Room(i, "Single", 500.0));
            else if (i <= 200) rooms.push_back(Room(i, "Double", 800.0));
            else rooms.push_back(Room(i, "Suite", 1500.0));
        }
    }
}

void FileManager::LoadUsers(vector<User*>& users) {
    ifstream inFile("users.txt");
    if (!inFile) {
        users.push_back(new Receptionist("merna", 1, "123"));
        users.push_back(new Receptionist("malak", 2, "345"));
        users.push_back(new Receptionist("jannah", 3, "678"));
        return;
    }
    string line;
    while (getline(inFile, line)) {
        cleanString(line); if (line.empty()) continue;
        stringstream ss(line); string name, id, pass, type;
        getline(ss, name, ','); getline(ss, id, ','); getline(ss, pass, ','); getline(ss, type, ',');

        if (type == "admin") {
            users.push_back(new Receptionist(name, stoi(id), pass));
        } else {
            string ecStr;
            if (!ss.eof() && getline(ss, ecStr)) {
                double ec = ecStr.empty() ? 0.0 : stod(ecStr);
                users.push_back(new Guest(name, stoi(id), pass, ec));
            } else {
                users.push_back(new Guest(name, stoi(id), pass, 0.0));
            }
        }
    }
    inFile.close();
}

void FileManager::LoadReservations(vector<Reservation>& res) {
    ifstream inFile("reservations.txt");
    if (!inFile) return;
    string line;
    while (getline(inFile, line)) {
        cleanString(line); if (line.empty()) continue;
        stringstream ss(line); string rID, gID, rNum, in, out, dur, bStr, lStr, dStr;
        getline(ss, rID, ','); getline(ss, gID, ','); getline(ss, rNum, ',');
        getline(ss, in, ','); getline(ss, out, ','); getline(ss, dur, ',');
        getline(ss, bStr, ','); getline(ss, lStr, ','); getline(ss, dStr);

        int bCount = bStr.empty() ? 0 : stoi(bStr);
        int lCount = lStr.empty() ? 0 : stoi(lStr);
        int dCount = dStr.empty() ? 0 : stoi(dStr);

        res.push_back(Reservation(stoi(rID), stoi(gID), stoi(rNum), in, out, stoi(dur), bCount, lCount, dCount));
    }
    inFile.close();
}
void FileManager::LoadEvents(vector<EventReservation>& evs) {
    ifstream inFile("events.txt");
    if (!inFile) return;
    string line;
    while (getline(inFile, line)) {
        cleanString(line); if (line.empty()) continue;
        stringstream ss(line); string eID, gID, type, singer, date, priceStr;
        getline(ss, eID, ','); getline(ss, gID, ','); getline(ss, type, ',');
        getline(ss, singer, ','); getline(ss, date, ','); getline(ss, priceStr);

        double price = priceStr.empty() ? 0.0 : stod(priceStr);
        evs.push_back(EventReservation(stoi(eID), stoi(gID), type, singer, date, price));
    }
    inFile.close();
}