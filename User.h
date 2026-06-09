#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;
class Room;
class Reservation;
class EventReservation;

class User {
protected:
    string username;
    int id;
    string password;
    string usertype;

public:
    User(string u, int i, string p, string ut);
    virtual ~User() {}

    string getusername() const;
    int getid() const;
    string getusertype() const;
    string getpassword() const;

    bool loggin(string us, string pas);
    virtual string toFileString() const;
};

class Receptionist : public User {
public:
    Receptionist(string user, int i, string pass);

    void addRoom(vector<Room>& r_list, Room newroom);
    void updateRoomStat(vector<Room>& r_list, int r_no, string r_stat);
    bool cancelReservation(vector<Reservation>& re_list, vector<Room>& r_list, int resid);
    bool cancelEvent(vector<EventReservation>& ev_list, int evID);
};

class Guest : public User {
private:
    double extraCharges;
public:
    Guest(string user_name, int i, string pass, double ec = 0.0);

    void addExtraCharge(double amount);
    double getExtraCharges() const;

    string toFileString() const override;

    void bookRoom(vector<Reservation>& res_list, vector<Room>& r_list, Reservation newRes);
    bool cancelMyReservation(vector<Reservation>& res_list, vector<Room>& r_list, int resID);
    void bookEvent(vector<EventReservation>& ev_list, EventReservation newEv);
    bool cancelMyEvent(vector<EventReservation>& ev_list, int evID);
};

#endif