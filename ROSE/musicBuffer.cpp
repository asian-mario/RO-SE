#include "musicBuffer.h"
#include <cstddef>
#include <AL\alext.h>
#include <malloc.h>

namespace ROSE {
	void musicBuffer::Play() {
		ALsizei i;


		alGetError();

		//rewinds source position + clear buffer
		alSourceRewind(se_source);
		alSourcei(se_source, AL_BUFFER, 0);

		//fill the buffer queue with info from sound file
		for (i = 0; i < num_buffers; i++) {
			sf_count_t slen = sf_readf_short(se_sndfile, se_membuf, b_samples);
			if (slen < 1) break;

			slen *= se_sfinfo.channels * (sf_count_t)sizeof(short);
			alBufferData(se_buffers[i], se_format, se_membuf, (ALsizei)slen, se_sfinfo.samplerate);
		}

		if (alGetError() != AL_NO_ERROR) {
			throw("Error buffering for playback");
		}

		//queue and start playback
		alSourceQueueBuffers(se_source, i, se_buffers);
		alSourcePlay(se_source);
		if (alGetError() != AL_NO_ERROR) {
			throw("Error starting playback");
		}

	}

	void musicBuffer::Pause()
	{
		alSourcePause(se_source);
	}

	void musicBuffer::Stop()
	{
		alSourceStop(se_source);
	}

	void musicBuffer::Resume()
	{
		alSourcePlay(se_source);
	}

	//refresh the buffers so they don't run out of info and stop playing
	void musicBuffer::updateBufferStream() {
		ALint processed, state;


		alGetError();

		//check status of speakers
		alGetSourcei(se_source, AL_SOURCE_STATE, &state);
		//check amnt of buffers processed
		alGetSourcei(se_source, AL_BUFFERS_PROCESSED, &processed);

		if (alGetError() != AL_NO_ERROR)
		{
			throw("error checking music source state");
		}


		while (processed > 0) {
			ALuint bufid;
			sf_count_t slen;

			alSourceUnqueueBuffers(se_source, 1, &bufid);
			processed--;

			//read the rest of the data, refill the buffers and re-queue
			slen = sf_readf_short(se_sndfile, se_membuf, b_samples);
			if (slen > 0) {
				slen *= se_sfinfo.channels * (sf_count_t)sizeof(short);
				alBufferData(bufid, se_format, se_membuf, (ALsizei)slen,
					se_sfinfo.samplerate);
				alSourceQueueBuffers(se_source, 1, &bufid);
			}

			if (alGetError() != AL_NO_ERROR) {
				throw("error buffering music data");
			}
		}

		//checking if source is underrun
		if (state != AL_PLAYING && state != AL_PAUSED) {
			ALint queued;

			//if there isnt any buffers queued it means playback is done
			alGetSourcei(se_source, AL_BUFFERS_QUEUED, &queued);
			if (queued == 0)
				return;

			alSourcePlay(se_source);
			if (alGetError() != AL_NO_ERROR)
			{
				throw("error restarting music playback");
			}
		}

	}

	musicBuffer::musicBuffer(const char* filename) {
		alGenSources(1, &se_source);
		//generates all the buffers (currently 4)
		alGenBuffers(num_buffers, se_buffers);

		std::size_t frame_size;

		//when specifying paths with '\' instead of '/' a double slash is needed 

		//using sndfile to read the soundtrack
		se_sndfile = sf_open(filename, SFM_READ, &se_sfinfo);
		if (!se_sndfile) {
			throw("could not open provided music file -- check path");
		}
		//get sound format then set OpenAL format
		if (se_sfinfo.channels == 1)
			se_format = AL_FORMAT_MONO16;

		else if (se_sfinfo.channels == 2)
			se_format = AL_FORMAT_STEREO16;

		else if (se_sfinfo.channels == 3) {
			if (sf_command(se_sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				se_format = AL_FORMAT_BFORMAT2D_16;
		}

		else if (se_sfinfo.channels == 4) {
			if (sf_command(se_sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				se_format = AL_FORMAT_BFORMAT3D_16;
		}


		if (!se_format) {
			sf_close(se_sndfile);
			se_sndfile = NULL;
			throw("Unsupported channel count from file");
		}

		//calculates audio frame size
		frame_size = ((size_t)b_samples * (size_t)se_sfinfo.channels) * sizeof(short);
		se_membuf = static_cast<short*>(malloc(frame_size));

	}

	musicBuffer::~musicBuffer() {
		//bog standard
		alDeleteSources(1, &se_source);

		//close sound file
		if (se_sndfile)
			sf_close(se_sndfile);

		se_sndfile = nullptr;

		//free all uploaded data from memory
		free(se_membuf);

		//begone buffers
		alDeleteBuffers(num_buffers, se_buffers);

	}

	bool musicBuffer::isPlaying() {
		ALint playState;

		alGetSourcei(se_source, AL_SOURCE_STATE, &playState);
		return (playState == AL_PLAYING);
	}
}