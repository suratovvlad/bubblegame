#ifndef __AUDIORESOURCE_H__
#define __AUDIORESOURCE_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "Core/Resource.h"

class AudioResourceLoader;

namespace MM {

class AudioManager;
class AudioSample;

enum class LoadMode {
	/// �������� �� ����� �� ���������� ���� �������, ������������� �� ��������� ������������
	OnDemand = 0,
	/// �������� �������
	Streamed = 1,
	/// ����� ����������� ���� �������, ������� �� �����������
	Cached = 2,
	/// �������� �������, ����������� ������� � ������ ����
	StreamedCached = 3
};

enum class VolumeMode {
	/// ������ SoundVolume
	Sound = 0,
	/// ������ MusicVolume
	Music = 1, 
	/// ������ Ambience 
	Ambience = 2 
};

///
/// �����������
///
class AudioResource : public Resource {
public:
	AudioResource();

	static AudioResource* CreateFromXml(rapidxml::xml_node<>* elem);

	const std::string& GetName() const { return id; }
	size_t GetMemoryInUse() const;

	const std::string& GetFileName() const { return filename; }
	LoadMode GetLoadMode() const { return loadMode; }
	int GetMix() const { return mix; }
	float GetVolumeFactor() const { return volumeFactor; }
	VolumeMode GetVolumeMode() const { return volumeMode; }
	float GetDefaultPan() const { return defaultPan; }
	bool IsPausable() const { return pausable; }

	AudioSample* CreateSample(AudioManager* manager, bool is_track);

private:
	friend class ::AudioResourceLoader;

	void InternalLoad();
	void InternalUnload();

private:
	std::string id;
	std::string filename;
	LoadMode loadMode;
	int mix;
	float volumeFactor;
	VolumeMode volumeMode;
	float defaultPan;
	bool pausable;
	
	boost::shared_ptr<std::vector<uint8_t>> data;
	int channels;
	int rate;
	int bits;

private:
	AudioResource(const AudioResource&);
	AudioResource& operator=(const AudioResource&);
};

typedef boost::intrusive_ptr<AudioResource> AudioResourcePtr;

} // namespace MM

#endif // __AUDIORESOURCE_H__
