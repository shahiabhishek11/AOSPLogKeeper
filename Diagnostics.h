#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include<utils/RefBase.h>
#include<android.h>


class Diagnostic : public android::Refbase //Inherit from Refbase
{
public:
	Diagnostic(); //constructor
	~Diagnostic(); //Destructor
	bool onRequest(); //Function which process a request
	
};

#endif
	
