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
	char *tmp = NULL;
	tmp = (char *) calloc(300, sizeof(char));
	strcpy(tmp, binary_path);

	char * binary_name;
	    char *tmp_string[sizeof(strtok(tmp, "/"))];
	    if(sizeof(tmp_string) > 0)
	    {
	        tmp_string[0] = strtok(tmp, "/");
	        unsigned int tmp_s = sizeof(strtok(tmp, "/"));
	        for(unsigned int i = 0; i < tmp_s; i++)
	        {
	            tmp_string[i] = strtok (NULL, "/");
	        }
	        tmp = tmp_string[tmp_s-2];
	    }
	    return tmp;
}


