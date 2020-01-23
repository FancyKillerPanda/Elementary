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

void Menu::draw()
{
	for (Text& item : items)
	{
		item.draw();
	}
}

int Menu::handleEvent(const SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_RETURN:
				{
					if (itemIndexSelected != -1)
					{
						items[itemIndexSelected].currentColour = items[itemIndexSelected].pressedColour;
						items[itemIndexSelected].update();
					}
				} break;

				default:
				{
					const SDL_Keycode& keySym = event.key.keysym.sym;

					// Pressed down or right key and should handle those events
					if ((canUseUpDownKeys && keySym == SDLK_UP) || (canUseLeftRightKeys && keySym == SDLK_LEFT))
					{
						itemIndexSelected -= 1;

						if (itemIndexSelected < 0)
						{
							itemIndexSelected = (int) items.size() - 1;
						}
					}
					// Pressed up or left key and should handle those events
					else if ((canUseUpDownKeys && keySym == SDLK_DOWN) || (canUseLeftRightKeys && keySym == SDLK_RIGHT))
					{
						itemIndexSelected += 1;
						itemIndexSelected %= items.size();
					}
				} break;
			}
		} break;

		case SDL_KEYUP:
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_RETURN:
				{
					if (itemIndexSelected != -1)
					{
						// Returns to not selected
						items[itemIndexSelected].currentColour = items[itemIndexSelected].baseColour;
						items[itemIndexSelected].update();

						int oldIndex = itemIndexSelected;
						itemIndexSelected = -1;

						return oldIndex;
					}
				} break;
			}
		} break;

		case SDL_MOUSEMOTION:
		{
			SDL_Point mousePos = { event.motion.x, event.motion.y };
			bool hit = false;

			for (Text& text : items)
			{
				if (SDL_PointInRect(&mousePos, &text.texture.rect))
				{
					hit = true;
				}
			}
			
			if (!hit)
			{
				// Mouse wasn't over any menu item
				itemIndexSelected = -1;
			}
			
		} break;
	}

	// Handles the mouse events
	for (int i = 0; i < items.size(); i++)
	{
		if (i == itemIndexSelected && items[i].currentColour == items[i].baseColour)
		{
			// Needs to be highlighted
			items[i].currentColour = items[i].hoverColour;
			items[i].update();
		}

		if (i != itemIndexSelected && items[i].currentColour != items[i].baseColour)
		{
			// Needs to stop highlighting
			items[i].currentColour = items[i].baseColour;
			items[i].update();
		}

		if (items[i].handleEvent(event))
		{
			// Item is clicked
			return i;
		}

		if (i != itemIndexSelected && items[i].currentColour != items[i].baseColour)
		{
			itemIndexSelected = i;
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
