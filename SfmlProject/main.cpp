#include "GameManager.h"

int main(int argc, char** argv)
{
	GameManager& gm = GameManager::Get();
	gm.Init(800, 600, "Test");
	gm.Run();

	return 0;
}