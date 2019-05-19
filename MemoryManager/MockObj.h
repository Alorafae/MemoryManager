#pragma once

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


