#include <iostream>
#include <string>
#include <deque>

#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	#include <set>
	namespace ft = std;

	template<typename T>
	void	print_vector(std::vector<T>& v, size_t id = 0, const std::string& delimiter = " ")
	{
		std::cout << "vector" << id << ": " << "[ ";
		for (typename std::vector<T>::iterator it1 = v.begin(); it1 != v.end(); ++it1)
			std::cout << *it1 << delimiter;
		std::cout << "]" << std::endl;
	}

	template<typename T, typename U>
	void	print_map(const std::map<T, U>& m, std::string comment = "")
	{
		std::cout << comment;
		for (typename std::map<T, U>::const_iterator it = m.begin(); it != m.end(); it++)
			std::cout << it->first << " = " << it->second << "; ";
		std::cout << '\n';
	}

	template<typename T>
	void print_set(const std::set<T>& s, std::string comment = "")
	{
		std::cout << comment;
		for (typename std::set<T>::const_iterator it = s.begin(); it != s.end(); it++)
			std::cout << *it << " -> ";
		std::cout << "(end)" << std::endl;
	}


	template<typename T>
	void	print_stack(std::stack<T> s, size_t id = 0, const std::string& delimiter = "\n")
	{
		size_t n_elems = s.size();
		std::cout << "stack" << id << ":\n";
		for (; !s.empty(); --n_elems)
		{
			std::cout << "[ " << s.top() << " ]" << delimiter;
			s.pop();
		}
	}

#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
	#include "set.hpp"

	template<typename T>
	void	print_vector(ft::vector<T>& v, size_t id = 0, const std::string& delimiter = " ")
	{
		std::cout << "vector" << id << ": " << "[ ";
		for (typename ft::vector<T>::iterator it1 = v.begin(); it1 != v.end(); ++it1)
			std::cout << *it1 << delimiter;
		std::cout << "]" << std::endl;
	}

	template<typename T, typename U>
	void	print_map(const ft::map<T, U>& m, std::string comment = "")
	{
		std::cout << comment;
		for (typename ft::map<T, U>::const_iterator it = m.begin(); it != m.end(); it++)
			std::cout << it->first << " = " << it->second << "; ";
		std::cout << '\n';
	}

	template<typename T>
	void	print_stack(ft::stack<T> s, size_t id = 0, const std::string& delimiter = "\n")
	{
		size_t n_elems = s.size();
		std::cout << "stack" << id << ":\n";
		for (; !s.empty(); --n_elems)
		{
			std::cout << "[ " << s.top() << " ]" << delimiter;
			s.pop();
		}
	}

	template<typename T>
	void print_set(const ft::set<T>& s, std::string comment = "")
	{
		std::cout << comment;
		for (typename ft::set<T>::const_iterator it = s.begin(); it != s.end(); it++)
			std::cout << *it << " -> ";
		std::cout << "(end)" << std::endl;
	}


