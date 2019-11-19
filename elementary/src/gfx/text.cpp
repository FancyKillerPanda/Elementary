#include "utils/log.h"
#include "gfx/text.h"

namespace el
{

Text::Text(SDL_Renderer* renderer, std::string fontPath, std::string text, unsigned int size, SDL_Color colour)
	: renderer(renderer), fontPath(fontPath), text(text), size(size), colour(colour), texture(renderer)
{
	update(fontPath);
}

void Text::update()
{
	isInitialised = false;
	
	// Destroys the last texture if it exists
	SDL_DestroyTexture(texture.texture);
	texture = nullptr;

	if (!font)
	{
		error("Text requires valid font.");
		return;
	}

	// Creates a surface for the text
	SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, text.c_str(), colour);

	if (!textSurface)
	{
		sdlError("Failed to create surface for text texture (font path: %s).", fontPath.c_str());
		return;
	}

	// Converts the surface to a texture
	// TODO(fkp): Make this a static method in texture
	texture.texture = SDL_CreateTextureFromSurface(renderer, textSurface);

	if (!texture.texture)
	{
		sdlError("Failed to create texture from surface (font path: %s).", fontPath.c_str());
		return;
	}

	// TODO(fkp): Move to texture method
	texture.renderer = renderer;
	if (SDL_QueryTexture(texture.texture, nullptr, nullptr, &texture.rect.w, &texture.rect.h) != 0)
	{
		sdlError("Texture is invalid.");
		return;
	}

	// Frees the temporary surface
	SDL_FreeSurface(textSurface);

	isInitialised = true;
}

void Text::update(std::string path)
{
	fontPath = path;
	
	// Removes the old font if it exists
	if (font)
	{
		TTF_CloseFont(font);
	}
	
	font = TTF_OpenFont(fontPath.c_str(), size);

	if (!font)
	{
		sdlError("Failed to create font (font path: %s).", fontPath.c_str());
		isInitialised = false;

		return;
	}

	update();
}

void Text::draw()
{
	texture.draw();
}

void Text::setPosition(int x, int y)
{
	texture.setPosition(x, y);
}

}
