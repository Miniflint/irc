#include "trie.hpp"

template <typename T>
Trie<T>::Trie() : _key(""), _element(), _leaf(false), _del(NULL)
{
	for (unsigned int i = 0; i < 256; i++)
		this->_nodes[i] = NULL;
}

template <typename T>
Trie<T>::Trie(std::string key) : _key(key), _element(), _leaf(false), _del(NULL)
{
	for (unsigned int i = 0; i < 256; i++)
		this->_nodes[i] = NULL;
}

template <typename T>
Trie<T>::Trie(std::string key, T element) : _key(key), _element(element), _leaf(false), _del(NULL)
{
	for (unsigned int i = 0; i < 256; i++)
		this->_nodes[i] = NULL;
}

template <typename T>
Trie<T>::Trie(std::string key, T element, bool leaf) : _key(key), _element(element), _leaf(leaf), _del(NULL)
{
	for (unsigned int i = 0; i < 256; i++)
		this->_nodes[i] = NULL;
}

template <typename T>
Trie<T>::~Trie() {
	for (int i = 0; i < 256; ++i) {
		if (this->_nodes[i]) {
			delete this->_nodes[i];
			this->_nodes[i] = NULL;
		}
	}
}

template <typename T>
std::string	Trie<T>::get_key(void) const
{
    return (this->_key);
}

template <typename T>
void	Trie<T>::set_key(std::string key) {
    this->_key = key;
}

template <typename T>
T	&Trie<T>::get_elem(void)
{
    return (this->_element);
}

template <typename T>
void	Trie<T>::set_elem(T elem) {
    this->_element = elem;
}

template <typename T>
bool	Trie<T>::get_leaf(void) const
{
    return (this->_leaf);
}

template <typename T>
void	Trie<T>::set_leaf(bool leaf)
{
	this->_leaf = leaf;
}

template <typename T>
void	Trie<T>::add_node(Trie<T> *node)
{
	this->_nodes[static_cast<unsigned char>(node->get_key()[0])] = node;
}

static int diff_index(std::string s1, std::string s2)
{
	int i;
	for (i = 0; s1[i] && s2[i] && s1[i] == s2[i]; i++);
	return (i);
}

template <typename T>
bool    Trie<T>::add(std::string new_key, T element)
{
    Trie<T>    *next_node = this->_nodes[static_cast<unsigned char>(new_key[0])];
	if (!next_node) {
		this->_nodes[static_cast<unsigned char>(new_key[0])] = new Trie<T>(new_key, element, true);
		return (true);
	}
	std::string key = next_node->get_key();
	int diff_i = diff_index(key, new_key);
	key.erase(0, diff_i);
	new_key.erase(0, diff_i);
	Trie<T>	*new_node;
	if (key.empty())
		new_node = next_node;
	else {
		std::string	com_key = next_node->get_key().substr(0, diff_i);
		new_node = new Trie<T>(com_key);
		next_node->set_key(key);
		new_node->add_node(next_node);
		this->_nodes[static_cast<unsigned char>(com_key[0])] = new_node;
	}
	if (new_key.empty()) {
		new_node->set_elem(element);
		new_node->set_leaf(true);
		return (true);
	}
	return (new_node->add(new_key, element));
}

template <typename T>
bool	Trie<T>::del(std::string key) {
	if (key == this->_key && this->_leaf) {
		this->_leaf = false;
		for (int i = 0; i < 256; ++i) {
			if (this->_nodes[i])
				return (false);
		}
		return (true);
	}
	int	i_diff = diff_index(this->_key, key);
	if (i_diff < this->_key.length())
		return (false);
	key.erase(0, i_diff);
	Trie<T>		*next_node = this->_nodes[static_cast<unsigned char>(key[0])];
	if (next_node) {
		if (next_node->del(key))
		{
			delete this->_nodes[static_cast<unsigned char>(key[0])];
			this->_nodes[static_cast<unsigned char>(key[0])] = NULL;
			if (!this->_leaf)
			{
				for (int i = 0; i < 256; ++i) {
					if (this->_nodes[i])
						return (false);
				}
				return (true);
			}
		}
	}
	return (false);
}

template <typename T>
T 			&Trie<T>::operator[](std::string key) const
{
	Trie<T>	*next_node = this->_nodes[static_cast<unsigned char>(key[0])];
	if (!next_node)
		throw std::exception();
	std::string	next_key = next_node->get_key();
	if (next_key.length() > key.length())
		throw std::exception();
	if (next_key == key)
	{
		if (next_node->get_leaf())
			return (next_node->get_elem());
		throw std::exception();
	}
	int	i_diff = diff_index(next_key, key);
	return ((*next_node)[std::string(key.c_str() + i_diff)]);
}

template <typename T>
void	create_graph_root(Trie<T> *root, std::ofstream &f)
{
	int i = 0;
	f << "\t\"" << root << "\" [label=\"" << root->get_key() << "\n" << root->get_leaf() << "\"]" << std::endl;
	while (i < 256)
	{
		if (root->_nodes[i] != NULL)
		{
			create_graph_root(root->_nodes[i], f);
			f << "\t\"" << root << "\" -> \"" << root->_nodes[i] << "\""<< std::endl;
		}
		i++;
	}
}

template <typename T>
void	Trie<T>::create_graph(void)
{
	std::ofstream f("t.dot");

	f << "digraph viz {" << std::endl;
	create_graph_root(this, f);
	f << "}" << std::endl;
	f.close();
}