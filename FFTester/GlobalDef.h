#pragma once

#include <mmreg.h>

enum MEDIA_CONTAINER_FORMAT_TYPE : WORD
{
	MEDIA_FMT_UNKNOWN = 0,
	MEDIA_FMT_RAWSTREAM = 1,
	MEDIA_FMT_WAV = 2,
	MEDIA_FMT_MP2 = 3,
	MEDIA_FMT_MP3 = 4,
	MEDIA_FMT_FLAC = 5,
	MEDIA_FMT_AAC = 6,
	MEDIA_FMT_WMA = 7,
	MEDIA_FMT_AIFF = 8,
	MEDIA_FMT_MP4 = 9,
};


enum MEDIA_CODEC_TYPE : WORD
{
	MEDIA_CODEC_UNKNOWN = 0,
	MEDIA_CODEC_PCM = 1,
	MEDIA_CODEC_MP2 = 2,
	MEDIA_CODEC_MP3 = 3,
	MEDIA_CODEC_WMA = 4,
	MEDIA_CODEC_FLAC = 5,
	MEDIA_CODEC_PLUGIN = 0xFFFF,
};

typedef enum ENUM_AUDIOTYPE : CHAR
{
	AT_UNKNOWN = 0,
	AT_WAV = 1,						// PCM
	AT_MP3WAV = 2,					// wav wrapped mpeg-1 layer 3
	AT_MP2 = 3,					// mpeg-1 layer 2 wav wrapped
	AT_MP3 = 4,						// mpeg-1 layer 3
	AT_MP2RAW = 5,					// mpeg-1 layer 2
	AT_INTERNAL = 5,
	AT_WMA = 6,						// microsoft media (http://msdn.microsoft.com/windowsmedia/downloads/default.aspx)
	AT_FLAC = 15,					// Free Lossless Audio Codec (http://flac.sourceforge.net/)
									/*	AT_RA = 7,						// real audio
									AT_APE = 8,						// monkey audio (http://www.monkeysaudio.com/)
									AT_MP4_AAC = 10,				// MP4 wrapped AAC
									AT_AAC = 11,					// mpeg-2/mpeg-4 AAC
									AT_QT = 12,						// Apple quicktime
									AT_OGG = 13,					//
									AT_FLAC = 15,					// Free Lossless Audio Codec (http://flac.sourceforge.net/)
									AT_MPC = 20,					// (http://www.musepack.net/)
									*/
	AT_EXT_CODEC = 21,				// Decode by external CODEC (FFmpeg , etc.)
} AUDIOTYPE;

struct AUDIO_STREAM_INFO
{
	MEDIA_CONTAINER_FORMAT_TYPE fmtType;
	MEDIA_CODEC_TYPE codecType;
	AUDIOTYPE aType;
	WAVEFORMATEX format;
	DWORD64 qwSamples;
	int nStreamIndex;
};