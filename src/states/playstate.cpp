#include "states/playstate.h"
#include "states/pausestate.h"
#include "utils/utils.h"

#include <iostream>

#define PLAYER_SPEED 100
PlayState PlayState::m_PlayState;

void PlayState::init(Graphics *graphics)
{
    m_Graphics = graphics;

    m_Player = new Player(m_Graphics);
    m_PlayerBullets.reserve(2);

    // Box2D
    b2Vec2 gravity(0.0f, -10.0f);
    m_World = new b2World(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(8.0f, 0.0f);
    m_GroundBody = m_World->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(8.0f, 0.5f);
    m_GroundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(8.0f, 8.0f);
    m_Body = m_World->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.5f, 0.5f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    fixtureDef.density = 3.0f;
    fixtureDef.friction = 0.3f;
    m_Body->CreateFixture(&fixtureDef);
    //m_Body->SetLinearDamping(1.5f);
}

void PlayState::clean()
{
    delete m_Player;
    delete m_World;
}

void PlayState::pause()
{
    std::cout << "Play state paused" << std::endl;
}

void PlayState::resume()
{
    std::cout << "Play state resumed" << std::endl;
    m_Input.clearAll();
}

void PlayState::handleEvents(Game *game)
{
    SDL_Event event;
    m_Input.beginNewFrame();
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            game->quit();
        break;

        case SDL_KEYDOWN:
            m_Input.keyDownEvent(event);
        break;

        case SDL_KEYUP:
            m_Input.keyUpEvent(event);
        break;

        case SDL_MOUSEBUTTONDOWN:
            m_Input.mouseDownEvent(event);
        break;

        case SDL_MOUSEBUTTONUP:
            m_Input.mouseUpEvent(event);
        break;

        default:
        break;
        }
    }

    if(m_Input.wasKeyPressed(SDL_SCANCODE_P))
        game->pushState(PauseState::instance());
    else if(m_Input.wasKeyPressed(SDL_SCANCODE_E))
        m_Enemies.push_back(Enemy(m_Graphics, 800, 500));
    else if(m_Input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
        game->quit();

    // Temp
    if(m_Input.isKeyHeld(SDL_SCANCODE_W))
        m_Body->ApplyForce(b2Vec2(0, PLAYER_SPEED), m_Body->GetWorldCenter(), true);
    else if(m_Input.isKeyHeld(SDL_SCANCODE_S))
        m_Body->ApplyForce(b2Vec2(0, -PLAYER_SPEED), m_Body->GetWorldCenter(), true);
    if(m_Input.isKeyHeld(SDL_SCANCODE_D))
        m_Body->ApplyForce(b2Vec2(PLAYER_SPEED, 0), m_Body->GetWorldCenter(), true);
    else if(m_Input.isKeyHeld(SDL_SCANCODE_A))
        m_Body->ApplyForce(b2Vec2(-PLAYER_SPEED, 0), m_Body->GetWorldCenter(), true);
    // Temp

    m_Player->handleInput(m_Input);
}

void PlayState::update(Game *game, int ms)
{
    NOT_USED(game);

    m_World->Step((float)(ms)/1000, 6, 2);

    // Temp
    b2Vec2 pos = m_Body->GetPosition();
    //std::cout << pos.x << ", " << pos.y << std::endl;
    pos = worldToPixel(pos);
    m_Player->setPos(pos.x, pos.y);
    // Temp

    for(Enemy& e: m_Enemies)
        e.update(ms);

    for(Bullet& b: m_PlayerBullets)
        b.update(ms);
    if (m_Player->isShooting())
    {
        Vector2 pos = m_Player->shootingPos();
        m_PlayerBullets.push_back(Bullet(m_Graphics, pos.X, pos.Y,
                                         m_Player->damage(),
                                         m_Player->shootingVec()));
    }

    // Clear deletable bullets
    for(size_t i = 0; i < m_PlayerBullets.size(); i++)
    {
        if (m_PlayerBullets.at(i).deleteLater())
        {
            m_PlayerBullets.erase(m_PlayerBullets.begin() + i);
            std::cout << "Bullets: " << m_PlayerBullets.size() << std::endl;
        }
    }

    m_Player->update(ms);
}

void PlayState::draw()
{
    // Temp
    b2Vec2 pos = worldToPixel(m_Body->GetPosition());
    SDL_Rect r({(int)pos.x, (int)pos.y,40,40});
    SDL_SetRenderDrawColor(m_Graphics->getRenderer(), 255,255,255,255);
    SDL_RenderDrawRect(m_Graphics->getRenderer(), &r);
    //r = {m_GroundBody->x,m_GroundBody->y, m_GroundBody->};
    //SDL_RenderDrawRect(m_Graphics->getRenderer(), &r);
    SDL_SetRenderDrawColor(m_Graphics->getRenderer(), 0,0,0,255);
    m_Player->draw(m_Graphics);
    // Temp


    for(Bullet& b: m_PlayerBullets)
        b.draw(m_Graphics);
    for(Enemy& e: m_Enemies)
        e.draw(m_Graphics);
}
