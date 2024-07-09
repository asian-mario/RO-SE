#pragma once
#include<AL/al.h>
#include <vector>

namespace ROSE {
	class soundBuffer {
	public:
		static soundBuffer* get();

		ALuint addSound(const char* filename);
		bool removeSound(const ALuint& buffer);


	private:
		soundBuffer();
		~soundBuffer();

		//every initialized sound goes here
		std::vector<ALuint> se_soundEffectBuffers;
	};


}
