//#pragma once
//
//#include <Windows.h>
//#include <iostream>
//#include <vector>
//
//#import <msxml3.dll>
//
//struct HaglofData
//{
//	std::wstring species;
//	long diameter;
//	long height1;
//};
//
//
//class HaglofFileImporter
//{
//private:
//	MSXML2::IXMLDOMDocument2Ptr pXMLDoc;
//	std::vector<HaglofData> measuredData;
//
//	BSTR readMeasuredData(IXMLDOMNode *node, bstr_t queryString);
//
//public:
//	HaglofFileImporter();
//	~HaglofFileImporter();
//
//	bool importXMLFile(char *filename);
//	bool readAll();
//};
//
