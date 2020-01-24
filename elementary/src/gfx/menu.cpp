#include "utils/log.h"
#include "gfx/menu.h"
#include "utils/sdl_compare.h"

namespace el
{

Menu::Menu(std::vector<Text> texts)
	: items(texts)
{
	for (Text& item : items)
	{
		item.setIsClickable(true);
	}
}

Menu::Menu(std::vector<Text> texts, SDL_Color baseColour, SDL_Color hoverColour, SDL_Color pressedColour)
	: items(texts)
{
	setColourValues(baseColour, hoverColour, pressedColour);

	for (Text& item : items)
	{
		item.setIsClickable(true);
	}
}

Menu::Menu(std::vector<Text> texts, SDL_Color baseColour, SDL_Color hoverColour, SDL_Color pressedColour, SDL_Color selectedColour)
	: Menu(texts, baseColour, hoverColour, pressedColour)
{
	this->selectedColour = selectedColour;
}

void Menu::draw()
{
	for (Text& item : items)
	{
		item.draw();
	}
}

int Menu::handleEvent(const SDL_Event& event)
{
	// Handles mouse input
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].handleEvent(event))
		{
			// Resets colour for previous item selected
			if (itemIndexSelected != -1)
			{
				items[itemIndexSelected].setCurrentColour(items[itemIndexSelected].baseColour);
			}				
			
			if (hasRadioButtons)
			{
				itemIndexSelected = i;
				items[itemIndexSelected].setCurrentColour(selectedColour);
			}
			
			return i;
		}
	}

	if (itemIndexSelected != -1 &&
		items[itemIndexSelected].currentColour == items[itemIndexSelected].baseColour)
	{
		items[itemIndexSelected].setCurrentColour(selectedColour);
	}					

	if (event.type == SDL_MOUSEMOTION &&
		itemIndexHovering != -1)
	{
		SDL_Point mousePos = { event.motion.x, event.motion.y };

		if (!SDL_PointInRect(&mousePos, &items[itemIndexHovering].texture.rect))
		{
			if (itemIndexHovering != itemIndexSelected)
			{
				items[itemIndexHovering].setCurrentColour(items[itemIndexHovering].baseColour);
			}
			
			itemIndexHovering = -1;
		}
	}
	else if (event.type == SDL_KEYDOWN)
	{
		const SDL_Keycode& keySym = event.key.keysym.sym;
		
		if (keySym == SDLK_RETURN)
		{
			if (itemIndexHovering != -1)
			{
				items[itemIndexHovering].setCurrentColour(items[itemIndexHovering].pressedColour);
			}
		}
		else
		{
			int oldIndex = itemIndexHovering;
			
			if ((keySym == SDLK_UP   && canUseUpDownKeys) ||
				(keySym == SDLK_LEFT && canUseLeftRightKeys))
			{
				itemIndexHovering -= 1;
				if (itemIndexHovering < 0) itemIndexHovering = (int) items.size() - 1;
			}
			else if ((keySym == SDLK_DOWN  && canUseUpDownKeys) ||
					 (keySym == SDLK_RIGHT && canUseLeftRightKeys))
			{
				itemIndexHovering += 1;
				itemIndexHovering %= items.size();
			}
			
			// Updates colours
			if (oldIndex != itemIndexHovering)
			{
				if (oldIndex != -1)
				{
					if (oldIndex == itemIndexSelected)
					{
						items[oldIndex].currentColour = selectedColour;
					}
					else
					{
						items[oldIndex].currentColour = items[oldIndex].baseColour;
					}

					items[oldIndex].update();
				}
				
				items[itemIndexHovering].setCurrentColour(items[itemIndexHovering].hoverColour);
			}
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_RETURN &&
			itemIndexHovering != -1)
		{
			// Resets the colour of previous item selected
			if (itemIndexSelected != -1)
			{
				items[itemIndexSelected].setCurrentColour(items[itemIndexSelected].baseColour);
			}

			if (hasRadioButtons)
			{
				itemIndexSelected = itemIndexHovering;
				items[itemIndexSelected].setCurrentColour(selectedColour);
			}
			else
			{
				items[itemIndexHovering].setCurrentColour(items[itemIndexHovering].baseColour);
			}
			
			// Updates index
			int oldIndex = itemIndexHovering;
			itemIndexHovering = -1;

			return oldIndex;
		}
	}

	return -1;
}

