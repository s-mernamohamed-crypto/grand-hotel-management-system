#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>

using namespace std;

class Reservation {
private:
    int ReservationID;
    int GuestID;
    int RoomNum;
    int Duration;
    string CheckInDate;
    string CheckOutDate;
    int BreakfastCount; 
    int LunchCount;
    int DinnerCount;
    bool isValidDate(const string& dateStr) const;

public:
    Reservation();
    Reservation(int id, int gid, int rNum, string in, string out, int dur, int b = 0, int l = 0, int d = 0);
    int getReservationID() const;
    int getGuestID() const;
    int getRoomNum() const;
    string getCheckInDate() const;
    string getCheckOutDate() const;
    int getDuration() const;
    int getBreakfast() const;
    int getLunch() const;
    int getDinner() const;
    string toFileString() const;
};

#endif