#include "Helper.h"
#include <ctime>
#include <cstdio>

void cleanString(string& str) {
    if (!str.empty() && str.back() == '\r') {
        str.pop_back();
    }
}

int calculateDays(string start, string end) {
    struct tm tm1 = { 0 }, tm2 = { 0 };
    if (sscanf(start.c_str(), "%d-%d-%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year) != 3) return 0;
    if (sscanf(end.c_str(), "%d-%d-%d", &tm2.tm_mday, &tm2.tm_mon, &tm2.tm_year) != 3) return 0;
    tm1.tm_mon -= 1; tm1.tm_year -= 1900;
    tm2.tm_mon -= 1; tm2.tm_year -= 1900;
    tm1.tm_isdst = -1; tm2.tm_isdst = -1;
    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);
    if (t1 == -1 || t2 == -1) return 0;
    double seconds = difftime(t2, t1);
    int days = seconds / (60 * 60 * 24);
    return (days > 0) ? days : 0;
}
bool isValidFutureDate(string dateStr) {
    int d, m, y;
    if (sscanf(dateStr.c_str(), "%d-%d-%d", &d, &m, &y) != 3) return false;

    time_t now = time(0);
    tm* ltm = localtime(&now);
    int curY = 1900 + ltm->tm_year;
    int curM = 1 + ltm->tm_mon;
    int curD = ltm->tm_mday;

    if (y < curY) return false;
    if (y == curY && m < curM) return false;
    if (y == curY && m == curM && d < curD) return false;

    return true;
}