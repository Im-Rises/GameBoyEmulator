#ifndef DEF_CARTRIDGE
#define DEF_CARTRIDGE

#include <fstream>
#include <map>
#include <memory>

#include "binaryLib/binaryLib.h"
#include "MBC/Mbc.h"

// Thanks to https://gbdev.io/pandocs/The_Cartridge_Header.html

class Cartridge
{
private:
	/*----------------------------Dictionaries for cartridge info---------------------------*/

	const std::map<char, std::string> manufacturerCodeMap = {
		{0x80, "Game supports CGB functions"},
		{0xC0, "Game works on CGB only"},
	};

	const std::map<char, std::string> oldLicenseeCodeMap = {
		{0x00, "none"},
		{0x01, "nintendo"},
		{0x08, "capcom"},
		{0x09, "hot - b"},
		{0x0A, "jaleco"},
		{0x0B, "coconuts"},
		{0x0C, "elite systems"},
		{0x13, "electronic arts"},
		{0x18, "hudsonsoft"},
		{0x19, "itc entertainment"},
		{0x1A, "yanoman"},
		{0x1D, "clary"},
		{0x1F, "virgin"},
		{0x24, "pcm complete"},
		{0x25, "san - x"},
		{0x28, "kotobuki systems"},
		{0x29, "seta"},
		{0x30, "infogrames"},
		{0x31, "nintendo"},
		{0x32, "bandai"},
		{0x33, "see above"},
		{0x34, "konami"},
		{0x35, "hector"},
		{0x38, "capcom"},
		{0x39, "banpresto"},
		{0x3C, "entertainment i"},
		{0x3E, "gremlin"},
		{0x41, "ubi soft"},
		{0x42, "atlus"},
		{0x44, "malibu"},
		{0x46, "angel"},
		{0x47, "spectrum holoby"},
		{0x49, "irem"},
		{0x4A, "virgin"},
		{0x4D, "malibu"},
		{0x4F, "u.s.gold"},
		{0x50, "absolute"},
		{0x51, "acclaim"},
		{0x52, "activision"},
		{0x53, "american sammy"},
		{0x54, "gametek"},
		{0x55, "park place"},
		{0x56, "ljn"},
		{0x57, "matchbox"},
		{0x59, "milton bradley"},
		{0x5A, "mindscape"},
		{0x5B, "romstar"},
		{0x5C, "naxat soft"},
		{0x5D, "tradewest"},
		{0x60, "titus"},
		{0x61, "virgin"},
		{0x67, "ocean"},
		{0x69, "electronic arts"},
		{0x6E, "elite systems"},
		{0x6F, "electro brain"},
		{0x70, "infogrames"},
		{0x71, "interplay"},
		{0x72, "broderbund"},
		{0x73, "sculptered soft"},
		{0x75, "the sales curve"},
		{0x78, "t*hq"},
		{0x79, "accolade"},
		{0x7A, "triffix entertainment"},
		{0x7C, "microprose"},
		{0x7F, "kemco"},
		{0x80, "misawa entertainment"},
		{0x83, "lozc"},
		{0x86, "*tokuma shoten i"},
		{0x8B, "bullet - proof software"},
		{0x8C, "vic tokai"},
		{0x8E, "ape"},
		{0x8F, "i'max"},
		{0x91, "chun soft"},
		{0x92, "video system"},
		{0x93, "tsuburava"},
		{0x95, "varie"},
		{0x96, "yonezawa / s'pal   "},
		{0x97, "kaneko"},
		{0x99, "arc"},
		{0x9A, "nihon bussan"},
		{0x9B, "tecmo"},
		{0x9C, "imagineer"},
		{0x9D, "banpresto"},
		{0x9F, "nova"},
		{0xA1, "hori electric"},
		{0xA2, "bandai"},
		{0xA4, "konami"},
		{0xA6, "kawada"},
		{0xA7, "takara"},
		{0xA9, "technos japan"},
		{0xAA, "broderbund"},
		{0xAC, "toei animation"},
		{0xAD, "toho"},
		{0xAF, "namco"},
		{0xB0, "acclaim"},
		{0xB1, "ascii or nexoft"},
		{0xB2, "bandai"},
		{0xB4, "enix"},
		{0xB6, "hal"},
		{0xB7, "snk"},
		{0xB9, "pony canyon"},
		{0xBA, "*culture brain o"},
		{0xBB, "sunsoft"},
		{0xBD, "sony imagesoft"},
		{0xBF, "sammy"},
		{0xC0, "taito"},
		{0xC2, "kemco"},
		{0xC3, "squaresoft"},
		{0xC4, "tokuma shoten i"},
		{0xC5, "data east"},
		{0xC6, "tonkin house"},
		{0xC8, "koei"},
		{0xC9, "ufl"},
		{0xCA, "ultra"},
		{0xCB, "vap"},
		{0xCC, "use"},
		{0xCD, "meldac"},
		{0xCE, "*pony canyon or"},
		{0xCF, "angel"},
		{0xD0, "taito"},
		{0xD1, "sofel"},
		{0xD2, "quest"},
		{0xD3, "sigma enterprises"},
		{0xD4, "ask kodansha"},
		{0xD6, "naxat soft"},
		{0xD7, "copya systems"},
		{0xD9, "banpresto"},
		{0xDA, "tomy"},
		{0xDB, "ljn"},
		{0xDD, "ncs"},
		{0xDE, "human"},
		{0xDF, "altron"},
		{0xE0, "jaleco"},
		{0xE1, "towachiki"},
		{0xE2, "uutaka"},
		{0xE3, "varie"},
		{0xE5, "epoch"},
		{0xE7, "athena"},
		{0xE8, "asmik"},
		{0xE9, "natsume"},
		{0xEA, "king records"},
		{0xEB, "atlus"},
		{0xEC, "epic / sony records"},
		{0xEE, "igs"},
		{0xF0, "a wave"},
		{0xF3, "extreme entertainment"},
		{0xFF, "ljn"},
	};

