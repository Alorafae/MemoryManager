#include "MockObj.h"

MockModel::MockModel() : posx(0), posy(0), posz(0)
{
}

MockModel::MockModel(int x, int y, int z)
{
}

MockModel::~MockModel()
{
}

void MockModel::Update(float dt)
{
  posx += 1 * dt;
  posy += 1 * dt;
  posz += 1 * dt;
}

void MockModel::Render(float dt)
{

}

MockTexture::MockTexture()
{
}

MockTexture::~MockTexture()
{
}

MockVirtual::MockVirtual()
{
}

MockVirtual::~MockVirtual()
{
}

void MockVirtual::VFunctionTest()
{
  printf("MockVirtual virtual function executed\n");
}

MockVirtualInherit::MockVirtualInherit()
{
}

MockVirtualInherit::~MockVirtualInherit()
{
}

void MockVirtualInherit::VFunctionTest()
{
  printf("MockVirtualInherit virtual function executed\n");
}
