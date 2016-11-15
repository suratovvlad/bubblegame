#ifndef __AUDIOSOURCE_H__
#define __AUDIOSOURCE_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "RefCounter.h"
#include "IO/Stream.h"

namespace MM {

///
/// �������� �������� ������
///
/// �� ���������� ������������ � ������, ������ ��������� ��������� ��������� ������
/// �� ������������� ������� �������� � PCM
///
class AudioSource : public IO::InputStream {
public:
	AudioSource() {}
	
	/// ���������� ���������� ������� (������ 1 ��� 2)
	virtual int GetChannels() const = 0;
	
	/// ���������� ������� �������������
	virtual int GetRate() const = 0;
	
	/// ���������� ���������� ��� �� ������� (������ 8, 16, 32)
	virtual int GetBits() const = 0;
	
	/// ���������� ������ ������ � ������
	virtual size_t GetLengthInBytes() const = 0;
	
	/// ���������, ��������� �� ����� ������
	/// (��� ������ � �������������� ����������� Read ����� ���������� 0 ��� ������������� �����)
	virtual bool IsEof() const = 0;
	
	/// �������� ��������� ��������� ���������� ���� �� ���������, ���� �� ����� ��������� ����� ������
	void ReadSome(std::vector<uint8_t>& buffer, size_t size);

    static AudioSource* FromStream(IO::InputStream* stream);
	
	static AudioSource* FromBuffer(const boost::shared_ptr<std::vector<uint8_t>>& buffer, int channels, int rate, int bits);
	
	static AudioSource* FromFileOgg(const std::string& filename);
	
	//static AudioSource* FromFileAiff(const std::string& filename));
	
	static AudioSource* FromFile(const std::string& filename);

private:
	AudioSource(const AudioSource&);
	AudioSource& operator=(const AudioSource&);
};

typedef boost::intrusive_ptr<AudioSource> AudioSourcePtr;

} // namespace MM

#endif // __AUDIOSOURCE_H__
