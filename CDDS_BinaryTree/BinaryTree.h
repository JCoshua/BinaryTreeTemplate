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
	TreeNode<T>* parentNode = currentNode;

	//While the current node exists
	while (currentNode)
	{
		//Makes the parent node become the current node
		parentNode = currentNode;

		//If the current node's value is less than the inserted value
		if (currentNode->getData() < value)
		{
			//Make the current value the next node to the right
			currentNode = currentNode->getRight();
		}

		//If the current node's value is greater than the inserted value
		else if (currentNode->getData() > value)
		{
			//Make the current value the next node to the left
			currentNode = currentNode->getLeft();
		}
	}
	//Make the current node become a node with the value to be inserted
	currentNode = new TreeNode<T>(value);

	///If the root node exists
	if (m_root)
	{
		//If the parents node's data is greater than the inserted node's
		if (parentNode->getData() > currentNode->getData())
			//set the parent's node's left to be the inserted node
			parentNode->setLeft(currentNode);
		else
			//Set the parent's node's right to be the inserted node
			parentNode->setRight(currentNode);
	}
	else
		m_root = currentNode;
}

template<typename T>
inline void BinaryTree<T>::remove(T value)
{
	//IF the value is null
	if (value == NULL || !find(value))
		return;

	//Create a pointer to the node to remove and its parent
	TreeNode<T>* currentNode;
	TreeNode<T>* parentNode = nullptr;

	findNode(value, currentNode, parentNode);

	//If the node has two leaves
	if (currentNode->hasLeft() && currentNode->hasRight())
	{
		//Create a pointer to nodes to replace the node to remove
		TreeNode<T>* replacementNode = currentNode->getRight();
		TreeNode<T>* replacementParent = currentNode;

		//Make the replacement node be the leftmost node to the right of the current node
		while (replacementNode->hasLeft())
		{
			//Makes the parent node become the current node
			replacementParent = replacementNode;

			//Makes the replacement node become the next value to the left
			replacementNode = replacementNode->getLeft();
		}

		if (replacementParent != currentNode)
		{
			if (replacementNode->hasRight())
				replacementParent->setLeft(replacementNode->getRight());
			else
				replacementParent->setLeft(nullptr);

			replacementNode->setRight(currentNode->getRight());
		}
		replacementNode->setLeft(currentNode->getLeft());

		//If the current node has no parent node
		if (!parentNode)
		{
			//Make the current node the root node
			m_root = replacementNode;
		}
		else
			if (parentNode->getLeft() == currentNode)
				parentNode->setLeft(replacementNode);
			else
				parentNode->setRight(replacementNode);
	}

	//If it only has one leaf
	else if (currentNode->hasLeft() || currentNode->hasRight())
	{
		//If the current node has no parent node
		if (!parentNode)
		{
			//Sets the leaf to by the root node
			if (currentNode->hasLeft())
				m_root = currentNode->getLeft();
			else
				m_root = currentNode->getRight();
		}

		//If the parent's left leaf is the node to remove
		else if (parentNode->getLeft() == currentNode)
		{
			//Set the parent's left leaf to the leaf of the removed node
			if (currentNode->hasLeft())
				parentNode->setLeft(currentNode->getLeft());
			else
				parentNode->setLeft(currentNode->getRight());
		}

		//If the parent's right leaf is the node to remove
		else if (parentNode->getRight() == currentNode)
		{
			//Set the parent's right leaf to the leaf of the removed node
			if (currentNode->hasLeft())
				parentNode->setRight(currentNode->getLeft());
			else
				parentNode->setRight(currentNode->getRight());
		}
	}

	//If the node has no leaves but isn't the root node
	else if (parentNode != nullptr)
	{
		//If the parent's left leaf is the node to remove
		if (parentNode->getLeft() == currentNode)
			//Set the parent's left leaf to the leaf of the removed node
			if (currentNode->getLeft())
				parentNode->setLeft(nullptr);
			else
				parentNode->setLeft(nullptr);
		//If the parent's right leaf is the node to remove
		else if (parentNode->getRight() == currentNode)
			//Set the parent's right leaf to the leaf of the removed node
			if (currentNode->getLeft())
				parentNode->setRight(nullptr);
			else
				parentNode->setRight(nullptr);
	}
	else
		m_root = nullptr;
	//Deletes the current node
	currentNode = nullptr;
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

		//If the current node's value is less than the inserted value
		if (nodeFound->getData() < searchValue)
			//Make the current value the next node to the right
			nodeFound = nodeFound->getRight();
		//If the current node's value is greater than the inserted value
		else if (nodeFound->getData() > searchValue)
			//Make the current value the next node to the left
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
