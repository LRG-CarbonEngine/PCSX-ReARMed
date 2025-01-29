#define UNICODE

#include <iostream>
#include <time.h>
#include <cmath>
#include <deque>
#include <filesystem>
#include <windows.h>
#include <wchar.h>
#include <codecvt>
#include "../titleConfig.h"
#include "PSXEngine.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "decode_xa.h"
#include "plugins/dfsound/externals.h"
#include "sio.h"

#ifdef __cplusplus
}
#endif
 
extern char Mcd1Data[MCD_SIZE];

const int samplerate = 48000;
 
 

#define AUDIO_SAMPLERATE samplerate
#define AUDIO_BUFFER_SAMPLES psx_out_size
#define AUDIO_TRANSFERBUF_SIZE (AUDIO_BUFFER_SAMPLES * 2)
 
SDL_AudioDeviceID psx_audio_device;
extern std::string g_SaveGameDirectory;

extern Pad* g_Input;
extern Keys* g_InputKeys;
#endif
 
// Define the source and target sample rates
#define INPUT_SAMPLE_RATE 44100
#define OUTPUT_SAMPLE_RATE 48000
constexpr double audioratio = (double)OUTPUT_SAMPLE_RATE / (double)INPUT_SAMPLE_RATE;
 
inline int resampleAudio(int16_t* inputBuffer, int inputSamples, int16_t* outputBuffer) {
	// Calculate the resampling ratio


	// Calculate the number of output samples
	int outputSamples = (int)(inputSamples * audioratio);

	// Resampling process (simple linear interpolation)
	for (int i = 0; i < outputSamples; i++) {
		double srcIndex = i / audioratio;
		int index1 = (int)srcIndex;
		int index2 = index1 + 1;

		if (index2 >= inputSamples) {
			index2 = inputSamples - 1;
		}

		double fraction = srcIndex - index1;

		outputBuffer[i] = (int16_t)(
			(1.0 - fraction) * inputBuffer[index1] +
			fraction * inputBuffer[index2]
			);
	}

	return outputSamples;
}
 
int16_t psx_out_buf[4096];

void psx_audio_queue(int16_t* inputWave, int inputLength)
{
 
}

#endif 

PSXEngine::PSXEngine()
{
}


size_t save_size(void)
{
	// it's currently 4380651-4397047 bytes,
	// but have some reserved for future
	return 0x440000;
}


PSXEngine::~PSXEngine()
{

}

size_t save_img_size(void)
{ 
 
}

struct save_fp
{
	char* buf;
	size_t pos;
	int is_write;
};

static void* save_open(const char* name, const char* mode)
{
	struct save_fp* fp;

	if (name == NULL || mode == NULL)
		return NULL;

	fp = (save_fp*)malloc(sizeof(*fp));
	if (fp == NULL)
		return NULL;

	fp->buf = (char*)name;
	fp->pos = 0;
	fp->is_write = (mode[0] == 'w' || mode[1] == 'w');

	return fp;
}

static int save_read(void* file, void* buf, u32 len)
{
	struct save_fp* fp = (save_fp*)file;
	if (fp == NULL || buf == NULL)
		return -1;

	memcpy(buf, fp->buf + fp->pos, len);
	fp->pos += len;
	return len;
}

static int save_write(void* file, const void* buf, u32 len)
{
	struct save_fp* fp = (save_fp*)file;
	if (fp == NULL || buf == NULL)
		return -1;

	memcpy(fp->buf + fp->pos, buf, len);
	fp->pos += len;
	return len;
}

static long save_seek(void* file, long offs, int whence)
{
	struct save_fp* fp = (save_fp*)file;
	if (fp == NULL)
		return -1;

	switch (whence)
	{
	case SEEK_CUR:
		fp->pos += offs;
		return fp->pos;
	case SEEK_SET:
		fp->pos = offs;
		return fp->pos;
	default:
		return -1;
	}
}

static void save_close(void* file)
{
	struct save_fp* fp = (save_fp*)file;
	size_t r_size = save_size();
	if (fp == NULL)
		return;

	if (fp->pos > r_size)
		SysPrintf("ERROR: save buffer overflow detected\n");
	else if (fp->is_write && fp->pos < r_size)
		// make sure we don't save trash in leftover space
		memset(fp->buf + fp->pos, 0, r_size - fp->pos);
	free(fp);
}


