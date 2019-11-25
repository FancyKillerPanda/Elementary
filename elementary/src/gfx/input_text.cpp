#include "utils/log.h"
#include "gfx/input_text.h"

namespace el
{

InputText::InputText(SDL_Renderer* renderer, std::string fontPath, std::string defaultText, unsigned int size, SDL_Color colour)
	: renderer(renderer), currentText(renderer, fontPath, defaultText, size, colour), defaultText(defaultText), baseColour(colour), selectedColour(colour)
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

	if (!isSelected)
	{
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
					int currentLength = (int) currentText.text.length();

					if (currentLength == 0)
					{
						break;
					}

					if (isShowingDefaultText)
					{
						currentText.text = " "; // TODO(fkp): Maybe this shouldn't be just a space?
						currentText.update();

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
						isShowingDefaultText = true;
						currentText.text = defaultText;
					}

					currentText.update();

					if (centerAlign)
					{
						currentText.setCenter(centerPos.x, centerPos.y);
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

			if (isShowingDefaultText)
			{
				isShowingDefaultText = false;
				currentText.text = "";
			}

			currentText.text += event.text.text;
			currentText.update();

			if (centerAlign)
			{
				currentText.setCenter(centerPos.x, centerPos.y);
			}
		} break;
	}
}

void InputText::draw()
{
	currentText.draw();
}

void InputText::setCenter(int x, int y)
{
	centerPos = { x, y };
	currentText.setCenter(x, y);
}

void InputText::setIsSelected(bool value)
{
	isSelected = value;

	if (isSelected)
	{
		currentText.currentColour = selectedColour;
	}
	else
	{
		currentText.currentColour = baseColour;
	}

	currentText.update();
}

}
