#ifndef _GUI_EDITBOX_H_
#define _GUI_EDITBOX_H_

#include "GUI/Widget.h"
#include "Render/RenderFunc.h"

namespace GUI
{

class FTEditBox
	: public GUI::Widget
{
public:
	FTEditBox(const std::string& name, rapidxml::xml_node<>* elem);
	void Update(float dt) override;
	virtual void Draw() override;
	virtual void AcceptMessage(const Message& message) override;
	virtual Message QueryState(const Message& message) const override;
	virtual bool MouseDown(const IPoint& mouse_pos) override;

	void SetChangeCallback(luabind::object obj);

protected:
	std::string GetUtf8Text() const;
	bool SetText(std::wstring text);
	bool SetText(std::string text);

protected:
	std::wstring _text;
	int _limit;
	size_t _ibeamPos;

	std::string _font;
	std::string _filterFont;	//дополнительный шрифт для фильтрации символов. может быть полезно если для вывода текста будет использоваться не тот же шрифт каким он вводится в EditBox
	bool _centered;
	int _adjustWidth;

	std::set<int> _denied;
	float _timer;
	float _kbTimer; // “‡ÈÏÂ ‰Îˇ ÔÓ‚ÂÍË Ì‡ÎË˜Ëˇ ÍÎ‡‚Ë‡ÚÛ˚
	bool _enabled;  // ¿ÍÚË‚ÌÓ ÎË ÔÓÎÂ ‰Îˇ ‚‚Ó‰‡ - ÌÛÊÌÓ ÎË ÔÓÍ‡Á˚‚‡Ú¸ ÍÎ‡‚Ë‡ÚÛÛ
	bool _uppercase;// œÂÂ‚Ó‰ËÚ¸ ‚ÒÂ ·ÛÍ‚˚ ‚ Á‡„Î‡‚Ì˚Â.

	luabind::object _onTextChanged;		// Œ·‡·ÓÚ˜ËÍ ÒÓÓ·˘ÂÌËˇ Ó· ËÁÏÂÌÂÌËË ÚÂÍÒÚ‡
};

}

#endif
