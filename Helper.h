#ifndef HELPER_H
#define HELPER_H
#include <string>
using namespace std;
void cleanString(string& str);
int calculateDays(string start, string end);
bool isValidFutureDate(string dateStr);
struct UserCredentials {
    string username;
    string password;
};

#endif