#include <utility>
#include "avlbst.h"

int main(){
	AVLTree<int, int> testTree;

	testTree.insert(std::make_pair(5, 8));
	testTree.insert(std::make_pair(3, 159));
	testTree.insert(std::make_pair(1, 9));
	testTree.insert(std::make_pair(3, 0x5a));
	testTree.insert(std::make_pair(15, 0xb));
	testTree.insert(std::make_pair(1, 4));
	testTree.insert(std::make_pair(3, 159));
}
	
