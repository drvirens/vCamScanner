
#include "ccConfig.h"

#include "LabelFactory.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)
	const float LabelFactory::BIG_FONT = 48 - 12;
	const float LabelFactory::HUGE_FONT = 150 - 60;
	const float LabelFactory::MEDIUM_FONT = 36 - 16;
  const float LabelFactory::SOMEWHAT_SMALL_FONT = 20 - 4;
	const float LabelFactory::SMALL_FONT = 20 - 8;
	const char* const LabelFactory::DEFAULT_FONT = "Segoe UI";

	const float LabelFactory::_v_fix = 0.375f;
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	const float LabelFactory::BIG_FONT = 48 - 10;
	const float LabelFactory::HUGE_FONT = 150 - 50;
	const float LabelFactory::MEDIUM_FONT = 36 - 12;
  const float LabelFactory::SOMEWHAT_SMALL_FONT = 20 - 4;
	const float LabelFactory::SMALL_FONT = 20 - 5;
	const char* const LabelFactory::DEFAULT_FONT = "Segoe UI";

	const float LabelFactory::_v_fix = 0.375f;
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	const float LabelFactory::BIG_FONT = 48;
	const float LabelFactory::HUGE_FONT = 150;
	const float LabelFactory::MEDIUM_FONT = 36;
  const float LabelFactory::SOMEWHAT_SMALL_FONT = 20 - 4;
	const float LabelFactory::SMALL_FONT = 20;
	const char* const LabelFactory::DEFAULT_FONT = "Segoe UI";

	const float LabelFactory::_v_fix = 0.375f;
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID


