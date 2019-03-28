/*
  ==============================================================================

    VibraFlangeSliderLookAndFeel.h
    Created: 23 Mar 2019 12:47:59pm
    Author:  Joonas

  ==============================================================================
*/

#pragma once


class VibraFlangeSliderLookAndFeel : public LookAndFeel_V4
{
public:
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
	{
		// Radius of knob
		auto radius = jmin(width / 2, height / 2) - 16.0f;
		// Centre point (centreX, centreY) of knob
		auto centreX = x + width * 0.5f;
		auto centreY = y + 20.f + radius + 2.f;

		auto rx = centreX - radius;
		auto ry = centreY - radius;
		auto rw = radius * 2.0f;
		// current angle of the slider
		auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

		// Draw path of the slider backgound (in darker background colour)
		Path backgroundArc;
		backgroundArc.addCentredArc(centreX, centreY, radius, radius, 0.0f, rotaryStartAngle, rotaryEndAngle, true);
		Colour myColour = findColour(0x1005700);
		myColour = myColour.darker(.8f);
		g.setColour(myColour);
		g.strokePath(backgroundArc, PathStrokeType(3.f, PathStrokeType::curved, PathStrokeType::rounded));


		// Draw path of slider foreground (in white)
		g.setColour(Colours::skyblue.brighter(.2f));
		Path foregroundArc;
		foregroundArc.addCentredArc(centreX, centreY, radius, radius, 0.0f, rotaryStartAngle, angle, true);
		g.strokePath(foregroundArc, PathStrokeType(3.f, PathStrokeType::curved, PathStrokeType::rounded));

		// Pointer
		Path p;
		auto pointerLength = radius * 1.f;
		auto pointerThickness = 3.0f;
		p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
		p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
		//g.setColour(Colours::white);
		g.fillPath(p);

		// Draw slider value
		//g.setFont(14);
		g.setFont(Font("Pacifico", 22.f, Font::plain));
		String flange = "Flange";
		String vibra  = "Vibra";
		String boring = "Lame";
		g.drawFittedText(flange, centreX - width / 2.f, 0.f, width, 14.f, Justification::centred, 1);
		g.drawFittedText(boring, 0.0, height - 10.f, 60.f, 10.f, Justification::centred, 1);
		g.drawFittedText(vibra, width - 45.f, height - 10.f, 45.f, 10.f, Justification::left, 1);
	}
};
