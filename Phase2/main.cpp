#include "Manager.h"
int main()
{
	Manager *manager = new Manager();
	manager->run();
	delete manager;
}
