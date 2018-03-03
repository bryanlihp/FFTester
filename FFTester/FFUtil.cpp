#include "stdafx.h"
#include "FFUtil.h"
#include "GlobalUtil.h"


#pragma comment(lib, "libavcodec.a")
#pragma comment(lib, "libavdevice.a")
#pragma comment(lib, "libavfilter.a")
#pragma comment(lib, "libavformat.a")
#pragma comment(lib, "libavutil.a")
#pragma comment(lib, "libswresample.a")
#pragma comment(lib, "libswscale.a")
#pragma comment(lib, "mp3lame.lib")
#pragma comment(lib, "Secur32.lib")

CFFUtil::CFFUtil()
{
}

CFFUtil::~CFFUtil()
{
}

void CFFUtil::Init()
{
	av_register_all();
	avfilter_register_all();
}

void CFFUtil::Uninit()
{
}

//AVERROR_BUFFER_TOO_SMALL;

void CFFUtil::FF_Probe(LPCTSTR pszFileName, int nStreamIndex)
{
	AUDIO_STREAM_INFO audioInfo;
	BOOL bSucceeded = FALSE;
	AVFormatContext *pFmtContext = NULL;
	AVCodecContext *pDecodeContext = NULL;

	CStringA sFileName = CT2A(pszFileName, CP_UTF8);
	int nCode = avformat_open_input(&pFmtContext, sFileName, NULL, NULL);
	if (nCode < 0)
	{
		char errMgr[4096];
		av_make_error_string(errMgr, 4096, nCode);
		av_log(NULL, AV_LOG_ERROR, "Cannot open input file");
		goto cleanup; // bail out
	}

	MEMLEAK_WRAPPER("LEAK001_S");
	//	av_dump_format(pFmtContext, 0, sFileName, 0);
	if (avformat_find_stream_info(pFmtContext, NULL) < 0)
	{
		av_log(NULL, AV_LOG_ERROR, "Cannot find stream information");
		goto cleanup; // bail out
	}
	MEMLEAK_WRAPPER("LEAK001_E");
	if (nStreamIndex < 0)
	{
		AVMediaType mType = AVMEDIA_TYPE_AUDIO;
		mType = AVMEDIA_TYPE_VIDEO;
		nStreamIndex = av_find_best_stream(pFmtContext, mType, -1, -1, NULL, 0);
		if (nStreamIndex < 0)
		{
			av_log(NULL, AV_LOG_ERROR, "Cannot find AUDIO stream in input file '%s'", sFileName);
			goto cleanup; // bail out
		}
	}
	else if (nStreamIndex >= (int)pFmtContext->nb_streams)
	{
		av_log(NULL, AV_LOG_ERROR, "Desired stream does not exist");
		goto cleanup; // bail out
	}
	/* find decoder for the stream */
	AVStream * pAudioStream = pFmtContext->streams[nStreamIndex];
	AVCodecParameters * pCodecPar = pAudioStream->codecpar;
	AVCodec * pDecoder = avcodec_find_decoder(pCodecPar->codec_id);
	if (!pDecoder) {
		av_log(NULL, AV_LOG_ERROR, "Failed to find AUDIO codec");
		goto cleanup; // bail out
	}
	pDecodeContext = avcodec_alloc_context3(pDecoder);
	if (NULL == pDecodeContext) {
		av_log(NULL, AV_LOG_ERROR, "Could not allocate audio codec context");
		goto cleanup; // bail out
	}
	int nErrCode = avcodec_parameters_to_context(pDecodeContext, pCodecPar);
	if (nErrCode < 0)
	{
		av_log(NULL, AV_LOG_ERROR, "Cannot init audio decoder context");
		goto cleanup; // bail out
	}

	if (pCodecPar->sample_rate <= 0)
	{
		av_log(NULL, AV_LOG_ERROR, "Unable to detect sample rate");
		goto cleanup; // bail out
	}

	double fStreamDuration = -1.0;
	if (pAudioStream->duration > 0)
	{
		fStreamDuration = (double)pAudioStream->duration * (double)pAudioStream->time_base.num * 1000.0 / (double)pAudioStream->time_base.den;
	}
	else if (pFmtContext->duration > 0)
	{
		fStreamDuration = (double)pFmtContext->duration * 1000.0 / (double)AV_TIME_BASE;
	}

	if (fStreamDuration <= 0)
	{
		av_log(NULL, AV_LOG_ERROR, "Unable to detect duration");
		goto cleanup; // bail out
	}

	AVCodecID avCodecID = pDecoder->id;
	audioInfo.nStreamIndex = nStreamIndex;
	audioInfo.fmtType = GetFormatType(pFmtContext->iformat->name);
	audioInfo.codecType = GetBurliMediaCodecTypeByAVCodecID(avCodecID);
	audioInfo.aType = GetBurliAudioFileType(audioInfo.fmtType, audioInfo.codecType);
	audioInfo.format.wFormatTag = GetWaveFormatTag(avCodecID);
	// Set input audio format from this plug-in DLL
	AVSampleFormat avFmt = (AVSampleFormat)pCodecPar->format;
	int bytes_per_sample = av_get_bytes_per_sample(avFmt);
	/*  for audio stream in AV_SAMPLE_FMT_FLTP format, pCodecPar->bits_per_coded_sample is 16.
	if (pCodecPar->bits_per_coded_sample > 0)
	{
	bytes_per_sample = pCodecPar->bits_per_coded_sample / 8;
	}
	*/
	audioInfo.format.nChannels = pCodecPar->channels;
	audioInfo.format.nSamplesPerSec = pCodecPar->sample_rate;
	audioInfo.format.nAvgBytesPerSec = bytes_per_sample * pCodecPar->sample_rate * pCodecPar->channels;
	audioInfo.format.nBlockAlign = bytes_per_sample * pCodecPar->channels;
	audioInfo.format.wBitsPerSample = bytes_per_sample * 8;
	audioInfo.format.cbSize = 0; 

	QWORD qwPlayLength = (QWORD)round(fStreamDuration);
	audioInfo.qwSamples = qwPlayLength * audioInfo.format.nSamplesPerSec;

	bSucceeded = TRUE;
cleanup:
	if (NULL != pDecodeContext)
	{
		avcodec_free_context(&pDecodeContext);
	}
	if (NULL != pFmtContext)
	{
		avformat_close_input(&pFmtContext);
	}
}
