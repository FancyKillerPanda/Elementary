#include "utils/log.h"
#include "gfx/input_text.h"

namespace el
{

InputText::InputText(SDL_Renderer* renderer, std::string fontPath, std::string defaultText, unsigned int size, SDL_Color colour)
	: renderer(renderer), displayedText(renderer, fontPath, defaultText, size, colour), defaultText(defaultText), text(defaultText), baseColour(colour), selectedColour(colour)
{
	isInitialised = displayedText.isInitialised;
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
					int currentLength = (int) displayedText.text.length();

					if (currentLength == 0)
					{
						break;
					}

					if (isShowingDefaultText)
					{
						text = "";
						displayedText.text = " ";
						displayedText.update();

						break;
					}

					if (SDL_GetModState() & KMOD_CTRL)
					{
						// Removes characters until a delimiting character
						while (displayedText.text.length() > 0 && !std::ispunct(displayedText.text.back()) && !std::isspace(displayedText.text.back()))
						{
							displayedText.text.pop_back();
						}

						// Removes the last space
						if (displayedText.text.length() > 0 && std::isspace(displayedText.text.back()))
						{
							displayedText.text.pop_back();
						}
					}
					else
					{
						displayedText.text.pop_back();
					}

					// Sets to default text if now empty
					if (displayedText.text.length() == 0)
					{
						isShowingDefaultText = true;
						displayedText.text = defaultText;
					}

					text = displayedText.text;
					displayedText.update();

					if (centerAlign)
					{
						displayedText.setCenter(centerPos.x, centerPos.y);
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
				displayedText.text = "";
			}

			displayedText.text += event.text.text;
			text = displayedText.text;
			displayedText.update();

			if (centerAlign)
			{
				displayedText.setCenter(centerPos.x, centerPos.y);
			}
		} break;
	}
}

void InputText::draw()
{
	displayedText.draw();
}

void InputText::setCenter(int x, int y)
{
	centerPos = { x, y };
	displayedText.setCenter(x, y);
}

void InputText::setIsSelected(bool value)
{
	isSelected = value;

	if (isSelected)
	{
		displayedText.currentColour = selectedColour;
	}
	else
	{
		displayedText.currentColour = baseColour;
	}

	displayedText.update();
}

}
