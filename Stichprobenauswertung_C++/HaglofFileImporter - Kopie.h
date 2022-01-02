#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>

#include <xmllite.h>
#include <Shlwapi.h>

class HaglofFileImporter
{
private:
	std::vector<std::string> diameters;

public:
	HaglofFileImporter();
	~HaglofFileImporter();

	bool importXMLFile();
};

