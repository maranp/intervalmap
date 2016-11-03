/*
 * mymap.cpp
 *
 *  Created on: 02-Nov-2016
 *      Author: maran
 */

#include <map>
#include <limits>
#include <iostream>
#include <iterator>

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

		iterator_t lbBegin = m_map.lower_bound(keyBegin); // the first entry in the map whose key is >= keyBegin
		iterator_t ubBegin = m_map.upper_bound(keyBegin); // the first entry in the map whose key is > keyBegin
		iterator_t delBegin;
		K searchBeginKey;
		delBegin = lbBegin; // the iterator from where the deletion of entry should start
		searchBeginKey = lbBegin->first; // set the search iterator to an entry earlier to where the new key will be inserted.
										 // this helps to merge the map if the values of consequtive entries match
		if (--lbBegin != m_map.end()) {
			searchBeginKey = lbBegin->first;
		}

		iterator_t lbEnd = m_map.lower_bound(keyEnd);
		iterator_t ubEnd = m_map.upper_bound(keyEnd);
		iterator_t delEnd;
		K searchEndKey;
		if (lbEnd == ubEnd) // the condition is true when keyEnd does not match with any key.
			--lbEnd;
		delEnd = lbEnd;
		V tailVal = delEnd->second; // the value to be set for the last entry in the modified range.
		searchEndKey = lbEnd->first;

		m_map.erase(delBegin, ++delEnd); // end is open interval so, advance the iterator

		m_map.insert(std::begin(m_map), std::make_pair(keyBegin, val));
		m_map.insert(std::begin(m_map), std::make_pair(keyEnd, tailVal));

		iterator_t it = m_map.find(searchBeginKey); //searchBegin;
		V prevVal = it->second;
		it++;
		iterator_t endIt = m_map.find(searchEndKey);
		endIt++;
		while (it != endIt) {
			if (it->second == prevVal) {
				iterator_t delIt = it;
				it++;
				m_map.erase(delIt);
			} else {
				prevVal = it->second;
				it++;
			}
		}
	}

	void test_interval_map() {
		m_map.insert(std::make_pair(1, 'b'));
		m_map.insert(std::make_pair(4, 'c'));
		m_map.insert(std::make_pair(7, 'd'));
		m_map.insert(std::make_pair(10, 'e'));
		m_map.insert(std::make_pair(13, 'a'));
	}

	// a print function for debugging
	void show() {
		std::cout << "show" << std::endl;
		for(auto entry : m_map) {
			std::cout << entry.first << entry.second << std::endl;
		}
	}

private:
	std::map<K,V> m_map;
};

int main() {
	mymap<unsigned int, char> imap {'a'};
	imap.test_interval_map();
	imap.show();
	//imap.assign(8, 10, 'k');
	//imap.assign(8, 12, 'k');
	//imap.assign(2, 12, 'k');
	//imap.assign(2, 12, 'b');
	//imap.assign(5, 12, 'b');
	//imap.assign(4, 10, 'b');
	//imap.assign(4, 12, 'b');
	//imap.assign(7, 13, 'a');
	//imap.assign(0, 10, 'e');
	//imap.assign(0, 10, 'e');
	imap.assign(1, 13, 'a');
	imap.show();
}
