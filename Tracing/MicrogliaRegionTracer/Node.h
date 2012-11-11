#ifndef NODE_H
#define NODE_H

#include "itkIntTypes.h"
#include <vector>

class Node
{
private:
	Node *parent;
	itk::uint64_t id;

public:
	double x;
	double y;
	double z;

	std::vector< Node* > children;

public:
	//Default constructor
	explicit Node(double x, double y, double z, itk::uint64_t id);
	
	//Copy constructor
	//Note: 
	//parent is set to old_node parent, the tree copy constructor must take care to regenerate the links to any new parents
	//children is set to the old_node vector of children, the tree copy constructor must take care to regenerate the links to the children as well
	Node(const Node& old_node);
	
    //Destructor
    ~Node();
    
	//Adds the child
	//Note: This does not make the child update its reference to the parent
	void AddChild(Node * const child);
	
	//Removes the child from this node, also removing the child's link to the parent
	//Returns true if the child was successfully removed, else returns false if the child to be removed was not found in the list of children
	void RemoveChild(Node* child_to_be_removed);

	void SetParent(Node * const parent);
	
	std::vector< Node* >& GetChildren();

	itk::uint64_t getID();
	
	Node* GetParent();
};

#endif