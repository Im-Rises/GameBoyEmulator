#ifndef DEF_CARTRIDGE
#define DEF_CARTRIDGE

#include <fstream>
#include <map>

#include "binaryLib/binaryLib.h"

using namespace std;

//p298

// enum CartridgeType
// {
// 	ROM,
// 	MBC1,
// 	MBC2,
// 	MBC3,
// 	MBC5
// };

class Cartridge
{
private:
	/*----------------------------Cartridge info---------------------------*/
	//Other data p299
	string gameName;
	string manufacturerCode;
	uint8 cgbFlag;

	uint8 destinationCode;

	map<uint8, string> publisherMap = {
		{0x00, "None"},
		{0x01, "Nintendo R & D1"},
		{0x08, "Capcom"},
		{0x13, "Electronic Arts"},
		{0x18, "Hudson Soft"},
		{0x19, "b - ai"},
		{0x20, "kss"},
		{0x22, "pow"},
		{0x24, "PCM Complete"},
		{0x25, "san - x"},
		{0x28, "Kemco Japan"},
		{0x29, "seta"},
		{0x30, "Viacom"},
		{0x31, "Nintendo"},
		{0x32, "Bandai"},
		{0x33, "Ocean / Acclaim"},
		{0x34, "Konami"},
		{0x35, "Hector"},
		{0x37, "Taito"},
		{0x38, "Hudson"},
		{0x39, "Banpresto"},
		{0x41, "Ubi Soft"},
		{0x42, "Atlus"},
		{0x44, "Malibu"},
		{0x46, "angel"},
		{0x47, "Bullet - Proof"},
		{0x49, "irem"},
		{0x50, "Absolute"},
		{0x51, "Acclaim"},
		{0x52, "Activision"},
		{0x53, "American sammy"},
		{0x54, "Konami"},
		{0x55, "Hi tech entertainment"},
		{0x56, "LJN"},
		{0x57, "Matchbox"},
		{0x58, "Mattel"},
		{0x59, "Milton Bradley"},
		{0x60, "Titus"},
		{0x61, "Virgin"},
		{0x64, "LucasArts"},
		{0x67, "Ocean"},
		{0x69, "Electronic Arts"},
		{0x70, "Infogrames"},
		{0x71, "Interplay"},
		{0x72, "Broderbund"},
		{0x73, "sculptured"},
		{0x75, "sci"},
		{0x78, "THQ"},
		{0x79, "Accolade"},
		{0x80, "misawa"},
		{0x83, "lozc"},
		{0x86, "Tokuma Shoten Intermedia"},
		{0x87, "Tsukuda Original"},
		{0x91, "Chunsoft"},
		{0x92, "Video system"},
		{0x93, "Ocean / Acclaim"},
		{0x95, "Varie"},
		{0x96, "Yonezawa / s’pal"},
		{0x97, "Kaneko"},
		{0x99, "Pack in soft"},
		{0xA4, "Konami(Yu - Gi - Oh!)"}
	};

	map<uint8, string> cartridgeTypeMap = {
		{0x00, "ROM ONLY"},
		{0x01, "MBC1"},
		{0x02, "MBC1 + RAM"},
		{0x03, "MBC1 + RAM + BATTERY"},
		{0x05, "MBC2"},
		{0x06, "MBC2 + BATTERY"},
		{0x08, "ROM + RAM 1"},
		{0x09, "ROM + RAM + BATTERY 1"},
		{0x0B, "MMM01"},
		{0x0C, "MMM01 + RAM"},
		{0x0D, "MMM01 + RAM + BATTERY"},
		{0x0F, "MBC3 + TIMER + BATTERY"},
		{0x10, "MBC3 + TIMER + RAM + BATTERY 2"},
		{0x11, "MBC3"},
		{0x12, "MBC3 + RAM 2"},
		{0x13, "MBC3 + RAM + BATTERY 2"},
		{0x19, "MBC5"},
		{0x1A, "MBC5 + RAM"},
		{0x1B, "MBC5 + RAM + BATTERY"},
		{0x1C, "MBC5 + RUMBLE"},
		{0x1D, "MBC5 + RUMBLE + RAM"},
		{0x1E, "MBC5 + RUMBLE + RAM + BATTERY"},
		{0x20, "MBC6"},
		{0x22, "MBC7 + SENSOR + RUMBLE + RAM + BATTERY"},
		{0xFC, "POCKET CAMERA"},
		{0xFD, "BANDAI TAMA5"},
		{0xFE, "HuC3"},
		{0xFF, "HuC1 + RAM + BATTERY"},
	};

