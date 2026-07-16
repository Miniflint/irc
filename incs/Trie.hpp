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
		bool		del(std::string key);
		void    	addNode(Trie<T> *node);
		T			&operator[](std::string key) const;
		void		createGraph(void);
		void		createGraph(const char *filename);
		std::string	getKey(void) const;
		void		setKey(std::string key);
		T			&getElem(void);
		void		setElem(T element);
		bool		getLeaf(void) const;
		void		setLeaf(bool leaf);
		bool		isIn(std::string key);
		Trie<T>		*find(std::string key);
		Trie<T>		*_nodes[256];
	private:
		std::string	_key;
		T			_element;
		bool		_leaf;
};

# include "Trie.tpp"

#endif
