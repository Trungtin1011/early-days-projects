#include "Server.h"
int main()
{
	Server web("0.0.0.0", 5500);

	if (web.init() != 0) return 0;

	system("pause");
	return 0;
}