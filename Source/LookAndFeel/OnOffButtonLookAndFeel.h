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
	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override
	{
		// Button width and height
		float width = button.getWidth();
		float height = button.getHeight();
		
		float radius = width / 2.f - 1.f;
		float centreX = width / 2.f;
		float centreY = height / 2.f;
		float startAngle = 40.f;
		float endAngle = 360.f - startAngle;

		float startRad = startAngle * (M_PI / 180.f);
		float endRad = endAngle * (M_PI / 180.f);

		if (button.getToggleState())
			g.setColour(Colours::skyblue.brighter(.5f));
		else
			g.setColour(Colours::skyblue.darker(0.5f));

		g.drawLine(width / 2.f, 0.f, width / 2.f, radius + 1.f, 2.f);

		Path p;
		p.addCentredArc(centreX, centreY, radius, radius, 0.0f, startRad, endRad, true);
		g.strokePath(p, PathStrokeType(2.f, PathStrokeType::curved, PathStrokeType::rounded));
	}
};