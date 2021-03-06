#include "Player.h"
#include "ZombieArena.h"
#include "TextureHolder.h"
#include "Zombie.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
int main() {

  TextureHolder holder;
  enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };

  State state = State::GAME_OVER;

  // Get the screen Resolution and create an smf window
  Vector2f resolution;
  resolution.x = VideoMode::getDesktopMode().width;
  resolution.y = VideoMode::getDesktopMode().height;

  RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena",
                      Style::Fullscreen);

  View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

  Clock clock;
  Time gameTimeTotal;

  Vector2f mouseWorldPosition;
  Vector2i mouseScreenPosition;

  Player player;
  VertexArray background;
  Texture backgroundTex =
  TextureHolder::GetTexture("recources/graphics/background_sheet.png");
  IntRect arena;

  //prepare for horde of zombies
  int numZombies;
  int numZombiesAlive;
  Zombie* zombies = nullptr;

  //*****Bullets*******
  Bullet bullets[100];
  int currentBullet =0;
  int bulletsSpare = 26;
  int bulletsInClip = 6;
  int clipSize = 6;
  float fireRate = 1;
  Time lastPressed;

  //*******Crosshair********
  window.setMouseCursorVisible(false);
  Sprite spriteCrosshair;
  Texture textureCrosshair = TextureHolder::GetTexture("recources/graphics/crosshair.png");
  spriteCrosshair.setTexture(textureCrosshair);
  spriteCrosshair.setOrigin(25,25);

  // the main game loop
  while (window.isOpen()) {
    /*
    *************
    Handle input
    *************
    */

    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Return && state == State::PLAYING) {
          state = State::PAUSED;
        } else if (event.key.code == Keyboard::Return &&
                   state == State::PAUSED) {
          state = State::PLAYING;
          clock.restart();
        } else if (event.key.code == Keyboard::Return &&
                   state == State::GAME_OVER) {
          state = State::LEVELING_UP;
        }
        if (state == State::PLAYING) {
          if (event.key.code == Keyboard ::R){
            if (bulletsSpare >= clipSize){
              bulletsInClip = clipSize;
              bulletsSpare  -= clipSize;
            }else if (bulletsSpare > 0){
              bulletsInClip = bulletsSpare;
              bulletsSpare = 0;
            }else{

            }
          }
        }
      }
    } // end event polling
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
    }
    // Handle WASD while playing
    if (state == State::PLAYING) {
      if (Keyboard::isKeyPressed(Keyboard::W)) {
        player.moveUp();
      } else {
        player.stopUp();
      }
      if (Keyboard::isKeyPressed(Keyboard::S)) {
        player.moveDown();
      } else {
        player.stopDown();
      }
      if (Keyboard::isKeyPressed(Keyboard::D)) {
        player.moveRight();
      } else {
        player.stopRight();
      }
      if (Keyboard::isKeyPressed(Keyboard::A)) {
        player.moveLeft();
      } else {
        player.stopLeft();
      }
      if (Mouse::isButtonPressed(sf::Mouse::Left)){
        if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000/fireRate && bulletsInClip > 0 )
        {
          bullets[currentBullet].shoot(player.getCenter().x,player.getCenter().y,mouseWorldPosition.x,mouseWorldPosition.y);
          currentBullet++;
          if (currentBullet>99)
          {
            currentBullet = 0;
          }
          
          lastPressed = gameTimeTotal;
          bulletsInClip--;
        }
        
      }
    } // end WSAD playing
    // Handle the leveling up state
    if (state == State::LEVELING_UP) {
    
      if (event.key.code == Keyboard::Num1) {
        state = State::PLAYING;
      }
      if (event.key.code == Keyboard::Num2) {
        state = State::PLAYING;
      }
      if (event.key.code == Keyboard::Num3) {
        state = State::PLAYING;
      }
      if (event.key.code == Keyboard::Num4) {
        state = State::PLAYING;
      }
      if (event.key.code == Keyboard::Num5) {
        state = State::PLAYING;
      }
      if (event.key.code == Keyboard::Num6) {
        state = State::PLAYING;
      }

      if (state == State::PLAYING) {
        // prepare the level
        arena.width = 500;
        arena.height = 500;
        arena.left = 0;
        arena.top = 0;
        int tileSize = createBackground(background,arena);
        player.spawn(arena, resolution, tileSize);
        numZombies = 10;
        delete[] zombies;
        zombies = createHorde(numZombies,arena);
        numZombiesAlive = numZombies;
        clock.restart();
      }
    } // end leveling up
    /*
    *******************
    UPDATE THE FRAME
    *******************
    */
    if (state == State::PLAYING) {
      Time dt = clock.restart();
      gameTimeTotal += dt;

      float dtAsSeconds = dt.asSeconds();
      mouseScreenPosition = Mouse::getPosition();
      // convert Mouse position to world coordinates of mainView
      mouseWorldPosition =
          window.mapPixelToCoords(Mouse::getPosition(), mainView);
          //set the crosshair to mouse position
        spriteCrosshair.setPosition(mouseWorldPosition);
      // update the player
      player.update(dtAsSeconds, Mouse::getPosition());
      Vector2f playerPosition(player.getCenter());
      mainView.setCenter(player.getCenter());
      //loop through each zombie and update them
      for (int i = 0; i < numZombies; i++)
      {
        if(zombies[i].isAlive()){
          zombies[i].update(dtAsSeconds,playerPosition);
        }
      }

      for (int  i = 0; i < 100; i++)
      {
          if (bullets[i].isInFlight()){
            bullets[i].update(dtAsSeconds);
          }
      }
      
      
    } // end updating the scene
    /*
    *****************
    Draw the scene
    *****************
    */
    if (state == State::PLAYING) {
      window.clear();
      window.setView(mainView);
      window.draw(background,&backgroundTex);
      //draw the zombies in a loop
      for (int i = 0; i < numZombies; i++)
      {
        window.draw(zombies[i].getSprite());
      }
      for (int i = 0; i < 100; i++)
      {
        if (bullets[i].isInFlight()){
          window.draw(bullets[i].getShape());
        }
      }
      
  
      window.draw(player.getSprite());
      window.draw(spriteCrosshair);
    }
    if (state == State::LEVELING_UP) {
    }
    if (state == State::PAUSED) {
    }
    if (state == State::GAME_OVER) {
    }
    window.display();

  } // end game loop
  delete[] zombies;
}