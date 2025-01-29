#pragma once

#ifdef PSX_ENGINE

#include "RewindHandler.h"

class PSXEngine
{
public:
	PSXEngine();
	~PSXEngine();

	void start(std::string rom);
	void stopEngine();
	void run_core();
	void handle_patches();
	void save_state(uint8_t slot, int gameIndex);
	void load_state(uint8_t slot, int gameIndex);
	void reset();
	void pause();
	void frame();
	void stop() { stopEngine(); };
	void initSaveStates(std::string gameName, int gameIndex);
	void clear_trophies();

	void trophy_complete(std::string description, int trophyID);

	int frameNum;
	saveStateMetaData saveData[3];

	// rewind stuff
	void handle_rewind(bool doRewind);
	void rewind_reset();
	void handleForwardsFrame();
	void rewind_push_state();
	void rewind_load_state_at_index(int idx);
	void rewind_handle_state(bool isSave);
	void set_rewinding(bool rewind) { isRewinding = rewind; };
	void set_language(std::string l) { language = l; };
	bool is_rewinding() { return isRewinding; };
	bool is_game_over() { return isGameOver; };
	void signal_rewind();
#if defined(TOMBA)
	bool is_movie_playing() { return movieReplaced; };
#endif 
	bool is_pal_rom() { return isPAL; };
	void set_is_pal_rom(bool p) 
	{
		isPAL = p; 	 
	};
	std::string get_language() { return language; };

	int GetRewindBufIdx() { return currentRewindIdx; };
	int GetRewindBufFrames() { return maxRewindFrames; };
	int GetRewindRecordedFrames() { return recordedFrames; };
	int GetIsBackwardFrame() { return isBackwardFrame; };
	int GetHasSave() { return hasSave; };
 
	int fb_width = 0;
	int fb_height = 0;
 
	const int maxRewindFrames = 30;
	int currentRewindIdx = 0;
	int recordedFrames = 0;

	bool enableAnalog = true;
	bool enableRumble = true;
	bool enableDownSampling = false;
	bool enableHighRes = true;
#if defined(TOMBA)
	bool enableOSTOverride = true;
	bool ostReplaced = false;
	bool movieReplaced = false;
	bool startupPatched = false;
 
#endif 
	bool disableInputs = false;
	bool disableRendering = false; 
	bool enableRewind = true;
	void set_analog_control(bool analog);
	void set_highres_mode(bool highres);
	std::string m_gamename;
 
	std::deque<RewindHandler> m_rewindStack;
	 
	uint8_t* m_psx_destbuff = NULL; // PSX Video buffer.
private:
	/* Rewind stuff goes here*/
	 
	bool isRewinding = false;
	bool isBackwardFrame = false;
	bool hasSave = false;
	bool isGameOver = false;
	bool isPAL = false;			
	std::string language = "ENG";
};

#endif
