#ifndef _DATASTORE_H_
#define _DATASTORE_H_

#include "Utils/IRect.h"
#include "Utils/IPoint.h"

#include <boost/variant.hpp>

class DataVariable
{
public:
	enum VARIABLE_TYPE { TYPE_NONE, TYPE_INT, TYPE_FLOAT, TYPE_DOUBLE, TYPE_STRING, TYPE_BOOLEAN, TYPE_POINT, TYPE_RECT, TYPE_ARRAY };

	DataVariable();

	void Load(rapidxml::xml_node<>* elem);
	void Load(pugi::xml_node elem);
	void Save(rapidxml::xml_node<>* elem) const;
	void Save(pugi::xml_node elem) const;

	void Load(const std::string &strType, const std::string &strValue);
	void Save(std::string &strType, std::string &strValue) const;

	VARIABLE_TYPE getType() const;
	bool getBool() const;
	int getInt() const;
	float getFloat() const;
	double getDouble() const;
	std::string getString() const;
	const IPoint& getPoint() const;
	const IRect &getRect() const;

	DataVariable& element(int index);
	const DataVariable& getElement(int index) const;
	DataVariable& appendElement();
	int arraySize() const;

	void setBool(bool value);
	void setInt(int value);
	void setFloat(float value);
	void setDouble(double value);
	void setString(const std::string &value);
	void setPoint(const IPoint &value);
	void setRect(const IRect &value);

private:
	friend struct GetStringVisitor;

	struct None {};

	typedef boost::variant<
		None, bool, int, float, double, std::string, IPoint, IRect, std::vector<DataVariable>
	> Variant;

	Variant _var;
};

class DataStore
{
public:
	void Clear();

	/// Загружает данные, предварительно очищая существующие
	void Load(rapidxml::xml_node<>* elem);
	void Load(pugi::xml_node elem);

	/// Загружает данные, не очищая существующие (с перезаписью данных)
	void LoadAppend(rapidxml::xml_node<>* elem);
	void LoadAppend(pugi::xml_node elem);

	void Save(rapidxml::xml_node<>* elem);
	void Save(pugi::xml_node elem);

	void LoadCSV(const std::string &filename);
	void SaveCSV(const std::string &filename);

	bool findName(const std::string &name) const;
	DataVariable::VARIABLE_TYPE variableType(const std::string &name) const;
	void erase(const std::string &name);

	bool getBool(const std::string &varName, bool def = false) const;
	int getInt(const std::string &varName, int def = 0) const;
	float getFloat(const std::string &varName, float def = 0.0f) const;
	double getDouble(const std::string &varName, double def = 0.0f) const;
	std::string getString(const std::string &varName, const std::string &def = "") const;
	IPoint getPoint(const std::string &varName, const IPoint &def = IPoint()) const;
	IRect getRect(const std::string &varName, const IRect &def = IRect()) const;

	bool getArrBool(const std::string &varName, int index, bool def = false);
	int getArrInt(const std::string &varName, int index, int def = 0);
	float getArrFloat(const std::string &varName, int index, float def = 0.0f);
	double getArrDouble(const std::string &varName, int index, double def = 0.0f);
	std::string getArrString(const std::string &varName, int index, const std::string &def = "");
	IPoint getArrPoint(const std::string &varName, int index, const IPoint &def = IPoint());
	IRect getArrRect(const std::string &varName, int index, const IRect &def = IRect());
	int getArraySize(const std::string &varName) const;
	
	void setBool(const std::string &varName, bool value);
	void setInt(const std::string &varName, int value);
	void setFloat(const std::string &varName, float value);
	void setDouble(const std::string &varName, double value);
	void setString(const std::string &varName, const std::string &value);
	void setPoint(const std::string &varName, const IPoint &value);
	void setRect(const std::string &varName, const IRect &value);

	void setArrBool(const std::string &varName, int index, bool value);
	void setArrInt(const std::string &varName, int index, int value);
	void setArrFloat(const std::string &varName, int index, float value);
	void setArrDouble(const std::string &varName, int index, double value);
	void setArrString(const std::string &varName, int index, const std::string &value);
	void setArrPoint(const std::string &varName, int index, const IPoint &value);
	void setArrRect(const std::string &varName, int index, const IRect &value);

private:
	static std::string DotToComma(const std::string &str);
	static std::string CommaToDot(const std::string &str);

private:
	typedef std::map<std::string, DataVariable> Data;
	Data _data;
};

#endif