#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			(void)vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;

	/* vector tests */

	ft::vector<int> v1;
	print_vector(v1, 1);

	ft::vector<int> v2(size_t(8), int(42));
	print_vector(v2, 2);

	ft::vector<int>::iterator it_tmp1 = v2.begin() + 1;
	ft::vector<int>::iterator it_tmp2 = v2.end() - 2;
	ft::vector<int> v3(it_tmp1, it_tmp2);
	print_vector(v3, 3);

	ft::vector<int> v4(v3);
	print_vector(v4, 4);

	ft::vector<int> v5 = v4;
	print_vector(v5, 5);

	std::cout << "v1 is empty: "<< v1.empty() << std::endl;
	std::cout << "v5 is empty: "<< v5.empty() << std::endl;

	std::cout << "v1 has size " << v1.size() << " and capacity " << v1.capacity() << std::endl;
	std::cout << "v5 has size " << v5.size() << " and capacity " << v5.capacity() << std::endl;

	std::cout << "v1 has max size of " << v1.max_size() << std::endl;
	std::cout << "v5 has max size of " << v5.max_size() << std::endl;

	v5.resize(20);
	print_vector(v5, 5);
	std::cout << v5[v5.size() - 1] << std::endl;
	std::cout << v5.at(v5.size() - 1) << std::endl;

	std::cout << v5.front() << std::endl;
	std::cout << v5.back() << std::endl;

	ft::vector<int> v6;
	v6.assign(7, 100);
	print_vector(v6, 6);

	ft::vector<int>::iterator v6_it1 = v5.begin() + 3;
	ft::vector<int>::iterator v6_it2 = v5.end() - 7;

	v6.assign(v6_it1, v6_it2);
	print_vector(v6, 6);

	ft::vector<int>::iterator v6_it3 = v6.begin() + 3;
	v6.erase(v6_it3);
	print_vector(v6, 6);

	ft::vector<int>::iterator v6_it4 = v6.begin() + 1;
	ft::vector<int>::iterator v6_it5 = v6.begin() + 6;
	v6.erase(v6_it4, v6_it5);
	print_vector(v6, 6);

	ft::vector<int>::iterator it1;
	ft::vector<int>::iterator it2;
	ft::vector<int>::iterator it3;
	ft::vector<int>::const_iterator it_const;
	ft::vector<int>::reverse_iterator it_r;
	ft::vector<int>::const_reverse_iterator it_rconst;

	v1.reserve(12);
	v1.push_back( 0 );
	v1.push_back( 1 );
	v1.push_back( 2 );
	v1.push_back( 3 );
	v1.push_back( 4 );
	v1.push_back( 5 );
	v1.push_back( 6 );
	v1.push_back( 7 );
	v1.push_back( 8 );
	v1.push_back( 9 );
	v1.push_back( 10 );
	v1.push_back( 11 );

	print_vector(v1, 1);

	it1 = v1.begin();
	it2 = v1.begin() + 3;
	it3 = v1.end() - 1;

	std::cout << "it1 = v1.begin()" << std::endl;
	std::cout << "it2 = v1.begin() + 3" << std::endl;
	std::cout << "it3 = v1.end() - 2;" << std::endl;
	std::cout << std::endl;

	std::cout << "*(it1): " << *(it1) << std::endl;

	std::cout << "*(it1 + 1): " << *(it1 + 1) << std::endl;
	std::cout << "*(1 + it1): " << *(1 + it1) << std::endl;
	std::cout << "*(it2 - 1): " << *(it2 - 1) << std::endl;
	std::cout << "*(-1 + it2): " << *(-1 + it2) << std::endl;

	std::cout << "*(it1++): " << *(it1++) << " -> " << *it1 << std::endl;
	std::cout << "*(it2++): " << *(it2++) << " -> " << *it2 << std::endl;
	std::cout << "*(++it1): " << *(++it1) << " -> " << *it1 << std::endl;
	std::cout << "*(++it2): " << *(++it2) << " -> " << *it2 << std::endl;
	std::cout << "*(it1--): " << *(it1--) << " -> " << *it1 << std::endl;
	std::cout << "*(it2--): " << *(it2--) << " -> " << *it2 << std::endl;
	std::cout << "*(--it1): " << *(--it1) << " -> " << *it1 << std::endl;
	std::cout << "*(--it2): " << *(--it2) << " -> " << *it2 << std::endl;

	std::cout << "*(it1 += 3): " << *it1 << " -> " << *(it1 += 3) << std::endl;
	std::cout << "*(it2 += 3): " << *it2 << " -> " << *(it2 += 3) << std::endl;
	std::cout << "*(it1 -= 1): " << *it1 << " -> " << *(it1 -= 1) << std::endl;
	std::cout << "*(it2 -= 1): " << *it2 << " -> " << *(it2 -= 1) << std::endl;

	ft::reverse_iterator<ft::vector<int>::iterator> it4( v1.rbegin() + 6 );
	ft::reverse_iterator<ft::vector<int>::iterator> it5( v1.rbegin() );
	std::cout << "*(it4): " << *(it4) << std::endl;

	std::cout << "*(it4++): " << *(it4++) << " -> " << *it4 << std::endl;
	std::cout << "*(++it4): " << *(++it4) << " -> " << *it4 << std::endl;
	std::cout << "*(it4--): " << *(it4--) << " -> " << *it4 << std::endl;
	std::cout << "*(--it4): " << *(--it4) << " -> " << *it4 << std::endl;

	std::cout << "*(it4 + 3): " << *(it4 + 3) << std::endl;
	std::cout << "*(it4 - 3): " << *(it4 - 3) << std::endl;
	std::cout << "it4 - it5: " << it4 - it5 << std::endl;

	print_vector(v1, 1);
	print_vector(v2, 2);

	std::cout << std::boolalpha << (v1 == v2) << std::endl;
	std::cout << std::boolalpha << (v1 != v2) << std::endl;
	std::cout << std::boolalpha << (v1 < v2) << std::endl;
	std::cout << std::boolalpha << (v1 > v2) << std::endl;
	std::cout << std::boolalpha << (v1 >= v2) << std::endl;
	std::cout << std::boolalpha << (v1 <= v2) << std::endl;

	/* map */

	ft::map<std::string, int> m1;
	m1["CPU"] = 10;
	m1["GPU"] = 15;
	m1["RAM"] = 20;

	std::cout << m1.empty() << std::endl;

	print_map(m1, "Initial map: ");

	m1["CPU"] = 25;  // update an existing value
	m1["SSD"] = 30;  // insert a new value
	print_map(m1, "Updated map: ");

	// using operator[] with non-existent key always performs an insert
	std::cout << "m1[UPS] = " << m1["UPS"] << '\n';
	print_map(m1, "Updated map: ");
	
	m1.erase("GPU");
	print_map(m1, "After erase: ");
	
	std::cout << "m.size() = " << m1.size() << '\n';
	
	ft::map<std::string, int> m2 = m1;
	print_map(m1, "Copy constructed map: ");
		
	std::cout << std::boolalpha << "m1 and m2 are equivalent: " << (m1 == m2) << '\n';
	m2["PSU"] = 34;
	m2["Peripherals"] = 12;
	print_map(m2, "Updated map: ");
	std::cout << std::boolalpha << "m1 and m2 are equivalent: " << (m1 == m2) << '\n';
		
	m1.swap(m2);
	print_map(m2, "Swapped map: ");
	
	ft::map<std::string, int>::key_compare key_comp_map = m1.key_comp();
	ft::map<std::string, int>::value_compare val_comp_map = m1.value_comp();
	
	std::cout << std::boolalpha << "Python is lexicographically less than C: " << key_comp_map("Python", "C") << '\n';
	std::cout << (std::string("Python") < std::string("C")) << '\n';
	
	ft::map<std::string, int>::value_type value1_map = ft::make_pair("C", 2);
	ft::map<std::string, int>::value_type value2_map = ft::make_pair("C++", 7);
	
	std::cout << std::boolalpha << "C is lexicographically less than C++: " << val_comp_map(value1_map, value2_map) << '\n';
	std::cout << (std::string("C") < std::string("C++")) << '\n';
	
	ft::map<std::string, int>::iterator it01 = m1.find("SSD");
	(void)it01;
	std::cout << "Key \"SSD\" is in the map: " << m1.count("SSD") << '\n';
	std::cout << "Key \"Stereo\" is in the map: " << m1.count("Stereo") << '\n';

	m1.clear();
	std::cout << std::boolalpha << "Map is empty: " << m1.empty() << '\n';

	/* set */

	// Create a set of strings
	ft::set<std::string> s1;
	s1.insert("CPU");
	s1.insert("GPU");
	s1.insert("RAM");
	
	std::cout << s1.empty() << std::endl;
	
	print_set(s1, "Initial set: ");
	
	s1.insert("CPU");  // update an existing value
	s1.insert("SSD");  // insert a new value
	print_set(s1, "Updated set: ");
	
	s1.erase("GPU");
	print_set(s1, "After erase: ");
	
	std::cout << "m.size() = " << s1.size() << '\n';
	
	ft::set<std::string> s2 = s1;
	print_set(s2, "Copy constructed set: ");
		
	std::cout << std::boolalpha << "s1 and s2 are equivalent: " << (s1 == s2) << '\n';
	s2.insert("PSU");
	s2.insert("Peripherals");
	print_set(s2, "Updated set: ");
	std::cout << std::boolalpha << "s1 and s2 are equivalent: " << (s1 == s2) << '\n';
	
	s1.swap(s2);
	print_set(s2, "Swapped set: ");
	
	ft::set<std::string>::key_compare key_comp_set = s1.key_comp();
	ft::set<std::string>::value_compare val_comp_set = s1.value_comp();
	
	std::cout << std::boolalpha << "Python is lexicographically less than C: " << key_comp_set("Python", "C") << '\n';
	std::cout << (std::string("Python") < std::string("C")) << '\n';
	
	ft::set<std::string>::value_type value1_set = (std::string)"C";
	ft::set<std::string>::value_type value2_set = (std::string)"C++";
	
	std::cout << std::boolalpha << "C is lexicographically less than C++: " << val_comp_set(value1_set, value2_set) << '\n';
	std::cout << (std::string("C") < std::string("C++")) << '\n';
	
	ft::set<std::string>::iterator it01_set = s1.find("SSD");
	(void)it01_set;
	std::cout << "Key \"SSD\" is in the set: " << s1.count("SSD") << '\n';
	std::cout << "Key \"Stereo\" is in the set: " << s1.count("Stereo") << '\n';
	
	//s1.print();
	
	s1.clear();
	std::cout << std::boolalpha << "Map is empty: " << s1.empty() << '\n';



	return (0);
}
