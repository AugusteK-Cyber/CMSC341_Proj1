//UMBC - CSEE - CMSC 341 - Fall 2021 - Proj2
#include "swarm.h"
// Constructor, performs the required initializations.
Swarm::Swarm() {
    m_root = nullptr;
}

// Destructor, performs the required cleanup including memory deallocations.
Swarm::~Swarm() {
    clear();
}

// This function inserts a Robot object into the tree in the proper position. The Robot::m_id 
// should be used as the key to traverse the Swarm tree and abide by BST traversal rules. 
// The comparison operators (>, <, ==, !=) work with the int type in C++. A Robot id is a 
// unique number, i.e. we do not allow duplicate id in the tree.
void Swarm::insert(const Robot& robot) {
    m_root = insertRobot(robot, m_root);
}

// Insert robot using recursion function
Robot* Swarm::insertRobot(const Robot& robot, Robot* &aBot)
{
    if (aBot == nullptr) {
        Robot* anotherBot = new Robot(robot.getID(), robot.m_type, robot.m_state);
        return anotherBot;
    }
    else if (aBot->m_id > robot.getID() && !(robot.getID() < MINID)) {
        aBot->m_left = insertRobot(robot, aBot->m_left);
        updateHeight(aBot);
        return rebalance(aBot);
    }
    else if (aBot->m_id < robot.getID() && !(robot.getID() > MAXID)) {
        aBot->m_right = insertRobot(robot, aBot->m_right);
        updateHeight(m_root);
        return rebalance(aBot);
    }
    else {
        //cout << "\nDUPLICATES ARE NOT ALLOWED!" << endl;
        return aBot;
    }
}

// The clear function deallocates all memory in the tree and makes it an empty tree.
void Swarm::clear() {
    clearFromNode(m_root);
}

// Clear from a specific node in the tree
void Swarm::clearFromNode(Robot* &aBot)
{
    if (aBot == nullptr) return;
    else {
        clearFromNode(aBot->m_left);
        clearFromNode(aBot->m_right);
        delete aBot;
        aBot = nullptr;
    }
}

// The remove function traverses the tree to find a node with the id and removes it from the tree.
// (Note: After a removal, we should also update the height of each node on the path traversed down 
// the tree as well as check for an imbalance at each node in this path.)
void Swarm::remove(int id) {
    Robot* aBot = m_root;
    deleteRobot(aBot, id);
}

// Delete a robot using recursion  
Robot* Swarm::deleteRobot(Robot* aBot, int id)
{
    if (aBot == nullptr) {
        return aBot;
    }
    else if (id < aBot->getID()) {
        aBot->m_left = deleteRobot(aBot->m_left, id);
    }
    else if (id > aBot->getID()) {
        aBot->m_right = deleteRobot(aBot->m_right, id);
    }
    else {
        // Case 1: no child
        if (aBot->getLeft() == nullptr && aBot->getRight() == nullptr) {
            delete aBot;
            aBot = nullptr;
        }

        // Case 2: one child
        else if (aBot->getLeft() == nullptr) {
            Robot* temp = aBot;
            aBot = aBot->getRight();
            delete temp;
        }
        else if (aBot->getRight() == nullptr) {
            Robot* temp = aBot;
            aBot = aBot->getLeft();
            delete temp;
        }

        // Case 3: two children
        else {
            Robot* temp = findMin(aBot->m_right);
            aBot->m_id = temp->m_id;
            aBot->m_right = deleteRobot(aBot->m_right, temp->m_id);
        }
    }
    updateHeight(aBot);
    aBot = rebalance(aBot);
    return aBot;
}

// This function updates the height of the node passed in. The height of a leaf node is 0. The height
// of all internal nodes can be calculated based on the heights of their immediate children.
void Swarm::updateHeight(Robot* aBot) {
    int heightLeft = 0; // Height of the left robot
    int heightRight = 0; // Height of the right robot

    // Case where aBot is null
    if (aBot == nullptr) {
        return;
    }
    updateHeight(aBot->m_left);
    updateHeight(aBot->m_right);

    // Case where aBot is not null
    if (aBot->m_left == nullptr) {
        heightLeft = -1; // -1 corresponds to nullptr
    }
    else if (aBot->m_left != nullptr) {
        heightLeft = aBot->m_left->m_height;
    }
    if (aBot->m_right == nullptr) {
        heightRight = -1; // -1 corresponds to nullptr
    }
    else if (aBot->m_right != nullptr) {
        heightRight = aBot->m_right->m_height;
    }

    // Update the height of the robot
    if (heightLeft < heightRight) {
        aBot->m_height = heightRight + 1;
    }
    else if (heightLeft > heightRight) {
        aBot->m_height = heightLeft + 1;
    }
    else if (heightLeft == heightRight) {
        aBot->m_height = heightLeft + 1;
    }
    else {
        return;
    } 
}

