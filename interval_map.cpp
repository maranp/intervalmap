#include <assert.h>
#include <map>
#include <limits>
#include <iostream>

template<class K, class V>
class interval_map {
    friend void IntervalMapTest();

private:
    std::map<K,V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map( V const& val) {
      
      m_map.insert(m_map.begin(),std::make_pair(std::numeric_limits<K>::lowest(),val));
    };

    // Assign value val to interval [keyBegin, keyEnd). 
    // Overwrite previous values in this interval. 
    // Do not change values outside this interval.
    // Conforming to the C++ Standard Library conventions, the interval 
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval, 
    // and assign must do nothing.

    // look-up of the value associated with key
    V const & operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }

    void assign( K const& keyBegin, K const& keyEnd, const V& val ) {
    	typedef typename std::map<K, V>::iterator iterator_t;

    	if (keyBegin >= keyEnd)
    		return;

    	V upval = this->operator[](keyBegin); //new upper interval value right now
    	iterator_t idx = m_map.upper_bound(keyBegin);
    	idx--;

    	V upkey = idx->first + 1; //new upper interval key right now

    	if (idx->first != keyBegin)
    		idx++;

    	iterator_t end = m_map.lower_bound(keyEnd);
    	iterator_t tempit = idx;


    	while (idx != end) {
    		std::cout << "KK, V:" << idx->first << "," << idx->second << std::endl;
    		upval = idx->second;
    		upkey = idx->first + 1;
    		tempit++;
    		m_map.erase(idx);
    		idx = tempit;
    	}

    	m_map.insert(std::make_pair(keyBegin, val));
    	iterator_t mergeit = m_map.upper_bound(keyBegin);
    	mergeit--; mergeit--;
    	if (mergeit->second == val) {
    		mergeit++;
    		m_map.erase(mergeit);
    	}

    	m_map.insert(std::make_pair(keyEnd, upval));
    	mergeit = m_map.upper_bound(keyBegin);
    	mergeit--; mergeit--;
    	if (mergeit->second == val) {
    		mergeit++;
    		upkey = mergeit->first + 1;
    		m_map.erase(mergeit);
    		m_map.insert(std::make_pair(upkey, upval));
    	}
    }

  void insertor(K const &key, V const& val) {
    m_map.insert(std::make_pair(key, val));
  }
    
  void show() {
      for (typename std::map<K, V>::iterator it = m_map.begin();
	   it != m_map.end(); it++) {
	std::cout << "K, V:" << it->first << "," << it->second << std::endl;
      }
  }
};

void myconstruct(interval_map<unsigned int, char> &imap) {
  //imap.insert(0, 'a');
  imap.insertor(1, 'b');
  imap.insertor(4, 'c');
  imap.insertor(7, 'd');
  imap.insertor(10, 'e');
  imap.insertor(13, 'a');
  
  //imap.show();
  // for (typename std::map<unsigned int, char>::iterator it = m_map.begin();
  //      it != m_map.end(); it++) {
  //   std::cout << "K, V:" << it->first << "," << it->second << std::endl;
  // }

}

void lookuper(interval_map<unsigned int, char> &imap) {
  for (int i = 0; i < 13; i++) {
    std::cout << "lookup:" << i << "," << imap[i] << std::endl;
  }
}

void IntervalMapTest() {
  interval_map<unsigned int, char> imap = {'a'};
  myconstruct(imap);

  imap.show();

  //imap.assign(3, 8, 'f');
  //imap.assign(3, 8, 'b');
  imap.assign(7, 10, 'c');
  ////imap.assign(4, 8, 'f');
  //imap.assign(4, 7, 'f');
  //imap.assign(2, 6, 'f');
  //imap.assign(11, 15, 'f');
  //imap.assign(0, 5, 'f');
  //imap.assign(5, 6, 'f');
  
  std::cout << "after assign \n";
  imap.show();
  //lookuper(imap);
  return;
}

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a function IntervalMapTest() here that tests the
// functionality of the interval_map, for example using a map of unsigned int
// intervals to char.

int main(int argc, char* argv[]) {
    IntervalMapTest();
    std::cout <<"test\n";
    return 0;
}
