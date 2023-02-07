#pragma once
#include "CoreMath.h"
#include <json_spirit/json_spirit.h>

namespace Game
{

	//typedef std::set<std::string> properties;

	struct properties : public std::set<std::string>
	{
		using std::set<std::string>::set;

		bool has(const std::string& prop) const;
	};

	typedef json_spirit::mObject data;

	struct id
	{
	private:
		std::string owner;
		std::string name;
		std::string ownerCOLONname;

	public:
		std::string asString() const { return ownerCOLONname; }
		std::string getName() const { return name; }
		std::string getOwner() const { return owner; }

		id() {}
		id(const std::string& owner, const std::string& name) : owner(owner), name(name), ownerCOLONname(owner + ":" + name) {}
		id(const std::string& ownerCOLONname) : ownerCOLONname(ownerCOLONname) {
			Core::u32 p = ownerCOLONname.find(':', 0);
			if (p == std::string::npos) throw std::exception("Wrong id");
			owner = ownerCOLONname.substr(0, p);
			name = ownerCOLONname.substr(p + 1);
		}
	};

}