std::wstring PSXUTF8ToWide(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);
}

std::string PSXWideToUTF8(const std::wstring& str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.to_bytes(str);
}
 

void PSXEngine::initSaveStates(std::string gameName, int gameIndex)
{
  
}

void PSXEngine::clear_trophies()
{
 
}
 
extern "C"
{
#include "arm_features.h"
#include "frontend\plugin_lib.h"
#include "frontend\cspace.h"
#include "frontend\main.h"
#include "psxcounters.h"
#include "frontend\plugin.h"
#include "plugins.h"
#include "psemu_plugin_defs.h"
#include "new_dynarec/new_dynarec.h"
#include "plugins/dfsound/spu_config.h"
#include "plugins/dfsound/out.h"
#include "plugins/dfinput/externals.h"
#include "misc.h"
#include "cheat.h"
#include "new_dynarec/new_dynarec.h"
#include "plugins/cdrcimg/cdrcimg.h"
#include "psxmem_map.h"
}

static int plugins_opened;

int vout_width=256, vout_height=240;
static int vout_doffs_old, vout_fb_dirty;

int sndWritePos = 0;

bool retro_load_game_special(unsigned game_type, const struct retro_game_info* info, size_t num_info) { return false; }
void retro_unload_game(void) {}
static int vout_open(void) { return 0; }
static void vout_close(void) {}
static int snd_init(void)
{
	return 0;
}
static void snd_finish(void) {}
static int snd_busy(void) { return 0; }
static void* vout_buf_ptr;

void pl_update_gun(int* xn, int* yn, int* xres, int* yres, int* in) {}

void force_vibration_off()
{
	// turn off all motors

	if (g_PSXEngine->enableRumble == true)
	{
		g_Input->SetRumble(0, RUMBLE_STRONG, 0);
	}
}

void plat_trigger_vibrate(int pad, int low, int high)
{
	if (g_PSXEngine->is_rewinding() == false)
	{
		if (g_PSXEngine->enableRumble == true)
		{
			g_Input->SetRumble(pad, RUMBLE_STRONG, high << 8);
		}
	}
}

static void snd_feed(void* buf, int bytes)
{
	psx_audio_queue((int16_t*)buf, bytes / 2);
}
extern "C"
{
	void out_register_carbon(struct out_driver* drv)
	{
		drv->name = "carbon";
		drv->init = snd_init;
		drv->finish = snd_finish;
		drv->busy = snd_busy;
		drv->feed = snd_feed;
	}
}

static void vout_set_mode(int w, int h, int raw_w, int raw_h, int bpp)
{
	vout_width = w;
	vout_height = h;

	vout_buf_ptr = g_PSXEngine->m_psx_destbuff;
}

int w, h;
int last_w, last_h;

static void vout_flip(const void* vram, int stride, int bgr24,
	int x, int y, int w, int h, int dims_changed)
{
	unsigned short* dest = (unsigned short*)vout_buf_ptr;
	const unsigned short* src = (unsigned short*)vram;
	int dstride = vout_width, h1 = h;
	int doffs;

	if (vram == NULL)
	{
		memset(vout_buf_ptr, 0, dstride * h * 2);
		goto out;
	}

	doffs = (vout_height - h) * dstride;
	doffs += (dstride - w) / 2 & ~1;
	if (doffs != vout_doffs_old)
	{
		// clear borders
		memset(vout_buf_ptr, 0, dstride * h * 2);
		vout_doffs_old = doffs;
	}
	dest += doffs;

	if (bgr24)
	{
		// XXX: could we switch to RETRO_PIXEL_FORMAT_XRGB8888 here?
		for (; h1-- > 0; dest += dstride, src += stride)
		{
			bgr888_to_rgb565(dest, src, w * 3);
		}
	}
	else
	{
		for (; h1-- > 0; dest += dstride, src += stride)
		{
			bgr555_to_rgb565(dest, src, w * 3);
		}
	}


out:
 
	std::string texName = std::string("PSXSourceFrameBuffer").append(std::to_string(g_PSXEngine->fb_width)).append(std::to_string(g_PSXEngine->fb_height));
	auto psxTexture = ResourceManager::GetTexture(texName.c_str());

	if (g_PSXEngine->fb_width != 0)
	{
		if (psxTexture.Width == 0)
		{
			ResourceManager::CreateTexture2(g_PSXEngine->fb_width, g_PSXEngine->fb_height, 2, texName.c_str());
			psxTexture = ResourceManager::GetTexture(texName.c_str());
			psxTexture.Set(vout_width, vout_height, (uint8_t*)(g_PSXEngine->m_psx_destbuff), 0, 2);
		}
		else
		{
			psxTexture.Set(vout_width, vout_height, (uint8_t*)(g_PSXEngine->m_psx_destbuff), 0, 2);
		}
	}
 
	vout_fb_dirty = 1;
	pl_rearmed_cbs.flip_cnt++;
}

