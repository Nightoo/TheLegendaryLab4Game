#include "Game/Application.hpp"
#include "Game/State/SelectLevelState.hpp"

int main()
{
    Application(new SelectLevelState(nullptr)).run();
}
