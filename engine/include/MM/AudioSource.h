#ifndef __AUDIOSOURCE_H__
#define __AUDIOSOURCE_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "RefCounter.h"
#include "IO/Stream.h"

namespace MM {

///
/// Источник звуковых данных
///
/// Не занимается кешированием и прочим, просто позволяет прочитать различные данные
/// из разнообразных входных форматов в PCM
///
class AudioSource : public IO::InputStream {
public:
	AudioSource() {}
	
	/// Возвращает количество каналов (обычно 1 или 2)
	virtual int GetChannels() const = 0;
	
	/// Возвращает частоту дискретизации
	virtual int GetRate() const = 0;
	
	/// Возвращает количество бит на выборку (обычно 8, 16, 32)
	virtual int GetBits() const = 0;
	
	/// Возвращает размер данных в байтах
	virtual size_t GetLengthInBytes() const = 0;
	
	/// Проверяет, достигнут ли конец данных
	/// (При работе с неблокирующими источниками Read может возвращать 0 при недостигнутом конце)
	virtual bool IsEof() const = 0;
	
	/// Пытается прочитать указанное количество байт из источника, пока не будет достигнут конец данных
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