void* pl_mmap(unsigned int size)
{
	return malloc(size);
}

void pl_munmap(void* ptr, unsigned int size)
{
	free(ptr);
}
#define MIN(a, b) ((a) > (b) ? (b) : (a))
inline unsigned char axis_range_modifier(float axis_value, bool is_square)
{
	float modifier_axis_range = 0;
 
	if (is_square)
	{
		// DualShock/Sense is -1.0f to 1.0f so we scale to -128 to 128
 
		modifier_axis_range = MIN(((axis_value*128.0f)+128.0f), 255.0f);	 
	}
	else
	{
		modifier_axis_range = MIN(((axis_value)+128.0f), 255.0f);

		// clamp 

		if (modifier_axis_range == 1.0f)
		{
			modifier_axis_range = 0.0f;
		}
	}

	if (g_PSXEngine->enableAnalog == false && modifier_axis_range != 128.0f)
		g_PSXEngine->enableAnalog = padToggleAnalog(0);

	return modifier_axis_range;
}

struct rearmed_cbs pl_rearmed_cbs = {
	.pl_vout_open = vout_open,
	.pl_vout_set_mode = vout_set_mode,
	.pl_vout_flip = vout_flip,
	.pl_vout_close = vout_close,
	.mmap = pl_mmap,
	.munmap = pl_munmap,
	/* from psxcounters */
	.gpu_hcnt = &hSyncCount,
	.gpu_frame_count = &frame_counter,
};

int in_analog_left[8][2] = { { 127, 127 },{ 127, 127 },{ 127, 127 },{ 127, 127 },{ 127, 127 },{ 127, 127 },{ 127, 127 },{ 127, 127 } };
int in_analog_right[8][2] = { { 127, 127 },{ 127, 127 },{ 127, 127 },{ 127, 127 },{ 127, 127 },{ 127, 127 },{ 127, 127 },{ 127, 127 } };
int in_mouse[8][2];
int multitap1 = 0;
int multitap2 = 0;
int in_enable_vibration = 1;

#define PORTS_NUMBER 8
unsigned short in_keystate[PORTS_NUMBER];

int in_type[8] = {
	PSE_PAD_TYPE_NONE, PSE_PAD_TYPE_NONE,
	PSE_PAD_TYPE_NONE, PSE_PAD_TYPE_NONE,
	PSE_PAD_TYPE_NONE, PSE_PAD_TYPE_NONE,
	PSE_PAD_TYPE_NONE, PSE_PAD_TYPE_NONE };

short switch_input() 
{
	return 0; 
}


#define MAX_LAG_FRAMES 3

#define tvdiff(tv, tv_old) \
	((tv.tv_sec - tv_old.tv_sec) * 1000000 + tv.tv_usec - tv_old.tv_usec)

static int vsync_cnt;
static int is_pal = false, frame_interval = 0, frame_interval1024 = 0;
static int vsync_usec_time=0;
 
int gettimeofday(struct timeval* tv, struct timezone* tz)
{
	FILETIME ft;
	unsigned __int64 tmpres = 0;
	static int tzflag = 0;

	if (NULL != tv)
	{
		GetSystemTimeAsFileTime(&ft);

		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;

		tmpres /= 10;  /*convert into microseconds*/
		/*converting file time to unix epoch*/
		tmpres -= DELTA_EPOCH_IN_MICROSECS;
		tv->tv_sec = (long)(tmpres / 1000000UL);
		tv->tv_usec = (long)(tmpres % 1000000UL);
	}

	return 0;
}
 

