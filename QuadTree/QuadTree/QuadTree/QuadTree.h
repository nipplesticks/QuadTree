#pragma once
#include "Quadrant.h"

enum Direction
{
	North		= 0,
	North_East	= 1,
	East		= 2,
	South_East	= 3,
	South		= 4,
	South_West	= 5,
	West		= 6,
	North_West	= 7
};

class QuadTree
{
public:
	QuadTree();
	~QuadTree();

	void BuildTree(unsigned int maxLevel, unsigned int worldSize, const DM::Vec2f & worldStart);
	void BuildTree(unsigned int maxLevel, unsigned int worldSize, float worldStartX, float worldStartY);

	Quadrant * GetQuadrant(const DM::Vec2f & worldPos, unsigned int level);
	
	Quadrant * GetQuadrantFrom(Quadrant * refQuadrant, Direction dir);

	int RegisterStaticObject(StaticObject * object);
	void UnregisterStaticObject(StaticObject * object, int address);

	unsigned int GetWorldSize() const;
	unsigned int GetMaxTreeLevel() const;

	const std::vector<Quadrant> & GetQuadrantVector() const;

	const Quadrant & operator[](unsigned int index);

	std::string ToString() const;

private:
	std::vector<Quadrant> m_quadTree;
	unsigned int m_worldSize;
	unsigned int m_maximumLevel;

private:
	size_t _GetQuadrantIndex(const DM::Vec2f & worldPos, unsigned int level);
};

