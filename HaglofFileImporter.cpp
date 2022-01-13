//#include "HaglofFileImporter.h"
//
//#import <msxml3.dll>
//
//
//
//HaglofFileImporter::HaglofFileImporter()
//{
//	// nothing to do
//}
//
//HaglofFileImporter::~HaglofFileImporter()
//{
//	// nothing to do
//}
//
//bool HaglofFileImporter::importXMLFile(char *filename)
//{
//	CoInitializeEx(NULL, COINIT_SPEED_OVER_MEMORY);
//
//	this->pXMLDoc.CreateInstance(__uuidof(DOMDocument));
//	this->pXMLDoc->async = VARIANT_FALSE;
//	this->pXMLDoc->validateOnParse = VARIANT_TRUE;
//
//	this->pXMLDoc->load(filename);
//	this->pXMLDoc->setProperty("SelectionLanguage", "XPath");
//
//	return TRUE;
//}
//
//bool HaglofFileImporter::readAll()
//{
//	IXMLDOMNodeListPtr pTrees = nullptr;
//	IXMLDOMNodePtr pTree = nullptr;
//
//	HaglofData entry;
//
//	pTrees = this->pXMLDoc->selectNodes("/MDIIDATA/Data/Tree");
//
//	long numTrees = 0;
//	pTrees->get_length(&numTrees);
//	for (long i = 0; i < numTrees; i++)
//	{
//		//entry is not empty
//		pTrees->get_item(i, &pTree);
//
//		// ist wtol sicher und gut?!
//		entry.species = this->readMeasuredData(pTree, bstr_t("SpeciesText"));
//		entry.diameter = _wtol(this->readMeasuredData(pTree, bstr_t("Diameter")));
//		entry.height1 = _wtol(this->readMeasuredData(pTree, bstr_t("Height1")));
//
//		this->measuredData.push_back(entry);
//	}
//
//	return TRUE;
//}
//
//// TODO: Verbesserung Pointer to Pointer = **node; Speicherverwaltung
//BSTR HaglofFileImporter::readMeasuredData(IXMLDOMNode *node, bstr_t queryString)
//{
//	IXMLDOMNodePtr pData = nullptr;
//	BSTR value;
//
//	node->selectSingleNode(queryString, &pData);
//	pData->get_text(&value);
//
//	return value;
//}
