#include "User.h"
#include "Room.h"
#include "Reservation.h"
#include "EventReservation.h" 
User::User(string u, int i, string p, string ut) : username(u), id(i), password(p), usertype(ut) {}
string User::getusername() const { return username; }
int User::getid() const { return id; }
string User::getusertype() const { return usertype; }
string User::getpassword() const { return password; }
bool User::loggin(string us, string pas) { return (us == username && pas == password); }
string User::toFileString() const { return username + "," + to_string(id) + "," + password + "," + usertype; }

// Receptionist
Receptionist::Receptionist(string user, int i, string pass) : User(user, i, pass, "admin") {}
void Receptionist::addRoom(vector<Room>& r_list, Room newroom) { r_list.push_back(newroom); }
void Receptionist::updateRoomStat(vector<Room>& r_list, int r_no, string r_stat) {
    for (auto& r : r_list) {
        if (r.getRoomNum() == r_no) {
            r.setRoomStatus(r_stat);
            break;
        }
    }
}
bool Receptionist::cancelReservation(vector<Reservation>& re_list, vector<Room>& r_list, int resid) {
    for (size_t i = 0; i < re_list.size(); i++) {
        if (re_list[i].getReservationID() == resid) {
            updateRoomStat(r_list, re_list[i].getRoomNum(), "Available");
            re_list.erase(re_list.begin() + i);
            return true;
        }
    }
    return false;
}
bool Receptionist::cancelEvent(vector<EventReservation>& ev_list, int evID) {
    for (size_t i = 0; i < ev_list.size(); i++) {
        if (ev_list[i].getEventResID() == evID) {
            ev_list.erase(ev_list.begin() + i);
            return true;
        }
    }
    return false;
}

Guest::Guest(string user_name, int i, string pass, double ec) : User(user_name, i, pass, "guest"), extraCharges(ec) {}
void Guest::addExtraCharge(double amount) { extraCharges += amount; }
double Guest::getExtraCharges() const { return extraCharges; }
string Guest::toFileString() const {
    return username + "," + to_string(id) + "," + password + "," + usertype + "," + to_string(extraCharges);
}
void Guest::bookRoom(vector<Reservation>& res_list, vector<Room>& r_list, Reservation newRes) {
    res_list.push_back(newRes);
    for (auto& r : r_list) {
        if (r.getRoomNum() == newRes.getRoomNum()) {
            r.setRoomStatus("Booked (Unavailable)");
            break;
        }
    }
}
bool Guest::cancelMyReservation(vector<Reservation>& res_list, vector<Room>& r_list, int resID) {
    for (size_t i = 0; i < res_list.size(); i++) {
        if (res_list[i].getReservationID() == resID && res_list[i].getGuestID() == getid()) {
            for (auto& r : r_list) {
                if (r.getRoomNum() == res_list[i].getRoomNum()) {
                    r.setRoomStatus("Available");
                    break;
                }
            }
            res_list.erase(res_list.begin() + i);
            return true;
        }
    }
    return false;
}
void Guest::bookEvent(vector<EventReservation>& ev_list, EventReservation newEv) {
    ev_list.push_back(newEv);
}
bool Guest::cancelMyEvent(vector<EventReservation>& ev_list, int evID) {
    for (size_t i = 0; i < ev_list.size(); i++) {
        if (ev_list[i].getEventResID() == evID && ev_list[i].getGuestID() == getid()) {
            ev_list.erase(ev_list.begin() + i);
            return true;
        }
    }
    return false;
}