#include "ofxNFC.h"

ofxNFC::ofxNFC() {
	connected = false;
}

string ofxNFC::getVersion() {
	return nfc_version();	
}

bool ofxNFC::connect() {
	if (!connected) pnd = reader.pdi = nfc_connect(NULL);
	return connected = (pnd!=NULL);
}

//int ofxNFC::getNumDevices() {
//    //nfc_list_devices (nfc_device_desc_t pnddDevices[], size_t szDevices, size_t * pszDeviceFound);
//    //nfc_list_devices
//}

void ofxNFC::disconnect() {
	nfc_disconnect(pnd);
	connected = false;
}

string ofxNFC::getReader() {

	// Connect using the first available NFC device
	if (!connect()) return "no reader found";

	// Set connected NFC device to initiator mode
	nfc_initiator_init(pnd);
	
	// Enable field so more power consuming cards can power themselves up
	nfc_configure(pnd, NDO_ACTIVATE_FIELD, true);
		
	return pnd->acName;
}

string ofxNFC::getUID() {
	connect();
	
	mftag tag;


	//r->pdi = nfc_connect(NULL);

	//cout << pnd << endl;
	//return "x";
	// Initialize reader/tag structures
	//mf_init(&t, &r);
	// Configure reader settings
	//mf_configure(pnd);
	//mf_select_tag(r.pdi, &(t.nt));
	
	nfc_initiator_init(reader.pdi);
		
	cout << reader.pdi << endl;
	
	// Drop the field for a while, so can be reset
	nfc_configure(reader.pdi,NDO_ACTIVATE_FIELD,false);
	// Let the reader only try once to find a tag
	nfc_configure(reader.pdi,NDO_INFINITE_SELECT,false);
	// Configure the CRC and Parity settings
	nfc_configure(reader.pdi,NDO_HANDLE_CRC,true);
	nfc_configure(reader.pdi,NDO_HANDLE_PARITY,true);
	// Enable the field so more power consuming cards can power themselves up
	nfc_configure(reader.pdi,NDO_ACTIVATE_FIELD,true);


	nfc_modulation_t nm;
	nm.nmt = NMT_ISO14443A;
	nm.nbr = NBR_106;

	//return "X";

	
	if (!nfc_initiator_select_passive_target(reader.pdi, nm, NULL, 0, &(tag.nt))) {
		fprintf(stderr, "!Error connecting to the MIFARE Classic tag\n");
		nfc_disconnect(reader.pdi);
		exit(1);
	}
	
//	
//	t.uid = (uint32_t) bytes_to_num(t.nt.nti.nai.abtUid, 4);
//	
//	char buf[20];
//	sprintf(buf, "%08x",t.uid);
//	return buf;
}

void mf_configure(nfc_device_t* pdi) {
}

void mf_select_tag(nfc_device_t* pdi, nfc_target_t* pnt) {
}

void num_to_bytes(uint64_t n, uint32_t len, byte_t* dest) {
	while (len--) {
		dest[len] = (byte_t) n;
		n >>= 8;
	}
}

long long unsigned int bytes_to_num(byte_t* src, uint32_t len) {
	uint64_t num = 0;
	while (len--)
	{
		num = (num << 8) | (*src);
		src++;
	}
	return num;
}
