#ifndef TRIE_HPP
# define TRIE_HPP

#include <vector>
#include <string>
#include <fstream> 

template <typename T>
class Trie {
	public:
		Trie();
		Trie(std::string key);
		Trie(std::string key, T element);
		Trie(std::string key, T element, bool leaf);
		~Trie();
		bool		add(std::string key, T element);
		bool		add2(std::string key, T element);
		void    	add_node(Trie<T> *node);
		T			&operator[](std::string key) const;
		void		create_graph(void);
		std::string	get_key(void) const;
		void		set_key(std::string key);
		T			&get_elem(void);
		void		set_elem(T element);
		bool		get_leaf(void) const;
		void		set_leaf(bool leaf);
		Trie<T>		*_nodes[256];
	private:
		std::string	_key;
		T			_element;
		bool		_leaf;
};

# include "trie.tpp"

#endif