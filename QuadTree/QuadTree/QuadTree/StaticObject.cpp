#include "StaticObject.h"
#include "QuadTree.h"
bool StaticObject::SetPosition(const DM::Vec3f & position)
{
	if (m_registerAddress != -1)
		return false;
	
	m_position = position;

	return true;
}

bool StaticObject::SetPosition(float x, float y, float z)
{
	return SetPosition(DM::Vec3f(x, y, z));
}

bool StaticObject::SetSize(const DM::Vec3f & size)
{
	if (m_registerAddress != -1)
		return false;

	m_size = size;

	return true;
}

bool StaticObject::SetSize(float x, float y, float z)
{
	return SetSize(DM::Vec3f(x, y, z));
}

bool StaticObject::SetSize(float size)
{
	return SetSize(DM::Vec3f(size, size, size));
}

bool StaticObject::SetRotation(const DM::Vec3f & axis)
{
	if (m_registerAddress != -1)
		return false;

	m_rotation = axis;

	return true;
}

bool StaticObject::SetRotation(float x, float y, float z)
{
	return SetRotation(DM::Vec3f(x, y, z));
}

bool StaticObject::SetBoundingBox(const DirectX::BoundingBox & AABB)
{
	return false;
}

bool StaticObject::SetBoundingBox(const DirectX::BoundingOrientedBox & OBB)
{
	return false;
}

bool StaticObject::SetBoundingBox(const DirectX::BoundingSphere & BS)
{
	return false;
}

const DM::Vec3f & StaticObject::GetPosition() const
{
	return m_position;
}

const DM::Vec3f & StaticObject::GetSize() const
{
	return m_size;
}

const DM::Vec3f & StaticObject::GetRotation() const
{
	return m_rotation;
}

bool StaticObject::Register(QuadTree * quadTree)
{
	if (m_registerAddress != -1)
		return false;

	m_pQuadTree = quadTree;
	m_pQuadTree->RegisterStaticObject(this);

	return true;
}

bool StaticObject::UnRegister()
{
	if (m_registerAddress == -1)
		return false;

	m_pQuadTree->UnregisterStaticObject(this, m_registerAddress);
	m_pQuadTree = nullptr;
	m_registerAddress = -1;

	return true;
}
