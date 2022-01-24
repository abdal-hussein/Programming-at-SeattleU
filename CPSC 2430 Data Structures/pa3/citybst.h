// Justin Thoreson
// citybst.h
// 05/18/20

#ifndef CITYBST_H
#define CITYBST_H
#include <string>

using namespace std;

class CityBST
{
  private:
    struct TreeNode
    {
      string key;
      string country;
      int population;
      TreeNode* left;
      TreeNode* right;
    };

    TreeNode* root;
    void insert(TreeNode*& node, string name, string ctry, int pop);
    bool remove(TreeNode*& node, string cityName);
    int getHeight(TreeNode* node);
    void print(TreeNode* node);
    void printCity(TreeNode* node, string city);
    void copy(TreeNode*& node, const TreeNode* origNode);
    void makeEmpty(TreeNode*& node);
     
  public:
    CityBST();
    CityBST(const CityBST& orig);
    const CityBST& operator=(const CityBST& rhs);
    ~CityBST();
    void insert(string name, string ctry, int pop);
    bool remove(string cityName);
    TreeNode* findMax(TreeNode* node);
    TreeNode* findMin(TreeNode* node);
    int getHeight();
    void print();
    void printCity(string city);
    TreeNode* highestPop(TreeNode* node);
    string biggestCity();
};

#endif
