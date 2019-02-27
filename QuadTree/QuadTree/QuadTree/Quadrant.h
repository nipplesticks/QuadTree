#pragma once
#include <vector>
#include <string>
#include "StaticObject.h"
#include <DMath/DMath.h>

class Quadrant
{
public:
	Quadrant();
	Quadrant(const Quadrant & other);
	~Quadrant();

	//void Build(const sf::Vector2f & pos, const sf::Vector2f & size, unsigned int currentLevel, unsigned int maxLevel, std::vector<Quadrant> & quadTree, size_t index);

	void Create(const DM::Vec2f & pos, float size, unsigned int currentLevel, bool isLeaf);
	void Create(float startX, float startY, float size, unsigned int currentLevel, bool isLeaf);

	void AddChild(int index);

	void SetParent(int index);

	const unsigned long int * GetChildren() const;

	long int GetParent() const;

	unsigned int GetNrOfChildren() const;

	const DM::Vec2f & GetMin() const;

	const DM::Vec2f & GetMax() const;

	const unsigned int & GetLevel() const;

	const float & GetSize() const;

	bool IsLeaf() const;

	Quadrant & operator=(const Quadrant & other);

	bool ContainsObjects() const;

	std::string ToString() const;

private:
	DM::Vec2f m_min;
	DM::Vec2f m_max;

	long int m_parent = -1;
	unsigned long int m_children[4] = { 0 };
	unsigned int m_nrOfChildren = 0;

	float m_size;

	unsigned int m_level;

	std::vector<StaticObject> m_staticOBjects;

	bool m_isLeaf;
private:
	void _copy(const Quadrant & other);

};