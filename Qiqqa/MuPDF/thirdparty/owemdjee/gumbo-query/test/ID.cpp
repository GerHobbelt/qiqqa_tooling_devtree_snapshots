/*
 * ID test.
 */

#include <iostream>
#include <fstream>

#include "Util.h"
#include "Document.h"
#include "Node.h"

#include "../example/monolithic_examples.h"

 using std::string;

#if defined(BUILD_MONOLITHIC)
#define main		gumboquery_test_main
#endif

int main(void)
{
	string page(file_str("test_page.html"));

	CDocument doc;
	doc.parse(page.c_str());

	CSelection c = doc.find("#start-of-content");
	if(c.nodeNum() > 0)
		return 0;
	return 1;
}
