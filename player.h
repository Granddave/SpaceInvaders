#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "input.h"

class Player : public Entity
{
public:
    Player(Graphics& graphics, const std::string& filePath,
           int srcX, int srcY, int width, int height,
           float posX, float posY, Vec2f speed);
    ~Player();

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void stopMoving();

    void update(int ms) override;
    void draw(Graphics &graphics) override;

    void handleInput(Input& input);

};

#endif // PLAYER_H
