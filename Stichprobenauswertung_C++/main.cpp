#include "Windows.h"

#include "HEPAutomator.h"
#include "HaglofFileImporter.h"

int main(int argc, char* argv[])
{
	//HEPAutomator hep = HEPAutomator();
	//hep.connectToHEP();
	//hep.sendMeasuredValues(9);

	// test
	char file[] = "kluppfall.xml";
	HaglofFileImporter test = HaglofFileImporter();
	test.importXMLFile(file);
	test.readAll();

}