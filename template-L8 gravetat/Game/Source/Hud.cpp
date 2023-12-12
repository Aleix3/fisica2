#include "Hud.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Input.h"
#include "Player.h"
#include "Log.h"
#include "Defs.h"

Hud::Hud() : Module() {

}

Hud::~Hud() {
	// Destructor
}

bool Hud::Start() {
	// Inicializa las variables de puntuación	
	sizeVector = LoadVector();
	LOG("Loading HUD textures");
	bool ret = true;
	textureFont = app->tex->Load("Assets/Textures/Font.png");

	return ret;
}

bool Hud::Update()
{
	bool ret = true;
	return ret;
}

bool Hud::PostUpdate() {
	bool ret = true;
	return ret;
}

bool Hud::CleanUp()
{
	return true;
}

int Hud::PosLetter(char leterToSearch) {

	char upperLetter = static_cast<char>(toupper(leterToSearch)); //  Converts the letter to uppercase

	for (int i = 0; i < sizeVector; i++)
	{
		if (vectorABC[i].lletra == upperLetter)
		{
			return i;
		}
	}
	return 0;
}

int Hud::LoadVector() {

	vectorABC.push_back({ '1', 0 });
	vectorABC.push_back({ '2', 1 });
	vectorABC.push_back({ '3', 2 });
	vectorABC.push_back({ '4', 3 });
	vectorABC.push_back({ '5', 4 });
	vectorABC.push_back({ '6', 5 });
	vectorABC.push_back({ '7', 6 });
	vectorABC.push_back({ '8', 7 });
	vectorABC.push_back({ '9', 8 });
	vectorABC.push_back({ '0', 9 });
	vectorABC.push_back({ 'A', 10 });
	vectorABC.push_back({ 'B', 11 });
	vectorABC.push_back({ 'C', 12 });
	vectorABC.push_back({ 'D', 13 });
	vectorABC.push_back({ 'E', 14 });
	vectorABC.push_back({ 'F', 15 });
	vectorABC.push_back({ 'G', 16 });
	vectorABC.push_back({ 'H', 17 });
	vectorABC.push_back({ 'I', 18 });
	vectorABC.push_back({ 'J', 19 });
	vectorABC.push_back({ 'L', 20 });
	vectorABC.push_back({ 'M', 21 });
	vectorABC.push_back({ 'O', 22 });
	vectorABC.push_back({ 'P', 23 });
	vectorABC.push_back({ 'R', 24 });
	vectorABC.push_back({ 'S', 25 });
	vectorABC.push_back({ 'T', 26 });
	vectorABC.push_back({ 'U', 27 });
	vectorABC.push_back({ 'V', 28 });
	vectorABC.push_back({ 'W', 29 });

	return vectorABC.size();
}

void Hud::PaintSentence(std::string sentenceToPaint, iPoint positionToPaint) {
	int size = sentenceToPaint.size();
	int writedLetters = 0;
	std::vector<int> posicions;
	SDL_Rect cutFont = { 0, 0, 15, 29 };

	for (int i = 0; i < size; i++)
	{
		posicions.push_back(PosLetter(sentenceToPaint[i]));
	}

	for (int i = 0; i < size; i++)
	{
		cutFont.x = widthLetter * posicions[i];
		app->render->DrawTexture(textureFont, positionToPaint.x + (writedLetters * widthLetter), positionToPaint.y, &cutFont);
		writedLetters++;
	}

}
