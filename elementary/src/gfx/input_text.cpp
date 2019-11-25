#include "utils/log.h"
#include "gfx/input_text.h"

namespace el
{

InputText::InputText(SDL_Renderer* renderer, std::string fontPath, std::string defaultText, unsigned int size, SDL_Color colour)
	: renderer(renderer), currentText(renderer, fontPath, defaultText, size, colour), defaultText(defaultText)
{
	isInitialised = currentText.isInitialised;
}

void InputText::handleEvent(SDL_Event& event)
{
	if (!isInitialised)
	{
		error("InputText not initialised before handling events.");
		return;
	}

	switch (event.type)
	{
		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_BACKSPACE:
				{
					// Gets current center position
					const SDL_Point oldCenterPos = currentText.getCenter();
					
					int currentLength = (int) currentText.text.length();

					if (currentLength == 0 || currentText.text == defaultText)
					{
						break;
					}

					if (SDL_GetModState() & KMOD_CTRL)
					{
						// Removes characters until a delimiting character
						while (currentText.text.length() > 0 && !std::ispunct(currentText.text.back()) && !std::isspace(currentText.text.back()))
						{
							currentText.text.pop_back();
						}

						// Removes the last space
						if (currentText.text.length() > 0 && std::isspace(currentText.text.back()))
						{
							currentText.text.pop_back();
						}
					}
					else
					{
						currentText.text.pop_back();
					}

					// Sets to default text if now empty
					if (currentText.text.length() == 0)
					{
						currentText.text = defaultText;
					}

					currentText.update();

					if (centerAlign)
					{
						currentText.setCenter(oldCenterPos.x, oldCenterPos.y);
					}
				} break;
			}
		} break;
		
		case SDL_TEXTINPUT:
		{
			// Letter pressed when numbers only
			if (numbersOnly && !std::isdigit(event.text.text[0]))
			{
				break;
			}

			// Gets current center position
			const SDL_Point oldCenterPos = currentText.getCenter();

			if (currentText.text == defaultText)
			{
				currentText.text = "";
			}

			currentText.text += event.text.text;
			currentText.update();

			if (centerAlign)
			{
				currentText.setCenter(oldCenterPos.x, oldCenterPos.y);
			}
		} break;
	}
}

void InputText::draw()
{
	currentText.draw();
}

}
