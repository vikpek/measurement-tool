/*
 * StringTransformer.cpp
 *
 *  Created on: May 17, 2011
 *      Author: vikpek
 */

#include "StringTransformer.h"

StringTransformer::StringTransformer() {
	// TODO Auto-generated constructor stub

}

StringTransformer::~StringTransformer() {
	// TODO Auto-generated destructor stub
}

char *StringTransformer::returnFileNameFromPath(char *binary_path)
{
	char * binary_name;
	    char *tmp_string[sizeof(strtok(binary_path, "/"))];
	    if(sizeof(tmp_string) > 0)
	    {
	        tmp_string[0] = strtok(binary_path, "/");
	        unsigned int tmp_s = sizeof(strtok(binary_path, "/"));
	        for(unsigned int i = 0; i < tmp_s; i++)
	        {
	            tmp_string[i] = strtok (NULL, "/");
	        }
	        binary_name = tmp_string[tmp_s-2];
	    }
	    return binary_name;
}


