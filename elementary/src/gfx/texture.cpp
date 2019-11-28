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
	if (isFadingCurrently)
	{
		fadeCurrentDuration = (int) fadeTimer.getElapsed();

		if (fadeCurrentDuration >= fadeTargetDuration)
		{
			// Makes sure the alpha is exactly the target
			SDL_SetTextureAlphaMod(texture, (unsigned char) fadeTargetAlpha);
			isFadingCurrently = false;
		}

		if (isFadingCurrently)
		{
			double portionOfTimeCompleted = (double) fadeCurrentDuration / (double) fadeTargetDuration;
			int fadeAlphaDifference = fadeTargetAlpha - fadeStartAlpha;
			unsigned char newAlpha = (unsigned char) (fadeStartAlpha + (fadeAlphaDifference * portionOfTimeCompleted));

			// Sets the new alpha of the texture
			SDL_SetTextureAlphaMod(texture, newAlpha);
		}
	}

	// Scaling
	if (isScalingCurrently)
	{
		scaleCurrentDuration = (int) scaleTimer.getElapsed();

		if (scaleCurrentDuration >= scaleTargetDuration)
		{
			// Makes sure the rect dimensions are exactly the target
			rect.w = scaleTargetWidth;
			rect.h = scaleTargetHeight;

			isScalingCurrently = false;
		}

		if (isScalingCurrently)
		{
			double portionOfTimeCompleted = (double) scaleCurrentDuration / (double) scaleTargetDuration;
		
			int widthDifference = scaleTargetWidth - scaleStartWidth;
			int heightDifference = scaleTargetHeight - scaleStartHeight;
			rect.w = (int) (scaleStartWidth + (widthDifference * portionOfTimeCompleted));
			rect.h = (int) (scaleStartHeight + (heightDifference * portionOfTimeCompleted));
		}
	}

	// Translation
	if (isTranslatingCurrently)
	{
		translateCurrentDuration = (int) translateTimer.getElapsed();

		if (translateCurrentDuration >= translateTargetDuration)
		{
			// Makes sure the rect positions are exactly the target
			rect.x = translateTargetX;
			rect.y = translateTargetY;

			isTranslatingCurrently = false;
		}

		if (isTranslatingCurrently)
		{
			double portionOfTimeCompleted = (double) translateCurrentDuration / (double) translateTargetDuration;
		
			int xDifference = translateTargetX - translateStartX;
			int yDifference = translateTargetY - translateStartY;
			rect.x = (int) (translateStartX + (xDifference * portionOfTimeCompleted));
			rect.y = (int) (translateStartY + (yDifference * portionOfTimeCompleted));
		}
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

void Texture::fadeIn(int durationMs)
{
	if (SDL_GetTextureAlphaMod(texture, (Uint8*) &fadeStartAlpha) == -1)
	{
		warn("Cannot fade in without valid texture.");
		return;
	}

	isFadingCurrently = true;

	// Sets the starting alpha to 0 if it hasn't been set yet (i.e is at 255)
	if (fadeStartAlpha == 255)
	{
		fadeStartAlpha = 0;
		SDL_SetTextureAlphaMod(texture, 0);
	}

	fadeTargetAlpha = 255;

	fadeCurrentDuration = 0;
	fadeTargetDuration = durationMs;
	fadeTimer.reset();
}

void Texture::fadeOut(int durationMs)
{
	if (SDL_GetTextureAlphaMod(texture, (Uint8*) &fadeStartAlpha) == -1)
	{
		warn("Cannot fade out without valid texture.");
		return;
	}

	isFadingCurrently = true;

	if (fadeStartAlpha == 0)
	{
		fadeStartAlpha = 255;
		SDL_SetTextureAlphaMod(texture, 255);
	}
	
	fadeTargetAlpha = 0;
	
	fadeCurrentDuration = 0;
	fadeTargetDuration = durationMs;
	fadeTimer.reset();
}

void Texture::smoothScale(int newWidth, int newHeight, int durationMs)
{
	if (!texture)
	{
		warn("Cannot size change without valid texture.");
		return;
	}

	isScalingCurrently = true;

	scaleStartWidth = rect.w;
	scaleTargetWidth = newWidth;
	scaleStartHeight = rect.h;
	scaleTargetHeight = newHeight;

	scaleCurrentDuration = 0;
	scaleTargetDuration = durationMs;
	scaleTimer.reset();
}

void Texture::smoothScale(double scaleFactor, int durationMs)
{
	int newWidth = (int) (rect.w * scaleFactor);
	int newHeight = (int) (rect.h * scaleFactor);

	smoothScale(newWidth, newHeight, durationMs);
}

void Texture::smoothTranslate(int newX, int newY, int durationMs)
{
	if (!texture)
	{
		warn("Cannot translate without valid texture.");
		return;
	}

	isTranslatingCurrently = true;

	translateStartX = rect.x;
	translateTargetX = newX;
	translateStartY = rect.y;
	translateTargetY = newY;

	translateCurrentDuration = 0;
	translateTargetDuration = durationMs;
	translateTimer.reset();
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
