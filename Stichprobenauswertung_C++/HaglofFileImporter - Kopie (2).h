#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>

#import <msxml3.dll>

struct HaglofData
{
	std::wstring species;
	int diameter;
	int height1;
};


class HaglofFileImporter
{
private:
	MSXML2::IXMLDOMDocument2Ptr pXMLDoc;
	std::vector<HaglofData> measuredData;

public:
	HaglofFileImporter();
	~HaglofFileImporter();

	bool importXMLFile(char *filename);
	bool readAll();
};

