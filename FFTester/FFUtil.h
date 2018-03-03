#pragma once



class CFFUtil
{
public:
	CFFUtil();
	~CFFUtil();
public:
	static void Init();
	static void Uninit();
	static void FF_Probe(LPCTSTR pszFileName, int nStreamIndex);
	static MEDIA_CONTAINER_FORMAT_TYPE GetFormatType(const char *pszFormatName)
	{
		if (_stricmp(pszFormatName, "wav") == 0)
		{
			return MEDIA_FMT_WAV;
		}
		return MEDIA_FMT_RAWSTREAM;
	}
	static MEDIA_CODEC_TYPE GetBurliMediaCodecTypeByAVCodecID(AVCodecID avCodecID)
	{
		MEDIA_CODEC_TYPE codecType = MEDIA_CODEC_PLUGIN;
		if (AV_CODEC_ID_MP2 == avCodecID)
		{
			codecType = MEDIA_CODEC_MP2;
		}
		else if (AV_CODEC_ID_MP3 == avCodecID)
		{
			codecType = MEDIA_CODEC_MP3;
		}
		else if (avCodecID >= AV_CODEC_ID_FIRST_AUDIO && avCodecID < AV_CODEC_ID_ADPCM_IMA_QT)
		{
			codecType = MEDIA_CODEC_PCM;
		}
		else if (avCodecID == AV_CODEC_ID_FLAC)
		{
			codecType = MEDIA_CODEC_FLAC;
		}
		else if (avCodecID == AV_CODEC_ID_WMAV1 || avCodecID == AV_CODEC_ID_WMAV2)
		{
			codecType = MEDIA_CODEC_WMA;
		}
		else
		{
			codecType = MEDIA_CODEC_PLUGIN;
		}
		return codecType;
	}

	static AUDIOTYPE GetBurliAudioFileType(MEDIA_CONTAINER_FORMAT_TYPE fmtType, MEDIA_CODEC_TYPE codecType)
	{
		AUDIOTYPE audioType = AT_UNKNOWN;
		BOOL bWavWrapped = (MEDIA_FMT_WAV == fmtType);
		switch (codecType)
		{
		case MEDIA_CODEC_PCM:
			audioType = AT_WAV;
			break;
		case MEDIA_CODEC_MP2:
			audioType = bWavWrapped ? AT_MP2 : AT_MP2RAW;
			break;
		case MEDIA_CODEC_MP3:
			audioType = bWavWrapped ? AT_MP3WAV : AT_MP3;
			break;
		case MEDIA_CODEC_WMA:
			audioType = AT_WMA;
			break;
		case MEDIA_CODEC_FLAC:
			audioType = AT_FLAC;
			break;
		case MEDIA_CODEC_PLUGIN:
			audioType = AT_EXT_CODEC;
			break;
		default:
			audioType = AT_UNKNOWN;
			break;
		}
		return audioType;
	}

	static WORD GetWaveFormatTag(AVCodecID avCodecID)
	{
		WORD wFormatTag = WAVE_FORMAT_EXTENSIBLE;
		if (avCodecID == AV_CODEC_ID_MP2)
		{
			wFormatTag = WAVE_FORMAT_MPEG;
		}
		else if (avCodecID == AV_CODEC_ID_MP3)
		{
			wFormatTag = WAVE_FORMAT_MPEG;
		}
		else if (avCodecID >= AV_CODEC_ID_FIRST_AUDIO && avCodecID < AV_CODEC_ID_ADPCM_IMA_QT)
		{
			wFormatTag = WAVE_FORMAT_PCM;
		}
		else if (avCodecID == AV_CODEC_ID_WMAV1 || avCodecID == AV_CODEC_ID_WMAV2)
		{
			wFormatTag = WAVE_FORMAT_MSAUDIO1;
		}
		else
		{
			wFormatTag = WAVE_FORMAT_EXTENSIBLE;
		}
		return wFormatTag;
	}

};

