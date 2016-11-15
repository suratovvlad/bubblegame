#ifndef __CORE_SYSTEMDIALOG_H__
#define __CORE_SYSTEMDIALOG_H__

#include "types.h"
#include <boost/function.hpp>

class SystemDialog
{
public:
	typedef boost::function<void()> CallbackType;

	enum class ButtonType {
		Normal,
		Cancel
	};

	SystemDialog();

	void SetCaption(const std::string &textId);

	void SetText(const std::string &textId);

	// Опциональная обработка отмены; если указана ф-ция, то для диалога разрешается
	// отмена (напр. кнопкой Back), в случае отмены вызывается указанная ф-ция
	void SetOnCancelCallback(CallbackType callback);

	void AddButton(const std::string &textId, CallbackType callback, ButtonType type = ButtonType::Normal);

	void Show();

private:
	bool _shown;

	std::string _caption;

	std::string _text;

	struct Button {
		std::string text;
		ButtonType type;
		CallbackType callback;

		Button(const std::string &textId, CallbackType callback, ButtonType type);
	};

	typedef std::vector<Button> Buttons;

	Buttons _buttons;

	CallbackType _cancelCallback;

	friend void RunDialogCallback(SystemDialog *dialog, int number);

};

#endif //__CORE_SYSTEMDIALOG_H__
