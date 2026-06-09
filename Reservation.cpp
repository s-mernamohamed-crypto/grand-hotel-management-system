#include "Reservation.h"
Reservation::Reservation() : ReservationID(0), GuestID(0), RoomNum(0), Duration(0), BreakfastCount(0), LunchCount(0), DinnerCount(0) {}

Reservation::Reservation(int id, int gid, int rNum, string in, string out, int dur, int b, int l, int d)
    : ReservationID(id), GuestID(gid), RoomNum(rNum), CheckInDate(in), CheckOutDate(out), Duration(dur), BreakfastCount(b), LunchCount(l), DinnerCount(d) {}

int Reservation::getReservationID() const { return ReservationID; }
int Reservation::getGuestID() const { return GuestID; }
int Reservation::getRoomNum() const { return RoomNum; }
string Reservation::getCheckInDate() const { return CheckInDate; }
string Reservation::getCheckOutDate() const { return CheckOutDate; }
int Reservation::getDuration() const { return Duration; }
int Reservation::getBreakfast() const { return BreakfastCount; }
int Reservation::getLunch() const { return LunchCount; }
int Reservation::getDinner() const { return DinnerCount; }

string Reservation::toFileString() const {
    return to_string(ReservationID) + "," + to_string(GuestID) + "," +
        to_string(RoomNum) + "," + CheckInDate + "," +
        CheckOutDate + "," + to_string(Duration) + "," +
        to_string(BreakfastCount) + "," + to_string(LunchCount) + "," + to_string(DinnerCount);
}
bool Reservation::isValidDate(const string& dateStr) const {
    int d, m, y;
    if (sscanf(dateStr.c_str(), "%d-%d-%d", &d, &m, &y) != 3) {
        return false; 
    }
    if (y < 2025 || y > 2100) return false;
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > 31) return false;
    if (m == 2) { 
        bool isLeap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        if (d > (isLeap ? 29 : 28)) return false;
    } 
    else if (m == 4 || m == 6 || m == 9 || m == 11) {
        if (d > 30) return false;
    }
    return true; 
}