#include "QuadTree/QuadTree.h"
#include <iostream>

int main()
{
	QuadTree qt;
	qt.BuildTree(3, 100, DM::Vec2f(-50.0f, -50.0f));

	std::cout << qt.ToString() << std::endl;


	return 0;
}