void pl_frame_limit(void)
{
 
	psxstop++;
}



void pl_timing_prepare(int is_pal_)
{
	pl_rearmed_cbs.fskip_advice = 0;
	pl_rearmed_cbs.flips_per_sec = 0;
	pl_rearmed_cbs.cpu_usage = 0;

	is_pal = is_pal_;
	frame_interval = is_pal ? 20000 : 16667;
	frame_interval1024 = is_pal ? 20000 * 1024 : 17066667;

	// used by P.E.Op.S. frameskip code
	pl_rearmed_cbs.gpu_peops.fFrameRateHz = is_pal ? 50.0f : 59.94f;
	pl_rearmed_cbs.gpu_peops.dwFrameRateTicks =
		(100000 * 100 / (unsigned long)(pl_rearmed_cbs.gpu_peops.fFrameRateHz * 100));
}

static void init_memcard(char* mcd_data)
{
	unsigned off = 0;
	unsigned i;

	memset(mcd_data, 0, MCD_SIZE);

	mcd_data[off++] = 'M';
	mcd_data[off++] = 'C';
	off += 0x7d;
	mcd_data[off++] = 0x0e;

	for (i = 0; i < 15; i++)
	{
		mcd_data[off++] = 0xa0;
		off += 0x07;
		mcd_data[off++] = 0xff;
		mcd_data[off++] = 0xff;
		off += 0x75;
		mcd_data[off++] = 0xa0;
	}

	for (i = 0; i < 20; i++)
	{
		mcd_data[off++] = 0xff;
		mcd_data[off++] = 0xff;
		mcd_data[off++] = 0xff;
		mcd_data[off++] = 0xff;
		off += 0x04;
		mcd_data[off++] = 0xff;
		mcd_data[off++] = 0xff;
		off += 0x76;
	}
}

 
void PSXEngine::start(std::string romName)
{	 
	frameNum = 0;
	dopause = false;
 
	int ret = 0;
 
	currentRewindIdx = 0;

	ret = emu_core_preinit();

	Config.Cpu = CPU_INTERPRETER;
 
	Config.PsxAuto = 0;
	Config.PsxType = PSX_TYPE_NTSC;
	Config.hacks.dualshock_init_analog = true; 
	Config.icache_emulation = 0; 
	pl_rearmed_cbs.screen_centering_type = C_BORDERLESS;	
 
	in_enable_vibration = enableRumble;
	enableDownSampling = false;
 
	set_highres_mode(true);
 
 
	Config.HLE = TRUE;
 
	init_memcard(Mcd1Data);
	ret |= emu_core_init();
	if (ret != 0) {
		SysPrintf("PCSX init failed.\n");
		exit(1);
	}

	bool found_bios = false;

	if (found_bios) {
		SysPrintf("found BIOS file: %s\n", Config.Bios);
	}
	else {
		SysPrintf("no BIOS files found.\n");
	}
	  
	spu_config.iUseReverb = 1;
	spu_config.iUseInterpolation = 1;
	spu_config.iXAPitch = 0;
	spu_config.iVolume = 768;
	spu_config.iTempo = 0;
	spu_config.iThreadAvail = 0;
 
	SaveFuncs.open = save_open;
	SaveFuncs.read = save_read;
	SaveFuncs.write = save_write;
	SaveFuncs.seek = save_seek;
	SaveFuncs.close = save_close;
 
	snprintf(Config.Mcd1, sizeof(Config.Mcd1), "none");
	snprintf(Config.Mcd2, sizeof(Config.Mcd2), "none");
	psxCpu->ApplyConfig();
	plugin_call_rearmed_cbs();
	if (plugins_opened) {
		ClosePlugins();
		plugins_opened = 0;
	}

	set_cd_image(romName.c_str());

	/* have to reload after set_cd_image for correct cdr plugin */
	if (LoadPlugins() == -1) {
		SysPrintf("failed to load plugins\n");
		return;
	}

	plugins_opened = 1;
	NetOpened = 0;

	if (OpenPlugins() == -1) {
		SysPrintf("failed to open plugins\n");
		return;
	}

	plugin_call_rearmed_cbs();
 
	dfinput_activate();

	if (CheckCdrom() == -1) {
		SysPrintf("unsupported/invalid CD image: %s\n", romName.c_str());
		return;
	}

	SysReset();
	if (Config.HLE)
		LoadCdrom();

	if (LoadCdrom() == -1) {
		SysPrintf("could not load CD\n");
		return;
	}
	emu_on_new_cd(0);
	psxstop = 0;
 
	in_type[0] = PSE_PAD_TYPE_ANALOGPAD;
	in_type[1] = PSE_PAD_TYPE_ANALOGPAD;
	enableAnalog = true;
 
}

