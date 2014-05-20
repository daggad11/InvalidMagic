#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>

class Item {	
	public:
		Item();
		~Item();
	protected:
		int mass;
		int id;
		std::string type;
};

#endif
