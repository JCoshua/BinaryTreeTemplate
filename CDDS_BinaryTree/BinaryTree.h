#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#pragma once
template<typename T>
class TreeNode;

template<typename T>
class BinaryTree
{
public:

	BinaryTree();
	~BinaryTree() {}

	/// <summary>
	/// Returns whether or not there are any nodes in the list
	/// </summary>
	bool isEmpty() const;
	/// <summary>
	/// Creates a new node that stores the given value and places it into the tree
	/// </summary>
	/// <param name="value">The new value to add to the tree</param>
	void insert(T value);
	/// <summary>
	/// Finds the node with the given value and removes it from the tree
	/// </summary>
	/// <param name="value">The value of the node to search for in the tree</param>
	void remove(T value);
	/// <summary>
	/// Finds and returns a node with the given value in the tree
	/// </summary>
	/// <param name="value">The value of the node to search for</param>
	TreeNode<T>* find(T value);

	void draw(TreeNode<T>* selected = nullptr);

private:
	/// <summary>
	/// Finds the node that matches the value in the list
	/// </summary>
	/// <param name="searchValue">The value of the node to search for</param>
	/// <param name="nodeFound">A pointer that will store the address of the node that was found</param>
	/// <param name="nodeParent">A pointer that will store the address of the parent of the node that was found</param>
	/// <returns>Whether or not a node matching the value could be found</returns>
	bool findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent);

	void draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected = nullptr);

	TreeNode<T>* m_root = nullptr;
};
#endif

template<typename T>
inline BinaryTree<T>::BinaryTree()
{
	m_root = nullptr;
}

template<typename T>
inline bool BinaryTree<T>::isEmpty() const
{
	return m_root == nullptr;
}

template<typename T>
inline void BinaryTree<T>::insert(T value)
{
	//Return if the value is null or is already exists
	if (value == NULL || find(value) != nullptr)
		return;

	//Creates pointer for the current node and its parent
	TreeNode<T>* currentNode = m_root;
	TreeNode<T>* parentNode;

	//While the current node exists
	while (currentNode)
	{
		//Makes the parent node become the current node
		parentNode = currentNode;

		//If the current node's value is less than the inserted value, move the current node to the right
		if (currentNode->getData() < value)
			currentNode = currentNode->getRight();

		//If the current node's value is greater than the inserted value, move the current node to the left
		else if (currentNode->getData() > value)
			currentNode = currentNode->getLeft();
	}

	//Make the current node become a node with the value to be inserted
	currentNode = new TreeNode<T>(value);

	///If the parent node exist, make the inserted node a leaf of the node
	if (parentNode)
	{
		if (parentNode->getData() > currentNode->getData())
			parentNode->setLeft(currentNode);
		else
			parentNode->setRight(currentNode);
	}
	else
		m_root = currentNode;
}

