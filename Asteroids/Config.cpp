#include "Config.h"
#include <string>

namespace Config {
	namespace {
		float aspect = 4.f / 3.f;
		float invAspect = 3.f / 4.f;
		bool aspectChange = false;
	}

	unsigned int windowWidth = 480;
	unsigned int windowHeight = 360;
	unsigned int frameLimit = 60;
	
	bool fixedAspect = true;

	float aspectRatio() {
		return aspect;
	}

	float invAspectRatio() {
		return invAspect;
	}

	bool aspectRatioChanged() {
		return aspectChange;
	}

	void setAspectRatio(float newAspectRatio) {
		if (newAspectRatio != aspect) {
			aspect = newAspectRatio;
			invAspect = 1 / newAspectRatio;
			aspectChange = true;
		}
	}

	void nextFrame() {
		aspectChange = false;
	}
}