void video_cb(void* video, int width, int height, int pitch)
{
	g_PSXEngine->handle_patches();
}

void PSXEngine::stopEngine()
{
	psxstop = 1;
	g_emu_want_quit = 1;
	audioRunning = false;
	dopause = true;
 
	if (psxCpu != NULL)
	{
		SysClose();
	}
 
}

void PSXEngine::run_core()
{
 
	psxstop = 0;
 
	if (disableInputs == false)
		in_keystate[0] = 0;

	 
	psxCpu->Execute();
	fb_width = vout_width;
	fb_height = vout_height;

	video_cb(vout_fb_dirty ? vout_buf_ptr : NULL,
		vout_width, vout_height, vout_width * 2);
	vout_fb_dirty = 0;
 
	frameNum++;	
}

#include "stb_image_write.h"

void PSXEngine::handle_patches()
{
}
void PSXEngine::save_state(uint8_t slot, int gameIndex)
{
}

void PSXEngine::load_state(uint8_t slot, int gameIndex)
{
	force_vibration_off();
}

void PSXEngine::reset()
{
	SysReset();
	if (Config.HLE)
		LoadCdrom();	

	m_rewindStack.clear();
	m_rewindStack.shrink_to_fit();

	recordedFrames = 0;
	in_keystate[0] = 0;

	force_vibration_off();
}

void PSXEngine::pause()
{
	dopause = true;
 
	force_vibration_off();
}
 
void PSXEngine::frame()
{ 
	
}

void PSXEngine::handleForwardsFrame()
{
  
}
 
void PSXEngine::rewind_push_state()
{ 
	rewind_handle_state(true);
}
 
 
void PSXEngine::rewind_load_state_at_index(int idx)
{	 
	rewind_handle_state(false);
}

void PSXEngine::rewind_handle_state(bool isSave)
{
 
}

void PSXEngine::signal_rewind()
{
 
}

void PSXEngine::set_analog_control(bool analog)
{
	// Just force it
	if (analog)
	{
		in_type[0] = PSE_PAD_TYPE_ANALOGPAD;
		in_type[1] = PSE_PAD_TYPE_ANALOGPAD;
		enableAnalog = true;
 
	}
	else
	{
		in_type[0] = PSE_PAD_TYPE_STANDARD;
		in_type[1] = PSE_PAD_TYPE_STANDARD;
		enableAnalog = true;
	}
}

void PSXEngine::set_highres_mode(bool highres)
{
	enableHighRes = highres;

	if (enableHighRes)
	{
		pl_rearmed_cbs.gpu_neon.enhancement_enable = 1;
		pl_rearmed_cbs.gpu_neon.enhancement_no_main = 1;
	}
	else
	{
		pl_rearmed_cbs.gpu_neon.enhancement_enable = 0;
		pl_rearmed_cbs.gpu_neon.enhancement_no_main = 0;
	}

 
}
 
void PSXEngine::handle_rewind(bool doRewind)
{	 
	handleForwardsFrame();
}

void PSXEngine::rewind_reset()
{ 
	currentRewindIdx = 0;
	recordedFrames = 0;
	isRewinding = false;
	isBackwardFrame = false;
	hasSave = false;	 

	m_rewindStack.clear();
	m_rewindStack.shrink_to_fit();
}
 
void PSXEngine::trophy_complete(std::string description, int trophyID)
{
 
}
 
 