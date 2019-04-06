/*
  ==============================================================================

    OnOffButtonLookAndFeel.h
    Created: 23 Mar 2019 4:18:57pm
    Author:  Joonas

  ==============================================================================
*/

#pragma once


#include "../JuceLibraryCode/JuceHeader.h"
#define _USE_MATH_DEFINES
#include <math.h>

// LookAndFeel for the low pass filter. Use with TextButton
//
class OnOffButtonLookAndFeel : public LookAndFeel_V4
{
public:
	void drawButtonBackground(Graphics& g, Button& button, const Colour&, bool, bool) override
	{
		// Button width and height
		auto area = button.getLocalBounds();
		Colour myColour = findColour(0x1005700);
		if (button.getToggleState())
		{
			button.setColour(TextButton::buttonColourId, Colours::white);
			myColour = myColour.darker(.4f);
		}
		else
		{
			myColour = myColour.darker(1);
		}
		
		g.setColour(myColour);
		g.fillRoundedRectangle(area.toFloat(), 22.f);
		
	}
	Font getTextButtonFont(TextButton&, int)
	{
		return Font(24, Font::bold);
	}
};