// This function checks if there is an imbalance at the node passed in. For an imbalance to occur, 
// the heights of the children node must differ by more than 1.
// For balanced trees, height must be in the range {-1, 0, 1} = |height <= 1|
// If |height <= 1| is not true, then the tree is not balanced
int Swarm::checkImbalance(Robot* aBot) {
    int heightLeft = -1; // Height of the left subtree = -1 meaning nullptr
    int heightRight = -1; // Height of the right subtree = -1 meaning nullptr

    // If a robot is null, no height to determine, so return -1 
    if (aBot == nullptr)
        return -1;
    else {
        if (aBot->m_left != nullptr)
            heightLeft = aBot->m_left->m_height; // Immediate left robot node
        if (aBot->m_right != nullptr)
            heightRight = aBot->m_right->m_height; // Immediate right robot node
        return (heightLeft - heightRight); // Return the difference
    }
}

// This function begins and manages the rebalancing process. It is recommended to write additional 
// helper functions to implement left and right rotations. You can use rebalance() function to
// determine which combination of rotations is necessary.
Robot* Swarm::rebalance(Robot* aBot) {
    Robot* anotherBot = nullptr;
    // Case of left imbalance 
    if ((checkImbalance(aBot) > 1) && (checkImbalance(aBot->m_left) >= 0)) {
        anotherBot = singleRightRotation(aBot);
        updateHeight(m_root);
        rebalance(m_root);
        return anotherBot;
    }
    // Case of right imbalance 
    else if ((checkImbalance(aBot) < -1) && (checkImbalance(aBot->m_right) <= 0)) {
        anotherBot = singleLeftRotation(aBot);
        updateHeight(m_root);
        rebalance(m_root);
        return anotherBot;
    }
    // Case of right - left imbalance
    else if ((checkImbalance(aBot) > 1) && (checkImbalance(aBot->m_left) <= 0)) {
        aBot->m_left = singleLeftRotation(aBot->m_left); // Rebalance to the left
        anotherBot = singleRightRotation(aBot);
        updateHeight(m_root);
        rebalance(m_root);
        return anotherBot;
    }
    // Case of left - right imbalance
    else if ((checkImbalance(aBot) < -1) && (checkImbalance(aBot->m_left) >= 0)) {
        aBot->m_right = singleRightRotation(aBot->m_right); // Rebalance to the right
        anotherBot = singleLeftRotation(aBot);
        updateHeight(m_root);
        rebalance(m_root);
        return anotherBot;
    }
    return aBot;
}

// Find node that contains the leaf on the left of the BST
Robot* Swarm::findMin(Robot* aBot)
{
    if (aBot == nullptr)
        return nullptr;
    else if (aBot->m_left == nullptr)
        return aBot;
    else
        return findMin(aBot->m_left);
}

// Find node that contains the leaf on the right of the BST
Robot* Swarm::findMax(Robot* aBot)
{
    if (aBot == nullptr)
        return nullptr;
    else if (aBot->m_right == nullptr)
        return aBot;
    else
        return findMax(aBot->m_right);
}

// Single right rotation
Robot* Swarm::singleRightRotation(Robot* aBot)
{
    Robot* temp = aBot->m_left;
    aBot->m_left = temp->m_right;
    temp->m_right = aBot;
    updateHeight(aBot);
    updateHeight(temp);
    return temp;
}

// Single left rotation
Robot* Swarm::singleLeftRotation(Robot* aBot)
{
    Robot* temp = aBot->m_right;
    aBot->m_right = temp->m_left;
    temp->m_left = aBot;
    updateHeight(aBot);
    updateHeight(temp);
    return temp;
}

