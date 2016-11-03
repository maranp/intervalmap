/*
 * mymap.cpp
 *
 *  Created on: 02-Nov-2016
 *      Author: maran
 */

#include <map>
#include <limits>
#include <iostream>

template <typename K,typename V>
class mymap {
public:
	mymap(V const & val) {
		m_map.insert(m_map.begin(),
					std::make_pair(std::numeric_limits<K>::min(), val));
	}
	V & operator [] (K const & key) {
		return (--m_map.upper_bound(key))->second;
	}

	void assign(K const & keyBegin, K const & keyEnd, V const & val) {
		std::cout << "(" << keyBegin << "," << keyEnd << "," << val << ")\n";

		using iterator_t = typename std::map<K, V>::iterator;

		iterator_t delBegin = m_map.upper_bound(keyBegin);
		m_map.insert(delBegin, std::make_pair(keyBegin, val));

		// find the position after which keyEnd needs to be inserted
		iterator_t delEnd = m_map.upper_bound(keyEnd);
		delEnd--;
		// the value at that position is the new value of keyEnd.
		// So create an entry with keyEnd and value at the inserted position
		m_map.insert(delEnd, std::make_pair(keyEnd, delEnd->second));

		if (delEnd->first != keyEnd) delEnd++;
		m_map.erase(delBegin, delEnd);
	}

	void test_interval_map() {
		m_map.insert(std::make_pair(1, 'b'));
		m_map.insert(std::make_pair(4, 'c'));
		m_map.insert(std::make_pair(7, 'd'));
		m_map.insert(std::make_pair(10, 'e'));
		m_map.insert(std::make_pair(13, 'a'));
	}
	void show() {
		std::cout << "show" << std::endl;
		for(auto entry : m_map) {
			std::cout << entry.first << entry.second << std::endl;
		}

//		for (auto i = 0; i < 14; i++) {
//			std::cout << this->operator [](i) <<std::endl;
//		}
	}

private:
	std::map<K,V> m_map;
};

int main() {
	mymap<unsigned int, char> imap {'a'};
	imap.test_interval_map();
	imap.show();
	//imap.assign(8, 10, 'k');
	//map.assign(8, 12, 'k');
	//imap.assign(2, 12, 'k');
	//imap.assign(2, 12, 'b');
	imap.assign(4, 12, 'b');
	imap.show();
}
