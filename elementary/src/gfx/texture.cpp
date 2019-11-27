#include "utils/log.h"
#include "gfx/texture.h"

namespace el
{

Texture::Texture(SDL_Renderer* renderer)
	: renderer(renderer)
{
}

Texture::Texture(SDL_Renderer* renderer, std::string filepath)
	: renderer(renderer), filepath(filepath)
{
	texture = IMG_LoadTexture(renderer, filepath.c_str());

	if (!texture)
	{
		sdlError("Failed to create texture (filepath: %s).", filepath.c_str());
		return;
	}

	if (SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h) != 0)
	{
		sdlError("Texture is invalid (filepath: %s).", filepath.c_str());
		return;
	}

	isInitialised = true;
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

void Texture::convertFromSurface(SDL_Surface* surfaceToConvertFrom)
{
	if (texture)
	{
		SDL_DestroyTexture(texture);

		texture = nullptr;
		filepath = "";
	}

	isInitialised = false;
	texture = SDL_CreateTextureFromSurface(renderer, surfaceToConvertFrom);

	if (!texture)
	{
		sdlError("Failed to create texture from surface.");
		return;
	}

	if (SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h) != 0)
	{
		sdlError("Texture is invalid.");
		return;
	}

	isInitialised = true;
}

void Texture::update()
{
	// Fades
	if (currentlyFading)
	{
		currentFadeDuration = (int) fadeTimer.getElapsed();

		if (currentFadeDuration >= targetFadeDuration)
		{
			// Makes sure the alpha is exactly the target
			SDL_SetTextureAlphaMod(texture, (unsigned char) targetFadeAlpha);
			currentlyFading = false;

			return;
		}

		double portionOfTimeCompleted = (double) currentFadeDuration / (double) targetFadeDuration;
		int fadeAlphaDifference = targetFadeAlpha - startFadeAlpha;
		unsigned char newAlpha = (unsigned char) (startFadeAlpha + (fadeAlphaDifference * portionOfTimeCompleted));

		// Sets the new alpha of the texture
		SDL_SetTextureAlphaMod(texture, newAlpha);
	}
}

void Texture::draw()
{
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

bool Texture::handleEvent(const SDL_Event& event)
{
	if (!isClickable)
	{
		return false;
	}

	lastClickState = currentClickState;
	
	switch (event.type)
	{
		case SDL_MOUSEMOTION:
		{
			SDL_Point mousePos = { event.button.x, event.button.y };

			if (SDL_PointInRect(&mousePos, &rect))
			{
				currentClickState = TextureClickState::Hover;
			}
			else
			{
				currentClickState = TextureClickState::None;
			}
		} break;
		
		case SDL_MOUSEBUTTONDOWN:
		{
			SDL_Point mousePos = { event.button.x, event.button.y };

			if (SDL_PointInRect(&mousePos, &rect))
			{
				// Button pressed
				currentClickState = TextureClickState::Pressed;
			}
		} break;
		
		case SDL_MOUSEBUTTONUP:
		{
			SDL_Point mousePos = { event.button.x, event.button.y };

			if (SDL_PointInRect(&mousePos, &rect))
			{
				// Button clicked
				currentClickState = TextureClickState::Clicked;
			}
		} break;
	}

	return lastClickState != currentClickState;
}

void Texture::fadeOut(int durationMs)
{
	currentlyFading = true;

	// TODO(fkp): Get start alpha
	// SDL_GetTextureAlphaMod(texture, (Uint8*) &startFadeAlpha);
	startFadeAlpha = 255;
	targetFadeAlpha = 0;
	
	currentFadeDuration = 0;
	targetFadeDuration = durationMs;
	fadeTimer.reset();
}

void Texture::setTopLeft(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Texture::setCenter(int x, int y)
{
	rect.x = x - (rect.w / 2);
	rect.y = y - (rect.h / 2);
}

void Texture::setRect(int x, int y, int width, int height)
{
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
}

SDL_Point Texture::getCenter()
{
	return SDL_Point { rect.x + (rect.w / 2), rect.y + (rect.h / 2) };
}

}