// This function prints a list of all robots in the tree to the standard output in the ascending 
// order of IDs. The information for every Robot object will be printed in a new line. For the 
// format of output please refer to the sample output file, i.e. driver.txt.
void Swarm::listRobots() const {
    Robot* aBot = traverseTree(m_root);
}

// Traverse the whole tree and display information
Robot* Swarm::traverseTree(Robot* aBot) const
{
    if (aBot != nullptr) {
        traverseTree(aBot->m_left);
        cout << aBot->getID() << ":" << aBot->getStateStr() << ":" << aBot->getTypeStr() << endl;
        traverseTree(aBot->m_right);
    }
    return nullptr;
}

// This function finds the node with id in the tree and sets its Robot::m_state member variable 
// to state. If the operation is successful, the function returns true otherwise it returns false. 
// For example, when the robot with id does not exist in the tree the function returns false.
bool Swarm::setState(int id, STATE state) {
    Robot* aBot = findThisBot(m_root, id);
    bool status = findBot(id);
    if (aBot == nullptr) {
        return false;
    }
    else if (status) {
        aBot->setState(state);
        return true;
    }
    else {
        return false;
    }
    return false;
}

// This function traverses the tree, finds all robots with DEAD state and removes them from the 
// tree. The final tree must be a balanced AVL tree.
void Swarm::removeDead() {
    Robot* aBot = removeDeadRobot(m_root);
}

// Remove dead robots using recursion
Robot* Swarm::removeDeadRobot(Robot* aBot)
{
   if (aBot != nullptr) {
        removeDeadRobot(aBot->m_left);
        cout << aBot->getID() << ":" << aBot->getStateStr() << ":" << aBot->getTypeStr() << endl;
        removeDeadRobot(aBot->m_right);
        if (aBot->getState() == DEAD) {
            remove(aBot->m_id);
        }
   }
   return nullptr;
}

// This function returns true if it finds the node with id in the tree, otherwise it returns false.
bool Swarm::findBot(int id) const {
    Robot* aBot = m_root; // Start search from m_root
    if (aBot == nullptr) {
        return false;
    }
    while (aBot != nullptr) {
        if (aBot->m_id == id) {
            return true;
        }
        else if (aBot->m_id < id) {
            aBot = aBot->m_right;
        }
        else if (aBot->m_id > id) {
            aBot = aBot->m_left;
        }
    }
    return false; // Return false if id was not found
}

// Return the robot corresponding to the id we are looking for
Robot* Swarm::findThisBot(Robot* aBot, int id)
{
    aBot = m_root; // Start search from m_root
    if (aBot == nullptr) {
        return nullptr;
    }
    while (aBot != nullptr) {
        if (aBot->m_id == id) {
            return aBot;
        }
        else if (aBot->m_id < id) {
            aBot = aBot->m_right;
        }
        else if (aBot->m_id > id) {
            aBot = aBot->m_left;
        }
    }
    return nullptr;
}

// Display tree
void Swarm::dumpTree() const {
    dump(m_root);
}

// Display tree
void Swarm::dump(Robot* aBot) const {
    if (aBot != nullptr) {
        cout << "(";
        dump(aBot->m_left);//first visit the left child
        cout << aBot->m_id << ":" << aBot->m_height;//second visit the node itself
        dump(aBot->m_right);//third visit the right child
        cout << ")";
    }
}

// See what is currently in the tree for future testing
bool Swarm::treeStatus(Robot* aBot)
{
    if (aBot == nullptr) {
        return false;
    }
    if (aBot != nullptr) {
        cout << "(";
        dump(aBot->m_left);//first visit the left child
        cout << aBot->m_id << ":" << aBot->m_height;//second visit the node itself
        dump(aBot->m_right);//third visit the right child
        cout << ")";
    }
    return true;
}

// Check if the BST property is respected
bool Swarm::bstProperty(Robot* aBot, int minKey, int maxKey)
{
    if (aBot == nullptr) {
        return true;
    }
    if (aBot->m_id < minKey || aBot->m_id > maxKey) {
        return false;
    }
    return bstProperty(aBot->m_left, minKey, aBot->m_id) &&
        bstProperty(aBot->m_right, aBot->m_id, maxKey);;
}
