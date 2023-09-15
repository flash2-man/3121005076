#include "Chesis.h"
int main(int argc, char* argv[])
{
	ChesisCheck chesischeck(argv[1], argv[2], argv[3]);
	chesischeck.Init(argc, argv,true);
	chesischeck.Start(true);

	return 0;
}