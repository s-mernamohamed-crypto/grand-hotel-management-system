#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H
#pragma once
#include <vector>
#include <string>
#include "Room.h"
#include "Reservation.h"
#include "EventReservation.h"
#include "User.h" 
#include "FileManager.h" 
using namespace std;
class ApplicationManager {
private:
    vector<Room> rooms;
    vector<Reservation> reservations;
    vector<EventReservation> events;
    vector<User*> users;
    FileManager fileMgr;

public:
    ApplicationManager();
    ~ApplicationManager();

    void ExitAndSave();
    User* AuthenticateUser(string u, string p);
    void RegisterNewGuest(string u, string p);

    vector<Room>& getRooms();
    vector<Reservation>& getReservations();
    vector<EventReservation>& getEvents();

    int generateReservationID();
    int generateEventID();

    int getEventCountOnDate(string date);

    double CalculateGuestTotalBill(int guestID, double extraCharges);
};

#endif