#include "utils/log.h"
#include "gfx/menu.h"

namespace el
{

Menu::Menu(std::vector<Text*> texts)
	: items(texts)
{
	for (Text* item : items)
	{
		item->setIsClickable(true);
	}
}

Menu::Menu(std::vector<Text*> texts, SDL_Color baseColour, SDL_Color hoverColour, SDL_Color pressedColour)
	: items(texts)
{
	setColourValues(baseColour, hoverColour, pressedColour);

	for (Text* item : items)
	{
		item->setIsClickable(true);
	}
}

Menu::~Menu()
{
	for (Text* item : items)
	{
		delete item;
		item = nullptr;
	}
}

void Menu::draw()
{
	for (Text* item : items)
	{
		item->draw();
	}
}

int Menu::handleEvent(const SDL_Event& event)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i]->handleEvent(event))
		{
			// Item is clicked
			return i;
		}
	}

	return -1;
}

void Menu::setCenter(int x, int y, int distanceBetweenItemCenters)
{
	if (items.size() == 0)
	{
		warn("Menu items vector size is 0.");
		return;
	}
	
	if (items.size() % 2 == 0)
	{
		int centerLeftItemIndex = (int) items.size() / 2;

		// Sets items left of center
		for (int i = centerLeftItemIndex; i >= 0; i--)
		{
			int xOffsetFromCenter = ((centerLeftItemIndex - i) * distanceBetweenItemCenters) - (distanceBetweenItemCenters / 2);
			items[i]->setCenter(x - xOffsetFromCenter, y);
		}

		int centerRightItemIndex = ((int) items.size() / 2) + 1;
		
		// Sets items right of center
		for (int i = centerRightItemIndex; i < items.size(); i++)
		{
			int xOffsetFromCenter = ((i - centerRightItemIndex) * distanceBetweenItemCenters) + (distanceBetweenItemCenters / 2);
			items[i]->setCenter(x + xOffsetFromCenter, y);
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
			items[i]->setCenter(x - xOffsetFromCenter, y);
		}

		// Sets items right of center
		for (int i = centerItemIndex + 1; i < items.size(); i++)
		{
			int xOffsetFromCenter = (i - centerItemIndex) * distanceBetweenItemCenters;
			items[i]->setCenter(x + xOffsetFromCenter, y);
		}
	}
}

void Menu::setColourValues(SDL_Color p_BaseColour, SDL_Color p_HoverColour, SDL_Color p_PressedColour)
{
	baseColour = p_BaseColour;
	hoverColour = p_HoverColour;
	pressedColour = p_PressedColour;
	
	for (Text* item : items)
	{
		item->setColourValues(baseColour, hoverColour, pressedColour);
	}
}

}