template<typename T>
inline void BinaryTree<T>::remove(T value)
{
	//Return if the value is null or not in the tree
	if (value == NULL || !find(value))
		return;

	TreeNode<T>* nodeToRemove;
	TreeNode<T>* parentNode = nullptr;

	//Sets the pointers to be the node to remove and its parent
	findNode(value, nodeToRemove, parentNode);

	//If the node has two leaves
	if (nodeToRemove->hasLeft() && nodeToRemove->hasRight())
	{
		//Create a pointer to nodes to replace the node to remove
		TreeNode<T>* replacementNode = nodeToRemove->getRight();
		TreeNode<T>* replacementParent = nodeToRemove;

		while (replacementNode->hasLeft())
		{
			//Makes the parent of the replacement node equal to its leaf, then moves its leaf to the left
			replacementParent = replacementNode;
			replacementNode = replacementNode->getLeft();
		}

		//Change the removed node with the replacement node
		replacementParent->setLeft(replacementNode->getRight());
		replacementNode->setLeft(nodeToRemove->getLeft());
		if (replacementParent != nodeToRemove)
			replacementNode->setRight(nodeToRemove->getRight());
		

		//If the removed node had a parent
		if (parentNode)
		{
			//Make the parent's leaf become the replacement node
			if (parentNode->getLeft() == nodeToRemove)
				parentNode->setLeft(replacementNode);
			else
				parentNode->setRight(replacementNode);
		}
		else
			m_root = replacementNode;
	}

	//If it only has one leaf
	else if (nodeToRemove->hasLeft() || nodeToRemove->hasRight())
	{
		//If the current node has no parent node
		if (!parentNode)
		{
			//Sets the leaf to be the root node
			if (nodeToRemove->hasLeft())
				m_root = nodeToRemove->getLeft();
			else
				m_root = nodeToRemove->getRight();
		}

		//If the parent's left leaf is the node to remove
		else if (parentNode->getLeft() == nodeToRemove)
		{
			//Set the parent's left leaf to be the leaf of the removed node
			if (nodeToRemove->hasLeft())
				parentNode->setLeft(nodeToRemove->getLeft());
			else
				parentNode->setLeft(nodeToRemove->getRight());
		}

		//If the parent's right leaf is the node to remove
		else if (parentNode->getRight() == nodeToRemove)
		{
			//Set the parent's right leaf to be the leaf of the removed node
			if (nodeToRemove->hasLeft())
				parentNode->setRight(nodeToRemove->getLeft());
			else
				parentNode->setRight(nodeToRemove->getRight());
		}
	}

	//If the node has no leaves but isn't the root node
	else if (parentNode != nullptr)
	{
		//If the parent's left leaf is the node to remove
		if (parentNode->getLeft() == nodeToRemove)
				parentNode->setLeft(nullptr);

		//If the parent's right leaf is the node to remove
		else if (parentNode->getRight() == nodeToRemove)
				parentNode->setRight(nullptr);
	}
	else
		m_root = nullptr;

	//Deletes the current node
	nodeToRemove = nullptr;
}

template<typename T>
inline TreeNode<T>* BinaryTree<T>::find(T value)
{
	//Return nullptr if the value is null
	if (!value)
		return nullptr;

	//Create a pointer for the node to return
	TreeNode<T>* currentNode = m_root;

	//While the current node exists
		while (currentNode)
		{
			//If the current node's value is less than the value to find
			if (currentNode->getData() < value)
				//Make the current value the next node to the right
				currentNode = currentNode->getRight();
			//If the current node's value is greater than the value to find
			else if (currentNode->getData() > value)
				//Make the current value the next node to the left
				currentNode = currentNode->getLeft();
			//If the current node's value is the value to find
			else if (currentNode->getData() == value)
				break;
		}

	//return the found node
	return currentNode;
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* selected)
{
	draw(m_root, 400, 40, 400, selected);
}

template<typename T>
inline bool BinaryTree<T>::findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent)
{
	//Return nullptr if the value is null
	if (!searchValue && !find(searchValue))
		return false;

	nodeFound = m_root;
	//While the current node is not the searched node
	while (nodeFound->getData() != searchValue)
	{
		//Makes the parent node become the current node
		nodeParent = nodeFound;

		//If the current node's value is less than the inserted value, move the node to the right
		if (nodeFound->getData() < searchValue)
			nodeFound = nodeFound->getRight();

		//If the current node's value is greater than the inserted value, move the node to the left
		else if (nodeFound->getData() > searchValue)
			nodeFound = nodeFound->getLeft();
	}
	return true;
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected)
{
	//sets the needed space in between      
	horizontalSpacing /= 2;   

	//check if the current node in null     
	if (currentNode)     
	{         
		//draws the left child if this node has one         
		if (currentNode->hasLeft())         
		{            
			//Darws a line betwen the left child and the current node             
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);             
			//draws the left child             
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);         
		}          

		//draws the right child if this node has one         
		if (currentNode->hasRight())         
		{             
			//draws a line between this child and the curent code             
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);             
			//draws the right child             
			draw(currentNode->getRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);         
		}         
		//draws the current node         
		currentNode->draw(x, y, (selected == currentNode));      
	}
}
