#pragma once

#include <stdio.h>

class MockModel
{
  public:
    MockModel();
    MockModel(int x, int y, int z);
    ~MockModel();

    void Update(float dt);
    void Render(float dt);
  private:
    int posx = 0;
    int posy = 0;
    int posz = 0;
};

class MockTexture
{
  public:
    MockTexture();
    ~MockTexture();



  private:
    unsigned sizeX = 0;
    unsigned sizeY = 0;
    unsigned sizeZ = 0;
};

class MockVirtual
{
  public:
    MockVirtual();
    ~MockVirtual();

    virtual void VFunctionTest();
  private:


};

class MockVirtualInherit : MockVirtual
{
  public:
    MockVirtualInherit();
    ~MockVirtualInherit();

    virtual void VFunctionTest();
  private:


};

