#include "utils/log.h"
#include "gfx/texture.h"
#include "animations/fade.h"
#include "animations/scale.h"
#include "animations/translate.h"

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
	for (Animation* animation : animationsQueue)
	{
		delete animation;
		animation = nullptr;
	}
	
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

bool Texture::update()
{
	std::vector<int> indicesToRemove;

	for (int i = 0; i < animationsQueue.size(); i++)
	{
		if (!animationsQueue[i]->update())
		{
			indicesToRemove.push_back(i);
		}
	}

	bool animationFinished = indicesToRemove.size() != 0 ? true : false;

	for (int i : indicesToRemove)
	{
		animationsQueue.erase(animationsQueue.begin() + i);
	}

	return animationFinished;
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
	animationsQueue.push_back(new Fade(this, durationMs, 255));
}

void Texture::fadeOut(int durationMs)
{
	animationsQueue.push_back(new Fade(this, durationMs, 0));
}

void Texture::smoothScale(int durationMs, int newWidth, int newHeight)
{
	animationsQueue.push_back(new Scale(this, durationMs, newWidth, newHeight));
}

void Texture::smoothScale(int durationMs, double scaleFactor)
{
	int newWidth = (int) (rect.w * scaleFactor);
	int newHeight = (int) (rect.h * scaleFactor);

	smoothScale(durationMs, newWidth, newHeight);
}

void Texture::smoothTranslate(int durationMs, int newX, int newY)
{
	animationsQueue.push_back(new Translate(this, durationMs, newX, newY));
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