	const std::map<char, std::string> newLicenseeCodeMap = {
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
		{0x96, "Yonezawa / s'pal"},
		{0x97, "Kaneko"},
		{0x99, "Pack in soft"},
		{0xA4, "Konami(Yu - Gi - Oh!)"}
	};

	const std::map<char, std::string> cartridgeTypeMap = {
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

	const std::map<char, int> romSizeCodeBankMap = {
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

	const std::map<char, int> ramSizeCodeBankMap = {
		{0x00, 0},
		{0x01, 0},
		{0x02, 1},
		{0x03, 4},
		{0x04, 16},
		{0x05, 8},
	};

	const std::map<char, std::string> destinationMap = {
		{0x00, "Japan"},
		{0x01, "Other"}
	};

	/*-----------------------String variables----------------------*/
	std::string romPath;

	std::string gameTitle;
	std::string manufacturerCode;
	std::string cGBFlag;
	std::string gamePublisher;
	std::string licensee;
	std::string sGBFlag;
	std::string cartridgeType;
	std::string destination;
	std::string maskRomVersion;
	std::string headerChecksum;
	std::string globalChecksum;


	/*-----------------------Cartridge rom, ram and MBC----------------------*/
	std::shared_ptr<Mbc> mbcPtr;
	// int nbrRomBanks, nbrRamBanks;
	std::vector<uint8> rom, ram;

public:
	/*----------------------------Constructor/Desctructor/Reset---------------------------*/
	Cartridge(const std::string& romPath);
	~Cartridge();

	void loadRom(std::string romPath);

	void writeRom(const uint16& address, const uint8& data);
	uint8 readRom(const uint16& address) const;

	void writeRam(const uint16& address, const uint8& data);
	uint8 readRam(const uint16& address) const;


	/*----------------------------Getters and Setters---------------------------*/
	void dump(std::ofstream& savestateFile);
	void loadDumpedData(std::ifstream& savestateFile);

	/*----------------------------Getters and Setters---------------------------*/
	std::string getGameName() const;

	std::string getRomPath() const;

	/*----------------------------ToString---------------------------*/
	std::string toString();
};

#endif
