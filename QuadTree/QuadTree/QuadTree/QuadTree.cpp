#include "QuadTree.h"

QuadTree::QuadTree()
{
}

QuadTree::~QuadTree()
{
}

void QuadTree::BuildTree(unsigned int maxLevel, unsigned int worldSize, const DM::Vec2f & startPos)
{
	m_quadTree.clear();
	m_maximumLevel = maxLevel;
	m_worldSize = worldSize;

	size_t numberOfQuadrants = 0;

	for (unsigned int level = 0; level <= maxLevel; level++)
	{
		numberOfQuadrants += (unsigned int)std::pow(4, level);
	}
	m_quadTree = std::vector<Quadrant>(numberOfQuadrants);

	float size = worldSize;

	Quadrant q;
	q.Create(startPos, size, 0, false);
	size_t index = 0;
	m_quadTree[index++] = q;

	for (unsigned int level = 1; level <= maxLevel; level++)
	{
		bool isLeaf = level == maxLevel;
		float rowCol = (unsigned int)std::pow(2, level);
		size = size * 0.5f;

		for (unsigned int y = 0; y < rowCol; y++)
		{
			DM::Vec2f currentPos = startPos;
			currentPos.y += size * y;

			for (unsigned int x = 0; x < rowCol; x++)
			{
				currentPos.x = startPos.x + size * x;
				q.Create(currentPos, size, level, isLeaf);
				size_t parent = _GetQuadrantIndex(currentPos, level - 1);				
				m_quadTree[index] = q;
				m_quadTree[index].SetParent(parent);
				m_quadTree[parent].AddChild(index++);
			}
		}
	}
}

void QuadTree::BuildTree(unsigned int maxLevel, unsigned int worldSize, float worldStartX, float worldStartY)
{
	BuildTree(maxLevel, worldSize, DM::Vec2f(worldStartX, worldStartY));
}

Quadrant * QuadTree::GetQuadrant(const DM::Vec2f & worldPos, unsigned int level)
{
	if (m_quadTree.empty())
		return nullptr;

	size_t quadrantIndex = _GetQuadrantIndex(worldPos, level);

	return &m_quadTree[quadrantIndex];;
}

Quadrant * QuadTree::GetQuadrantFrom(Quadrant * refQuadrant, Direction dir)
{
	DM::Vec2f searchPos = refQuadrant->GetMin();

	float size = refQuadrant->GetSize() * 1.5f;

	switch (dir)
	{
	case North:
		searchPos.y -= size;
		break;
	case North_East:
		searchPos.y -= size;
		searchPos.x += size;
		break;
	case East:
		searchPos.x += size;
		break;
	case South_East:
		searchPos.y += size;
		searchPos.x += size;
		break;
	case South:
		searchPos.y += size;
		break;
	case South_West:
		searchPos.y += size;
		searchPos.x -= size;
		break;
	case West:
		searchPos.x -= size;
		break;
	case North_West:
		searchPos.y -= size;
		searchPos.x -= size;
		break;

	}

	return GetQuadrant(searchPos, refQuadrant->GetLevel());
}

int QuadTree::RegisterStaticObject(StaticObject * object)
{
	

	return 0;
}

void QuadTree::UnregisterStaticObject(StaticObject * object, int address)
{

}

unsigned int QuadTree::GetWorldSize() const
{
	return m_maximumLevel;
}

unsigned int QuadTree::GetMaxTreeLevel() const
{
	return m_maximumLevel;
}

const std::vector<Quadrant>& QuadTree::GetQuadrantVector() const
{
	return m_quadTree;
}

const Quadrant & QuadTree::operator[](unsigned int index)
{
	return m_quadTree[index];
}

std::string QuadTree::ToString() const
{
	std::string str = "";

	str += "World size: " + std::to_string(m_worldSize) + "\n";
	str += "Maximum level: " + std::to_string(m_maximumLevel) + "\n\n";
	str += "############### QUAD TREE BEGIN ###############\n\n";

	for (int i = 0; i < m_quadTree.size(); i++)
	{
		str += "Index: " + std::to_string(i) + "\n";
		str += m_quadTree[i].ToString() + "\n";
	}

	return str;
}

size_t QuadTree::_GetQuadrantIndex(const DM::Vec2f & worldPos, unsigned int level)
{
	level = level > m_maximumLevel ? m_maximumLevel : level;

	size_t levelStartIndex = 0;
	size_t levelEndIndex = 0;

	for (unsigned int i = 0; i < level; i++)
	{
		levelStartIndex += (unsigned int)std::pow(4, i);
	}

	levelEndIndex = levelStartIndex + (unsigned int)std::pow(4, level);

	float size = m_quadTree[levelStartIndex].GetSize();
	DM::Vec2f searchPos = worldPos;

	DM::Vec2f worldStart = m_quadTree[0].GetMin();
	DM::Vec2f worldEnd = m_quadTree[0].GetMax();

	searchPos.x = searchPos.x < worldStart.x ? worldStart.x : searchPos.x;
	searchPos.y = searchPos.y < worldStart.y ? worldStart.y : searchPos.y;
	searchPos.x = searchPos.x > worldEnd.x ? worldEnd.x : searchPos.x;
	searchPos.y = searchPos.y > worldEnd.y ? worldEnd.y : searchPos.y;

	searchPos -= worldStart;

	DM::Vec2f step = searchPos / size;

	return levelStartIndex + (int)step.x + (int)step.y * (int)std::pow(2, level);
}

