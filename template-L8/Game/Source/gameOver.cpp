#include "gameOver.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Log.h"
#include "Defs.h"
#include "Score.h"
#include "SDL/include/SDL.h"

gameOver::gameOver() : Module() {
}

gameOver::~gameOver() {
}

bool gameOver::Start() {
    _gameOverText = app->tex->Load("Assets/Textures/Game_Over.png");
    return true;
}

bool gameOver::Update() {
    return true;
}

bool gameOver::PostUpdate() {
    //DrawGameOver();
    return true;
}

bool gameOver::CleanUp() {
    if (_gameOverText != nullptr) {
        app->tex->UnLoad(_gameOverText);
        _gameOverText = nullptr;
    }
    return true;
}

void gameOver::DrawGameOver() {

    int screenWidth = 2400;
    int screenHeight = 2400;
    int textWidth = 100;
    int textHeight = 50;

    SDL_Rect fullScreenRect = { 0, 0, screenWidth, screenHeight };  // Asume que tu pantalla es de 1280x720
    SDL_SetRenderDrawColor(app->render->renderer, 0, 0, 0, 255);  // Establece el color de dibujo en negro
    SDL_RenderFillRect(app->render->renderer, &fullScreenRect);  // Dibuja un rectángulo que cubre toda la pantalla

    app->render->DrawTexture(_gameOverText, 700, 400);
}
