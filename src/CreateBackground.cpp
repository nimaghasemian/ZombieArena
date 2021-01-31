#include "ZombieArena.h"
using namespace sf;

int createBackground(VertexArray& rVa,IntRect arena){
      const int TILE_SIZE = 50;
      const int TILE_TYPE = 3;
      const int VERTS_IN_QUAD = 4;

      int worldWidth =  arena.width / TILE_SIZE; 
      int worldHeight = arena.height / TILE_SIZE;

      rVa.setPrimitiveType(Quads);
      rVa.resize(worldHeight * worldWidth * VERTS_IN_QUAD);
      int currentVertex = 0;
      for (int w = 0; w < worldWidth; w++)
      {
          for (int h = 0; h < worldHeight; h++)
          {
              //position each Vertex in the current quad
              rVa[currentVertex + 0].position = 
                            Vector2f(w * TILE_SIZE,h*TILE_SIZE);
              
              rVa[currentVertex + 1].position = 
                            Vector2f((w * TILE_SIZE) + TILE_SIZE ,h*TILE_SIZE);
                            
              rVa[currentVertex + 2].position = 
                            Vector2f((w * TILE_SIZE) + TILE_SIZE,(h*TILE_SIZE) + TILE_SIZE);

                rVa[currentVertex + 3].position = 
                            Vector2f(w * TILE_SIZE,(h*TILE_SIZE) + TILE_SIZE);
              
              // Define the positio int the texture for current quad
              if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth-1)
              {
                  rVa[currentVertex + 0].texCoords = Vector2f(0, 0 + TILE_TYPE * TILE_SIZE);
                  rVa[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + TILE_TYPE * TILE_SIZE);
                  rVa[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPE * TILE_SIZE);
                  rVa[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + TILE_TYPE * TILE_SIZE);                  
              } else{
                    srand((int) time(0) + h * w - h);
                    int mOrG = rand() % TILE_TYPE;
                    int verticalOffset = mOrG * TILE_SIZE;
                    rVa [currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
                    rVa [currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
                    rVa [currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
                    rVa [currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
              }
              
              
              currentVertex = currentVertex + VERTS_IN_QUAD;
          }
          
      }
      
      return TILE_SIZE;
}