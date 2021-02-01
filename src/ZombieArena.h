#pragma once
#include "Zombie.h"
#include <SFML/Graphics.hpp>
using namespace sf;
int createBackground(VertexArray& rVa,IntRect arena);
Zombie* createHorde(int numZombies,IntRect arena);