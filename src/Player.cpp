#include "Player.h"
#include <cmath>
#include "TextureHolder.h"
Player::Player() {
  m_speed = START_SPEED;
  m_Health = START_HEALTH;
  m_MaxHealth = START_HEALTH;

  //!!watch this space!!
  m_sprite.setTexture(TextureHolder::GetTexture("recources/graphics/player.png"));
  m_sprite.setOrigin(25, 25);
}
void Player::spawn(IntRect arena, Vector2f resolution, int tileSize) {
  m_position.x = arena.width / 2;
  m_position.y = arena.height / 2;
  m_Arena.left = arena.left;
  m_Arena.width = arena.width;
  m_Arena.top = arena.top;
  m_Arena.height = arena.height;
  m_TileSize = tileSize;
  m_Resolution.x = resolution.x;
  m_Resolution.y = resolution.y;
}

void Player::resetPlayerStats() {
  m_speed = START_SPEED;
  m_Health = START_HEALTH;
  m_MaxHealth = START_HEALTH;
}

Time Player::getLastHitTime() { return m_LastHit; }
bool Player::hit(Time timeHit) {
  if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200) {
    m_LastHit = timeHit;
    m_Health -= 10;
    return true;
  } else {
    return false;
  }
}

FloatRect Player ::getPosition() { return m_sprite.getGlobalBounds(); }
Vector2f Player::getCenter() { return m_position; }
float Player::getRotation() { return m_sprite.getRotation(); }
Sprite Player::getSprite() { return m_sprite; }
int Player::getHealth() { return m_Health; }

void Player::moveLeft() { m_LeftPressed = true; }
void Player::moveRight() { m_RightPressed = true; }
void Player::moveUp() { m_UpPressed = true; }
void Player::moveDown() { m_DownPressed = true; }
void Player::stopLeft() { m_LeftPressed = false; }
void Player::stopRight() { m_RightPressed = false; }
void Player::stopUp() { m_UpPressed = false; }
void Player::stopDown() { m_DownPressed = false; }
void Player::update(float elapsedTime, Vector2i mousePosition) {
  if (m_UpPressed) {
    m_position.y -= m_speed * elapsedTime;
  }
  if (m_DownPressed) {
    m_position.y += m_speed * elapsedTime;
  }
  if (m_RightPressed) {
    m_position.x += m_speed * elapsedTime;
  }
  if (m_LeftPressed) {
    m_position.x -= m_speed * elapsedTime;
  }
  m_sprite.setPosition(m_position);

  // keep the player in the arena
  if (m_position.x > m_Arena.width - m_TileSize) {
    m_position.x = m_Arena.width - m_TileSize;
  }
  if (m_position.x < m_Arena.left + m_TileSize) {
    m_position.x = m_Arena.left + m_TileSize;
  }
  if (m_position.y > m_Arena.height - m_TileSize) {
    m_position.y = m_Arena.height - m_TileSize;
  }
  if (m_position.y < m_Arena.top + m_TileSize) {
    m_position.y = m_Arena.top + m_TileSize;
  }

  float angle = (atan2(mousePosition.y - m_Resolution.y / 2,
                       mousePosition.x - m_Resolution.x / 2) *
                 180) /3.141;

  m_sprite.setRotation(angle);
}

void Player::upgradeSpeed() { m_speed += (START_SPEED * .2); }

void Player::upgradeHealth() { m_MaxHealth += (START_HEALTH * .2); }

void Player::increaseHealthLevel(int amount) {
  m_Health += amount;
  if (m_Health > m_MaxHealth) {
    m_Health = m_MaxHealth;
  }
}