#ifndef TRIE_HPP
# define TRIE_HPP

#include <vector>
#include <string>

template <typename T>
class Trie {
	public:
		Trie();
		Trie(std::string key, T element);
		Trie(std::string key, T element, bool leaf);
		~Trie();
		bool		add(std::string key, T element);
		T			&operator[](std::string key) const;
		void		create_graph(void) const;
		std::string	get_key(void) const;
		void		set_key(std::string key);
		std::string	get_elem(void) const;
		void		set_elem(T element);
		bool		get_leaf(void) const;
		Trie		_nodes[256];
	private:
		std::string	_key;
		T			_element;
		bool		_leaf;
};

#endif