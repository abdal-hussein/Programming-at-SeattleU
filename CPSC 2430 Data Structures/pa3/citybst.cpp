// Justin Thoreson
// citybst.cpp
// 05/18/20

#include "citybst.h"
#include <iostream>
#include <string>
#include <algorithm>

CityBST::CityBST(): root(nullptr) {}

CityBST::CityBST(const CityBST& orig) { copy(root, orig.root); }

const CityBST& CityBST::operator=(const CityBST& rhs)
{
  if (this != &rhs)
  {
    makeEmpty(root);
    copy(root, rhs.root);
  }

  return *this;
}

CityBST::~CityBST() { makeEmpty(root); }

void CityBST::insert(string name, string ctry, int pop)
{ insert(root, name, ctry, pop); }

void CityBST::insert(TreeNode*& node, string name, string ctry, int pop)
{  
  if (!node)
  {
    node = new TreeNode;  
    node->key = name;
    node->country = ctry;
    node->population = pop;
    node->left = nullptr;
    node->right = nullptr;
  }
  else if (node->key > name)
    insert(node->left, name, ctry, pop);
  else
    insert(node->right, name, ctry, pop);
}

bool CityBST::remove(string cityName) { return remove(root, cityName); }

bool CityBST::remove(TreeNode*& node, string cityName)
{
  if (!node)
    return false;

  if (cityName < node->key)
    return remove(node->left, cityName);
  else if (cityName > node->key)
    return remove(node->right, cityName);
  else if (node->left && node->right)
  {
    node->key = findMin(node->right)->key;
    return remove(node->right, node->key);
  }
  else
  {
    TreeNode* oldNode = node;
    node = (node->left) ? node->left : node->right;
    delete oldNode;
    return true;
  }
}

CityBST::TreeNode* CityBST::findMin(TreeNode* node)
{
  if (!node)
    return nullptr;
  if (!node->left)
    return node;
  return findMin(node->left);
}

// PURPOSE: Finds and returns the height of the tree.
// PRECONDITION: A tree exists and its root node is provided.
// POSTCONDITION: The height of the tree found and returned.
int CityBST::getHeight() { return getHeight(root); }

int CityBST::getHeight(TreeNode* node)
{
  if(!node)
    return 0;
  else
  {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return max(leftHeight, rightHeight) + 1;
  }
} 

void CityBST::print() { print(root); }

void CityBST::print(TreeNode* node)
{
  if (!root)
  {
    cout << "The tree is empty." << endl;
    return;
  }

  if (node)  
  {
    print(node->left);
    cout << node->key << endl;
    print(node->right);
  }
}

// PURPOSE: Prints the details of a single city.
// PRECONDITION: The user provides a city name.
// POSTCONDITION: The name, country, and population of the cirty are printed.
void CityBST::printCity(string city) { printCity(root, city); }
    
void CityBST::printCity(TreeNode* node, string city)
{
  if (!node)
  {
    cout << "The city of " << city << " is not in the tree." << endl;    
    return;
  }
  else if (node->key == city)
  {
    // To print the population with commas  
    string numWithCommas = to_string(node->population);
    int insertPosition = numWithCommas.length() - 3;
    while (insertPosition > 0)
    {
      numWithCommas.insert(insertPosition, ",");
      insertPosition-=3;
    }
    
    cout << "City: " << node->key << endl
         << "Country: " << node->country << endl
         << "Population: " << numWithCommas << endl;
  }
  else if (node->key > city)
    printCity(node->left, city);
  else
    printCity(node->right, city);
}

// PURPOSE: Searches for the city with the largest population.
// PRECONDITION: A tree exists and its root node is provided.
// POSTCONDITION: The city with the largest population if found and returned.
CityBST::TreeNode* CityBST::highestPop(TreeNode* node)
{
  if (!node)
    return nullptr;
  else if (!node->left && !node->right)
    return node;
  else if (!node->left)
  {
    return (node->population > highestPop(node->right)->population)
      ? node : node->right;
  }
  else if (!node->right)
  {
    return (node->population > highestPop(node->left)->population)
      ? node : node->left;
  }
  else
  {
    int leftPop = highestPop(node->left)->population;
    int rightPop = highestPop(node->right)->population;

    if (node->population > leftPop && node->population > rightPop)
      return node;
    else if (leftPop > node->population && leftPop > rightPop)
      return node->left;
    else
      return node->right;
  }
}

// PURPOSE: Returns the name of the most populated city.
// PRECONDITION: The city with the highest population is found via the helper
//               function highestPop().
// POSTCONDITION: The name of the city is returned.
string CityBST::biggestCity()
{
  TreeNode* city = highestPop(root);
  return (!city) ? "" : city->key;
}

void CityBST::copy(TreeNode*& node, const TreeNode* origNode)
{
  if (!origNode)
    node = nullptr;
  else
  {
    node = new TreeNode;
    node->key = origNode->key;
    node->country = origNode->country;
    node->population = origNode->population;
    copy(node->left, origNode->left);
    copy(node->right, origNode->right);
  }
}

void CityBST::makeEmpty(TreeNode*& node)
{
  if (node)
  {
    makeEmpty(node->left);
    makeEmpty(node->right);
    delete node;
  }
}
