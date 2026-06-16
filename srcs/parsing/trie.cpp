#include "trie.hpp"

template <typename T>
static int util_get_index(Trie<T> *root, std::string inserter)
{
	for (int i = 0; root->get_key()[i] && inserter[i] && root->get_key()[i] == inserter[i]; i++) ;
	if (root->get_key().length() >= inserter.length())
		return (-i);
	return (i);
}

template <typename T>
Trie<T>::Trie() {}

template <typename T>
Trie<T>::Trie(std::string key, T element) : _key(key), _element(element), _leaf(false)
{
	for (unsigned int i = 0; i < 256; i++)
		this->_nodes[i] = NULL;
}

template <typename T>
Trie<T>::Trie(std::string key, T element, bool leaf) : _key(key), _element(element), _leaf(leaf)
{
	for (unsigned int i = 0; i < 256; i++)
		this->_nodes[i] = NULL;
}

template <typename T>
Trie<T>::~Trie() {}

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
std::string	Trie<T>::get_elem(void) const
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
bool	recur(Trie<T> root, std::string key, T element)
{
	int	i;

	Trie<T>	*next_node = root->_nodes[key[0]];
	if (!next_node) {
		root->_nodes[key[0]] = new Trie<T>(key, element, true);
		return (true);
	}
	i = root->util_get_index(key);
	if (i > 0)
		return (recur(next_node, key.substr(i, key.length() - i)));
	else if (i < 0) {
		next_node->set_key(next_node->get_key().substr(-i, next_node->get_key().length() + i));
		Trie<T> *inserted = new Trie<T>(key, element, true);
		inserted->_nodes[next_node->get_key()[0]] = next_node;
		inserted->set_elem(element);
		root->_nodes[key[0]] = inserted;
		return (recur(inserted, key.substr(-i, key.length() + i), element));
	} else
		next_node->_element = element;
	return (true);
}

template <typename T>
bool    Trie<T>::add(std::string key, T element)
{
	return (recur(this/*)*/, key, element);
}

template <typename T>
static int diff_index(std::string key)
{
	for (int i = 0; this->_key[i] && key[i] && this->_key[i] == key[i]; i++);
	return (i);
}

template <typename T>
bool    /*Trie<T>::*/add2(std::string key, T element)
{
	int	diff_i;
	int	size_diff;

    Trie    *next_node = root->_nodes[key[0]];
	if (!next_node) {
		root->_nodes[key[0]] = new Trie(key, element);
        return (true);
	}
	diff_i = diff_index(key);
	size_diff = this->_key.length() - key.length();
	if (!size_diff && diff_i == key.length())
		this->_element = element;
	else if (size_diff > 0) { // this->_key plus long
		
	} else { // key plus long
		
	}
}

template <typename T>
T 			&Trie<T>::operator[](std::string key) const
{

}

template <typename T>
void	Trie<T>::create_graph(void) const
{

}
