#include <map>
#include <singleton.hpp>
#include <Utils\utils.hpp>

#define COUNT_POINTS "CountPoints"
#define BORN_TIME "BornTime"
#define LIFE_TIME "LifeTime"
#define MAX_SPEED "MaxSpeed"
#define MIN_SPEED "MinSpeed"
#define SCALE_MINI_BUBBLE "MiniBubbleScale"
#define MAX_SCALE_MACRO_BUBBLE "MacroBubbleMaxScale"
#define GOAL_PER_ROUND "GoalPerRound"
#define COEF_PARTICLES_POSITION "MiniBubbleCoefParticlesPosition"
#define THINNIHG_PARTICLES "MiniBubbleThinningParticles"
#define MAIN_THEME_TRACK "MainThemeTrack"

class SettingsManager : public Singleton<SettingsManager>
{
	std::map<std::string, std::string> m_settingsMap;

public:
	SettingsManager();
	~SettingsManager();
	void ReadSettingsFromFile(const std::string& filepath);
	std::string GetSettingByName(const std::string& setting_name, const std::string& defaultVal) const;
};