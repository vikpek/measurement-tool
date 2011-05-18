/*
 * StringTransformer.h
 *
 *  Created on: May 17, 2011
 *      Author: vikpek
 */

#ifndef STRINGTRANSFORMER_H_
#define STRINGTRANSFORMER_H_
#include <iostream>
#include <string>

using namespace std;
class StringTransformer {
public:
	StringTransformer();
	virtual ~StringTransformer();

	char* returnFileNameFromPath(char *binary_path);
};

#endif /* STRINGTRANSFORMER_H_ */
