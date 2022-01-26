#include "AbstractImporter.h"

#include <iostream>

void AbstractImporter::setLengthMeasurement(bool with_length_and_diameter)
{
	this->with_length_and_diameter = with_length_and_diameter;

	return;
}