void Menu::setPositionsHorizontal(int x, int y, int distanceBetweenItemCenters, bool setUseLeftRightKeys)
{
	if (items.size() == 0)
	{
		warn("Menu items vector size is 0.");
		return;
	}
	
	if (items.size() % 2 == 0)
	{
		int centerLeftItemIndex = ((int) items.size() / 2) - 1;

		// Sets items left of center
		for (int i = centerLeftItemIndex; i >= 0; i--)
		{
			int xOffsetFromCenter = ((centerLeftItemIndex - i) * distanceBetweenItemCenters) + (distanceBetweenItemCenters / 2);
			items[i].setCenter(x - xOffsetFromCenter, y);
		}

		int centerRightItemIndex = (int) items.size() / 2;
		
		// Sets items right of center
		for (int i = centerRightItemIndex; i < items.size(); i++)
		{
			int xOffsetFromCenter = ((i - centerRightItemIndex) * distanceBetweenItemCenters) + (distanceBetweenItemCenters / 2);
			items[i].setCenter(x + xOffsetFromCenter, y);
		}
	}
	else
	{
		// Floors because of integer division
		int centerItemIndex = (int) items.size() / 2;

		// Sets items left of center and center
		for (int i = centerItemIndex; i >= 0; i--)
		{
			int xOffsetFromCenter = (centerItemIndex - i) * distanceBetweenItemCenters;
			items[i].setCenter(x - xOffsetFromCenter, y);
		}

		// Sets items right of center
		for (int i = centerItemIndex + 1; i < items.size(); i++)
		{
			int xOffsetFromCenter = (i - centerItemIndex) * distanceBetweenItemCenters;
			items[i].setCenter(x + xOffsetFromCenter, y);
		}
	}

	if (setUseLeftRightKeys)
	{
		canUseLeftRightKeys = true;
	}
}

void Menu::setPositionsVertical(int x, int y, int distanceBetweenItemCenters, bool setUseUpDownKeys)
{
	if (items.size() == 0)
	{
		warn("Menu items vector size is 0.");
		return;
	}
	
	if (items.size() % 2 == 0)
	{
		int centerUpItemIndex = (int) (items.size() / 2) - 1;

		// Sets items above center
		for (int i = centerUpItemIndex; i >= 0; i--)
		{
			int yOffsetFromCenter = ((centerUpItemIndex - i) * distanceBetweenItemCenters) + (distanceBetweenItemCenters / 2);
			items[i].setCenter(x, y - yOffsetFromCenter);
		}

		int centerDownItemIndex = (int) items.size() / 2;
		
		// Sets items below center
		for (int i = centerDownItemIndex; i < items.size(); i++)
		{
			int yOffsetFromCenter = ((i - centerDownItemIndex) * distanceBetweenItemCenters) + (distanceBetweenItemCenters / 2);
			items[i].setCenter(x, y + yOffsetFromCenter);
		}
	}
	else
	{
		// Floors because of integer division
		int centerItemIndex = (int) items.size() / 2;

		// Sets items above center and center
		for (int i = centerItemIndex; i >= 0; i--)
		{
			int yOffsetFromCenter = (centerItemIndex - i) * distanceBetweenItemCenters;
			items[i].setCenter(x, y - yOffsetFromCenter);
		}

		// Sets items below center
		for (int i = centerItemIndex + 1; i < items.size(); i++)
		{
			int yOffsetFromCenter = (i - centerItemIndex) * distanceBetweenItemCenters;
			items[i].setCenter(x, y + yOffsetFromCenter);
		}
	}

	if (setUseUpDownKeys)
	{
		canUseUpDownKeys = true;
	}
}

void Menu::setColourValues(SDL_Color p_BaseColour, SDL_Color p_HoverColour, SDL_Color p_PressedColour)
{
	baseColour = p_BaseColour;
	hoverColour = p_HoverColour;
	pressedColour = p_PressedColour;
	
	for (Text& item : items)
	{
		item.setColourValues(baseColour, hoverColour, pressedColour);
	}
}

}
