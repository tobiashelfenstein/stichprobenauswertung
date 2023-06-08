// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "AbstractImporter.h"

#include <iostream>

void AbstractImporter::setLengthMeasurement(bool with_length_and_diameter)
{
	this->with_length_and_diameter = with_length_and_diameter;

	return;
}

bool AbstractImporter::getLiveState()
{
	return m_liveModus;
}
