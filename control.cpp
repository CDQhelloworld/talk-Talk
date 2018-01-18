#include <iostream>
#include "control.h"
#include "public.h"

Control::control()
{
	_map.insert(make_pair(MSG_TYPE_REGISTER, new view))
}

Control::~control()
{

}

void Control::handle(char *buff, int cli_fd)
{

}
