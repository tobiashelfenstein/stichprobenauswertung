#include "HaglofFileImporter.h"

#import <msxml3.dll>



HaglofFileImporter::HaglofFileImporter()
{
	// nothing to do
}

HaglofFileImporter::~HaglofFileImporter()
{
	// nothing to do
}

bool HaglofFileImporter::importXMLFile(char *filename)
{
	CoInitialize(NULL);
	// use CoInitializeEx(); instead

	this->pXMLDoc.CreateInstance(__uuidof(DOMDocument));

	this->pXMLDoc->async = VARIANT_FALSE;
	//pXMLDoc->validateOnParse = VARIANT_TRUE;

	this->pXMLDoc->load(filename);

	this->pXMLDoc->setProperty("SelectionLanguage", "XPath");

	return TRUE;
}

bool HaglofFileImporter::readAll()
{
	IXMLDOMNodeListPtr pTrees = nullptr;
	IXMLDOMNodePtr pTree = nullptr;

	IXMLDOMNodeListPtr pMeasuring = nullptr;
	IXMLDOMNodePtr pData = nullptr;

	BSTR nodeName;
	VARIANT nodeValue;

	HaglofData entry;
	//std::wstring entry;


	pTrees = this->pXMLDoc->getElementsByTagName("Tree");

	long numTrees = 0;
	pTrees->get_length(&numTrees);
	for (long i = 0; i < numTrees; i++)
	{
		pTrees->get_item(i, &pTree);
		pTree->get_childNodes(&pMeasuring);

		// entry is always an empty wstring
		//entry = L"";

		IXMLDOMNodePtr data;
		pTree->selectSingleNode(bstr_t("SpeciesText"), &data);

		data->get_nodeName(&nodeName);

		std::wcout << L"Select: " << nodeName << std::endl;

		long numData = 0;
		pMeasuring->get_length(&numData);
		for (long j = 0; j < numData; j++)
		{
			pMeasuring->get_item(j, &pData);
			pData->get_nodeName(&nodeName);
			pData->get_nodeTypedValue(&nodeValue);

			// save species text
			if (wcscmp(nodeName, L"SpeciesText") == 0)
			{
				entry.species = nodeValue.bstrVal;
				break;
			}

			// save diameter
			if (wcscmp(nodeName, L"Diameter") == 0)
			{
				entry.diameter = nodeValue.intVal;
				break;
			}

			if (wcscmp(nodeName, L"Height1") == 0)
			{
				entry.height1 = nodeValue.intVal;
				break;
			}

			//// return comma separated values
			//entry.append(nodeValue.bstrVal);
			//entry.append(L";");

			std::wcout << entry.diameter << std::endl;


		}

		//this->measuredData.push_back(entry);		
	}

	return TRUE;
}
