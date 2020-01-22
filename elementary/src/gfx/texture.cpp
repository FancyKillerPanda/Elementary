#include "utils/log.h"
#include "utils/sdl_compare.h"
#include "gfx/texture.h"
#include "animations/fade.h"
#include "animations/scale.h"
#include "animations/translate.h"

namespace el
{

std::unordered_map<SDL_Texture*, unsigned int> Texture::s_TextureCountMap = {};

Texture::Texture(SDL_Renderer* renderer, std::string filepath)
	: renderer(renderer), filepath(filepath)
{
	texture = IMG_LoadTexture(renderer, filepath.c_str());

	if (handleTextureCreationChecks())
	{
		isInitialised = true;
	}
}

Texture::Texture(const Texture& from)
	: isInitialised(from.isInitialised), renderer(from.renderer),
	  filepath(from.filepath), rect(from.rect),
	  rotation(from.rotation),
	  isClickable(from.isClickable), currentClickState(from.currentClickState), lastClickState(from.lastClickState),
	  textureSubRect(from.textureSubRect)
{
	if (from.texture)
	{
		texture = from.texture;
		
		if (!handleTextureCreationChecks()) // This will increment s_TextureCountMap[texture]
		{
			error("Copied texture was invalidated.\n");
		}
	}
}

Texture& Texture::operator=(Texture from)
{
	swap(*this, from);	
	return *this;
}

Texture::Texture(Texture&& from)
	: Texture()
{
	swap(*this, from);
}

Texture::~Texture()
{
	// TODO(fkp): Handle better deletion (like SDL_Texture)
	for (Animation* animation : animationsRunning)
	{
		delete animation;
		animation = nullptr;
	}

	if (texture)
	{
		s_TextureCountMap[texture] -= 1;

		if (s_TextureCountMap[texture] == 0)
		{
			// There are no references to this left
			SDL_DestroyTexture(texture);
		}
	}
}

void Texture::convertFromSurface(SDL_Renderer* p_Renderer, SDL_Surface* surfaceToConvertFrom)
{
	renderer = p_Renderer;
	
	if (texture)
	{
		SDL_DestroyTexture(texture);

		texture = nullptr;
		filepath = "";
	}

	isInitialised = false;
	texture = SDL_CreateTextureFromSurface(renderer, surfaceToConvertFrom);

	if (handleTextureCreationChecks())
	{
		isInitialised = true;
	}
}

void swap(Texture& first, Texture& second)
{
	std::swap(first.isInitialised, second.isInitialised);

	std::swap(first.renderer, second.renderer);
	std::swap(first.filepath, second.filepath);
	std::swap(first.texture, second.texture);

	std::swap(first.rect, second.rect);
	std::swap(first.rotation, second.rotation);

	std::swap(first.isClickable, second.isClickable);
	std::swap(first.currentClickState, second.currentClickState);
	std::swap(first.lastClickState, second.lastClickState);

	std::swap(first.isFadingCurrently, second.isFadingCurrently);
	std::swap(first.isScalingCurrently, second.isScalingCurrently);
	std::swap(first.isTranslatingCurrently, second.isTranslatingCurrently);
	std::swap(first.animationsRunning, second.animationsRunning);

	std::swap(first.textureSubRect, second.textureSubRect);
}

bool Texture::handleTextureCreationChecks()
{
	if (!texture)
	{
		sdlError("Failed to create texture (filepath: %s).", filepath.c_str());
		return false;
	}

	SDL_Rect oldRect = rect;

	if (SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h) != 0)
	{
		sdlError("Texture is invalid (filepath: %s).", filepath.c_str());
		return false;
	}

	if (textureSubRect == SDL_Rect { 0, 0, 0, 0 } ||
		textureSubRect == SDL_Rect { 0, 0, oldRect.w, oldRect.h })
	{
		textureSubRect = { 0, 0, rect.w, rect.h };
	}

	s_TextureCountMap[texture] += 1;
	return true;
}
	
bool Texture::update()
{
	if (!isInitialised)
	{
		return false;
	}

	std::vector<int> indicesToRemove;

	for (int i = 0; i < animationsRunning.size(); i++)
	{
		if (!animationsRunning[i]->update())
		{
			indicesToRemove.push_back(i);
		}
	}

	bool animationFinished = indicesToRemove.size() != 0 ? true : false;

	for (int i : indicesToRemove)
	{
		animationsRunning.erase(animationsRunning.begin() + i);
	}

	return animationFinished;
}

void Texture::draw()
{
	if (!isInitialised)
	{
		return;
	}

	SDL_RenderCopyEx(renderer, texture, &textureSubRect, &rect, rotation, nullptr, SDL_FLIP_NONE);
}

bool Texture::handleEvent(const SDL_Event& event)
{
	if (!isInitialised)
	{
		return false;
	}

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

void Texture::animate(Animation* animation)
{
	animationsRunning.push_back(animation);
}

void Texture::animate(Animation* animationToDo, Animation* executeAfter)
{
	animate(animationToDo);
	executeAfter->animationsToExecuteAfter.push_back(animationToDo);
}


void Texture::fadeIn(int durationMs, int waitDurationMs)
{
	animationsRunning.push_back(new Fade(this, durationMs, 255, true, waitDurationMs));
}

void Texture::fadeOut(int durationMs, int waitDurationMs)
{
	animationsRunning.push_back(new Fade(this, durationMs, 0, true, waitDurationMs));
}

void Texture::smoothScale(int durationMs, int newWidth, int newHeight, int waitDurationMs)
{
	animationsRunning.push_back(new Scale(this, durationMs, newWidth, newHeight, true, waitDurationMs));
}

void Texture::smoothScale(int durationMs, double scaleFactor, int waitDurationMs)
{
	int newWidth = (int) (rect.w * scaleFactor);
	int newHeight = (int) (rect.h * scaleFactor);

	smoothScale(durationMs, newWidth, newHeight, waitDurationMs);
}

void Texture::smoothTranslate(int durationMs, int newX, int newY, int waitDurationMs)
{
	animationsRunning.push_back(new Translate(this, durationMs, newX, newY, true, waitDurationMs));
}

void Texture::setSubRect(int x, int y, int width, int height)
{
	textureSubRect.x = x;
	textureSubRect.y = y;
	textureSubRect.w = width;
	textureSubRect.h = height;
}

void Texture::setSubRect(SDL_Rect subRect)
{
	textureSubRect = rect;
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

SDL_Point Texture::getCenter() const
{
	return SDL_Point { rect.x + (rect.w / 2), rect.y + (rect.h / 2) };
}

}
