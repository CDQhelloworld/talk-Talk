#pragma once
#ifndef CONTROL_H
#define CONTROL_H

#include <map>
#include "view.h"
using namespace std;

typedef class control
{
public:
    control();
    ~control();

	void handle(char *buff, int cli_fd);
private:
    map<int,view*> _map;//model
}Control,*PControl;

#endif
