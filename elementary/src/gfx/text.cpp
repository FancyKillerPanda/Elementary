#include "utils/log.h"
#include "gfx/text.h"

namespace el
{

Text::Text(SDL_Renderer* renderer, std::string fontPath, std::string text, unsigned int size, SDL_Color colour)
	: renderer(renderer), fontPath(fontPath), text(text), size(size),
	  currentColour(colour), baseColour(colour), hoverColour(colour), pressedColour(colour),
	  texture()
{
	update(fontPath);
}

void Text::update()
{
	isInitialised = false;
	
	// Destroys the last texture if it exists
	SDL_DestroyTexture(texture.texture);
	texture.texture = nullptr;

	if (!font)
	{
		error("Text requires valid font.");
		return;
	}

	// Creates a surface for the text
	SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, text.c_str(), currentColour);

	if (!textSurface)
	{
		sdlError("Failed to create surface for text texture (font path: %s).", fontPath.c_str());
		return;
	}

	// Converts the surface to a texture for rendering
	texture.convertFromSurface(renderer, textSurface);

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
	if (!isInitialised)
	{
		return;
	}

	texture.draw();
}

bool Text::handleEvent(const SDL_Event& event)
{
	if (!isInitialised)
	{
		return false;
	}

	if (texture.handleEvent(event))
	{
		switch (texture.currentClickState)
		{
			case el::TextureClickState::None:
			{
				currentColour = baseColour;
				update();
			} break;

			case el::TextureClickState::Hover:
			{
				currentColour = hoverColour;
				update();
			} break;

			case el::TextureClickState::Pressed:
			{
				currentColour = pressedColour;
				update();
			} break;

			case el::TextureClickState::Clicked:
			{
				// Mouse will still be over the text, so hover colour
				// is used instead of base colour
				currentColour = hoverColour;
				update();
				
				return true;
			} break;

			default:
			{
				warn("Unknown TextureClickState in Text::handleEvent().");
			} break;
		}
	}

	return false;
}

void Text::setTopLeft(int x, int y)
{
	texture.setTopLeft(x, y);
}

void Text::setCenter(int x, int y)
{
	texture.setCenter(x, y);
}

void Text::setColourValues(SDL_Color p_BaseColour, SDL_Color p_HoverColour, SDL_Color p_PressedColour)
{
	baseColour = p_BaseColour;
	hoverColour = p_HoverColour;
	pressedColour = p_PressedColour;
}

void Text::setIsClickable(bool value)
{
	texture.isClickable = value;
}

}
