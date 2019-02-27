#pragma once
#include <DMath/DMath.h>
#include <DirectXCollision.h>

class QuadTree;
class StaticObject
{
public:
	StaticObject() = default;
	~StaticObject() = default;

	bool SetPosition(const DM::Vec3f & position);
	bool SetPosition(float x, float y, float z);

	bool SetSize(const DM::Vec3f & size);
	bool SetSize(float x, float y, float z);
	bool SetSize(float size);

	bool SetRotation(const DM::Vec3f & axis);
	bool SetRotation(float x, float y, float z);

	bool SetBoundingBox(const DirectX::BoundingBox & AABB);
	bool SetBoundingBox(const DirectX::BoundingOrientedBox & OBB);
	bool SetBoundingBox(const DirectX::BoundingSphere & BS);

	const DM::Vec3f & GetPosition() const;
	const DM::Vec3f & GetSize() const;
	const DM::Vec3f & GetRotation() const;

	bool Register(QuadTree * quadTree);
	bool UnRegister();

protected:
	DM::Vec3f m_position;
	DM::Vec3f m_size;
	DM::Vec3f m_rotation;



private:
	int m_registerAddress = -1;
	QuadTree * m_pQuadTree = nullptr;
};