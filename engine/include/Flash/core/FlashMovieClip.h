#pragma once

#include <map>
#include <vector>
#include <string>
#include <boost/shared_array.hpp>
#include <boost/intrusive_ptr.hpp>

#include "IPrototype.h"
#include "IFlashMovieClip.h"
#include "FlashDisplayObjectContainer.hpp"
#include "FlashUnknown.hpp"
#include "DecoderContext.h"

//-----------------------------------------------------------------------------
struct IMovieClipDecoder;

//-----------------------------------------------------------------------------
class FlashMovieClip:
	public IPrototype,
	public FlashDisplayObjectContainer<IFlashMovieClip>
{
BEGIN_INTERFACE_MAP()
	INTERFACE_ENTRY(IPrototype)
	INTERFACE_ENTRY(IFlashMovieClip)
	INTERFACE_ENTRY(IFlashSprite)
	INTERFACE_ENTRY(IFlashDisplayObject)
END_INTERFACE_MAP()

public:
	FlashMovieClip();
	FlashMovieClip(FlashMovieClip& _ref);
	virtual ~FlashMovieClip();

	void addLibItem(IFlashDisplayObject* _item);

	void setCodec(const boost::intrusive_ptr<IMovieClipDecoder>& _codec);
	const boost::intrusive_ptr<IMovieClipDecoder>& getCodec() const;

	//---------------------------------------------------------------------------
	//
	//                        IDisplayObject
	//
	//---------------------------------------------------------------------------
	bool hitTest(float x, float y, IHitTestDelegate* hitTestDelegate);
	void advance(FlashUpdateListener* updateListener, float dt);
	bool playing() const { return isPlaying; }

	//---------------------------------------------------------------------------
	//
	//                        IFlashSprite
	//
	//---------------------------------------------------------------------------
	IFlashDisplayObject* removeChildAt(int _index);

	//---------------------------------------------------------------------------
	//
	//                        IFlashMovieClip
	//
	//---------------------------------------------------------------------------
	float getFps();
	int nextFrame();
	int prevFrame();
	int gotoFrame(int frameId);
	int gotoLabel(const std::string& label);
	int getCurrentFrame();
	void setPlayback(bool value);
	void setLooping(bool isLooping);
	void setLoop(int startFrame, int endFrame);
	int resolveLabelFrame(const std::string& label);
	void setPlaybackOperation(IPlaybackOperation* playbackOperation);
	int countFrames();

	//----------------------------------------------------------------------------
	//
	//                   CFlashMovieClipEncoderVisitor
	//
	//----------------------------------------------------------------------------
	void visitRotateChildren(int index1, int index2);
	void visitAttach(unsigned int id, unsigned char (&_color)[3], float _alpha, float (&_matrix)[6]);
	void visitDetach(unsigned int id, int index);
	void visitAttachAt(unsigned int id, int index, unsigned char (&_color)[3], float alpha, float (&_matrix)[6]);
	void visitBakeFrame();
	void visitColor(int index, unsigned char (&_color)[3]);
	void visitAlpha(int index, unsigned char alpha);
	void visitKeyFrame();
	void visitGetMatrix(int _libid, float* _matrix);
	void visitSetMatrix(int _libid, float* _matrix);

	//---------------------------------------------------------------------------
	//
	//
	//
	//---------------------------------------------------------------------------
private:
	int __gotoFrame(int _frameNum);
	void __advanceIterate(FlashUpdateListener* updateListener, float dt);
	bool __needAdvanceFrame();
	void __updateAdvanceFrameStatus();
	void __destroyChildren();

protected:
	GC_BLACKEN_DECL();

public:
	static float fps;

private:
	CDecoderContext __m_codecContext;
	bool isPlaying;
	bool advanceFrame;
	bool isLooping;
	int loopStart, loopEnd;
	float framePiece;
	IPlaybackOperation* playbackOperation;
	std::vector<IFlashDisplayObject*> __m_library;
	boost::intrusive_ptr<IMovieClipDecoder> __m_codec;
};
