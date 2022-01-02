#include "HaglofFileImporter.h"

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "XmlLite.lib")


HaglofFileImporter::HaglofFileImporter()
{
	// nothing to do
}

HaglofFileImporter::~HaglofFileImporter()
{
	// nothing to do
}

bool HaglofFileImporter::importXMLFile()
{
	HRESULT hr;

	IStream *xmlFile;
	SHCreateStreamOnFile(L"kluppfall.xml", STGM_READ, &xmlFile);

	IXmlReader *reader;
	//CreateXmlReader(IID_PPV_ARGS(&reader), nullptr); // was ist IID_PPV_ARGS und nullptr statt NULL
	CreateXmlReader(__uuidof(IXmlReader), (void**) &reader, NULL);

	reader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit);
	reader->SetInput(xmlFile); // bin nicht sicher, ob das so klappt

	PCWSTR localName = nullptr;
	bool readSpecies = FALSE;
	PCWSTR currentSpecies = nullptr;
	PCWSTR currentDiameter = nullptr;

	PCWSTR value = nullptr;

	XmlNodeType nodeType;
	while (!reader->IsEOF())
	{
		reader->Read(&nodeType);
		switch (nodeType)
		{
		case XmlNodeType_XmlDeclaration:
			reader->GetValue(&value, NULL);
			std::wcout << "Test1: " << value << std::endl;
			break;

		case XmlNodeType_Element:
			reader->GetLocalName(&localName, NULL);
			
			// find current tree species text under tree node
			if (lstrcmp(localName, L"SpeciesText") == 0)
			{
				readSpecies = TRUE;
			}

			/*if (lstrcmp(localName, L"Diameter") == 0)
			{
				reader->GetValue(&currentDiameter, NULL);

				std::wcout << currentSpecies << ": " << currentDiameter << std::endl;

				currentSpecies = nullptr;
				currentDiameter = nullptr;

				std::wcout << "Leer: " << currentSpecies << ": " << currentDiameter << std::endl;
			}*/
			break;

		case XmlNodeType_Text:
			if (readSpecies)
			{
				reader->GetValue(&currentSpecies, NULL);
				std::wcout << "Baumart:" << currentSpecies << std::endl;

				readSpecies = FALSE;
			}

			break;
		}
	}

	return TRUE;
}