	map<uint8, int> romSizeCodeBankMap = {
		{0x00, 2},
		{0x01, 4},
		{0x02, 8},
		{0x03, 16},
		{0x04, 32},
		{0x05, 64},
		{0x06, 128},
		{0x07, 256},
		{0x08, 512},
		{0x52, 72},
		{0x53, 80},
		{0x54, 96},
	};

	map<uint8, int> ramSizeCodeBankMap = {
		{0x00,NULL},
		{0x01, NULL},
		{0x02, 1},
		{0x03, 4},
		{0x04, 16},
		{0x05, 8},
	};

	map<uint8, string> destinationMap = {
		{0x00, "Japan"},
		{0x01, "Other"}
	};

	string oldLicenseeCode;

	string maskRomVersionNumber;

	string headerChecksum;
	string globalChecksum;



	// bool cartridgeEmpty;
// string romPath;
//
// CartridgeType cartridgeType;
//
// //Rom and Ram banking
// uint8* rom = nullptr; //uint8 gameRom[0x100000];//Max rom size 8Mb, 1Mo
// uint8* ram = nullptr; //Ram bank of size 0x2000 (maximum of 4 ram bank)
//
// uint8 currentRomBank;
// uint8 currentRamBank;
//
// bool romBankingEnable;
// bool ramBankingEnable;
	// string gameCode;
	// uint8 cgbSupport;
	// uint8 romSize;
	// uint8 externalRamSize;
	// string destinationText;
public
:
	/*----------------------------Constructor/Desctructor/Reset---------------------------*/
	Cartridge();
	~Cartridge();
	void reset();

// 	/*----------------------------Load rom in cartridge---------------------------*/
// 	void writeRomInCartridge(const string& romPath);
//
// 	/*----------------------------Read and write---------------------------*/
// 	uint8 readRom(int address) const;
// 	uint8 readRomBank(const uint16& address) const;
// 	uint8 readRamBank(const uint16& address) const;
// 	void writeRamBank(const uint16& address, const uint8& data);
// 	void handleBanking(const uint16& address, const uint8& data);
//
// private
// :
// 	/*----------------------------Handle rom and ram banking---------------------------*/
// 	void mbcRegister0(const uint16& address, const uint8& data);
// 	void mbcRegister1(const uint16& address, const uint8& data);
// 	void mbcRegister2(const uint16& address, const uint8& data);
// 	void mbcRegister3(const uint16& address, const uint8& data);
//
// public
// :
// 	/*----------------------------Savestate---------------------------*/
// 	void dump(ofstream& savestateFile);
// 	void loadDumpedData(ifstream& savestateFile);
//
// 	/*----------------------------Getters and setters---------------------------*/
// 	CartridgeType getCartridgeType();
//
// 	uint8 getCurrentRamBank() const;
// 	void setCurrentRamBank(uint8 value);
//
// 	uint8 getCurrentRomBank() const;
// 	void setCurrentRomBank(uint8 value);
//
// 	bool getRamBankingEnable() const;
// 	void setRamBankingEnable(bool state);
//
// 	string getCartridgeTypeToString() const;
// 	bool getCartridgeIsEmpty() const;
//
// 	string getGameName() const;
// 	string getRomPath() const;
//
// 	/*----------------------------ToString---------------------------*/
// 	string toString() const;
// };

#endif
