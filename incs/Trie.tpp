#include "Trie.hpp"

template <typename T>
Trie<T>::Trie() : _key(""), _element(), _leaf(false)
{
	for (unsigned int i = 0; i < 256; i++)
		this->_nodes[i] = NULL;
}

template <typename T>
Trie<T>::Trie(std::string key) : _key(key), _element(), _leaf(false)
{
	for (unsigned int i = 0; i < 256; i++)
		this->_nodes[i] = NULL;
}

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
Trie<T>::~Trie() {
	for (int i = 0; i < 256; ++i) {
		if (this->_nodes[i]) {
			delete this->_nodes[i];
			this->_nodes[i] = NULL;
		}
	}
}

template <typename T>
std::string	Trie<T>::getKey(void) const
{
    return (this->_key);
}

template <typename T>
void	Trie<T>::setKey(std::string key) {
    this->_key = key;
}

template <typename T>
T	&Trie<T>::getElem(void)
{
    return (this->_element);
}

template <typename T>
void	Trie<T>::setElem(T elem) {
    this->_element = elem;
}

template <typename T>
bool	Trie<T>::getLeaf(void) const
{
    return (this->_leaf);
}

template <typename T>
void	Trie<T>::setLeaf(bool leaf)
{
	this->_leaf = leaf;
}

template <typename T>
void	Trie<T>::addNode(Trie<T> *node)
{
	this->_nodes[static_cast<unsigned char>(node->getKey()[0])] = node;
}

static inline int diff_index(std::string s1, std::string s2)
{
	int i;
	for (i = 0; s1[i] && s2[i] && s1[i] == s2[i]; i++);
	return (i);
}

template <typename T>
bool    Trie<T>::add(std::string new_key, T element)
{
    Trie<T>    *nextNode = this->_nodes[static_cast<unsigned char>(new_key[0])];
	if (!nextNode) {
		this->_nodes[static_cast<unsigned char>(new_key[0])] = new Trie<T>(new_key, element, true);
		return (true);
	}
	std::string key = nextNode->getKey();
	const int diff_i = diff_index(key, new_key);
	key.erase(0, diff_i);
	new_key.erase(0, diff_i);
	Trie<T>	*new_node;
	if (key.empty())
		new_node = nextNode;
	else {
		std::string	com_key = nextNode->getKey().substr(0, diff_i);
		new_node = new Trie<T>(com_key);
		nextNode->setKey(key);
		new_node->addNode(nextNode);
		this->_nodes[static_cast<unsigned char>(com_key[0])] = new_node;
	}
	if (new_key.empty()) {
		new_node->setElem(element);
		new_node->setLeaf(true);
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
	size_t	i_diff = diff_index(this->_key, key);
	if (i_diff < this->_key.length())
		return (false);
	key.erase(0, i_diff);
	Trie<T>		*nextNode = this->_nodes[static_cast<unsigned char>(key[0])];
	if (nextNode) {
		if (nextNode->del(key))
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
	Trie<T>	*nextNode = this->_nodes[static_cast<unsigned char>(key[0])];
	if (!nextNode)
		throw std::exception();
	std::string	next_key = nextNode->getKey();
	if (next_key.length() > key.length())
		throw std::exception();
	if (next_key == key)
	{
		if (nextNode->getLeaf())
			return (nextNode->getElem());
		throw std::exception();
	}
	int	i_diff = diff_index(next_key, key);
	return ((*nextNode)[std::string(key.c_str() + i_diff)]);
}

template <typename T>
Trie<T>		*Trie<T>::find(std::string key) {
	Trie<T>	*nextNode = this->_nodes[static_cast<unsigned char>(key[0])];
	if (!nextNode)
		return (NULL);
	std::string	next_key = nextNode->getKey();
	if (next_key.length() > key.length())
		return (NULL);
	if (next_key == key)
	{
		if (nextNode->getLeaf())
			return (nextNode);
		return (NULL);
	}
	int	i_diff = diff_index(next_key, key);
	return (nextNode->find(std::string(key.c_str() + i_diff)));
}

template <typename T>
bool		Trie<T>::isIn(std::string key) {
	return (this->find(key) != NULL);
}

template <typename T>
void	create_graph_root(Trie<T> *root, std::ofstream &f)
{
	int i = 0;
	f << "\t\"" << root << "\" [label=\"" << root->getKey() << "\n" << root->getLeaf() << "\"]" << std::endl;
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
void	Trie<T>::createGraph(void)
{
	std::ofstream f("t.dot");

	f << "digraph viz {" << std::endl;
	create_graph_root(this, f);
	f << "}" << std::endl;
	f.close();
}

template <typename T>
void	Trie<T>::createGraph(const char *filename)
{
	std::ofstream f(filename);

	f << "digraph viz {" << std::endl;
	create_graph_root(this, f);
	f << "}" << std::endl;
	f.close();
}
