#ifndef RESTORABLEDEVASSET_H
#define RESTORABLEDEVASSET_H

class RestorableDevAsset {
public:
	virtual void RealiseLost() = 0;
	virtual void Restore() = 0;
};

#endif // RESTORABLEDEVASSET_H
