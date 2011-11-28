#ifndef OFX_NFC
#define OFX_NFC

#include "ofMain.h"

#include <nfc.h>
//#include <nfc/nfc-types.h>
#include <nfc-messages.h>

//#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>
//#include <string.h>

// NFC
#include <nfc.h>

// Crapto1
#include "crapto1.h"

// Internal
#include "config.h"
#include "mifare.h"
#include "nfc-utils.h"

#include "mfoc.h"


class ofxNFC {
public:
	
	ofxNFC();
	
	string getVersion();
	string getReader();
	string getUID();
	vector<string> getUIDs();
	
	bool connect();
	void disconnect();
	
	bool connected;
	
	mftag tag;
	mfreader reader;
	nfc_device_t* pnd;
	//nfc_target_t* pnt;
	
};

#endif