#ifndef UI_H
#define UI_H

#pragma once
#include "ApplicationManager.h"
#include <string>

using namespace std;

class UI {
public:
    static int ProcessCommand(int argc, char* argv[], ApplicationManager& sys);
};

#endif