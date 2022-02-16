/**
 * File:    mytest.cpp
 * Author:  Auguste Kiendrebeogo
 * Section: 4
 * Created: 10/10/21
 * Date due: 10/26/21
 * E-mail:  akiendr1@umbc.edu
 *
 * UMBC - CSEE - CMSC 341 - Fall 2021 - Proj2
 * 
 * Description:
 * File with the different tests in it.
 */

#include "swarm.h"
#include <random>

enum RANDOM { UNIFORM, NORMAL };
class Random {
public:
    Random(int min, int max, RANDOM type = UNIFORM) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL) {
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 and standard deviation of 20 
            m_normdist = std::normal_distribution<>(50, 20);
        }
        else {
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min, max);
        }
    }

    int getRandNum() {
        int result = 0;
        if (m_type == NORMAL) {
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while (result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else {
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//uniform distribution

};

class Tester {
    public:
        bool testInsertionFunction();
        bool testBalanceOfTree();
        bool testBSTProperty();
        bool testRemoveFunction();
        bool testBalanceAfterMultipleRemovals();
        bool testBSTAfterMultipleRemovals();
        bool testRemovedDeadFunction();
        bool testDuplicates();
        bool proveInsertionTimeComplexity();
        bool proveInsertionTimeComplexity2();
        bool proveDeletionTimeComplexity();
        bool testInsertionOutOfRangeMin();
        bool testInsertionOutOfRangeMax();
        bool testInsertionEmptyRobotObjects();
        bool testInsertionVeryLargeTree();
        bool testDeletionOutOfRangeMin();
        bool testDeletionOutOfRangeMax();
        bool testDeleteAllRobots();
        unsigned int Log2n(unsigned int n);
};

int main() {
    Tester tester;
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    {
        Swarm team;
        int teamSize = 10;
        int tempID = 0;
        int ID = 0;
        for (int i = 0; i < teamSize; i++) {
            ID = idGen.getRandNum();
            if (i == teamSize / 2) tempID = ID;//we store this ID for later use
            Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
            team.insert(robot);
        }
        cout << "\nDump after inserting " << teamSize << " nodes:\n\n";
        team.dumpTree();
        cout << "\n\nList of Robots after inserting " << teamSize << " nodes:\n";
        team.listRobots();
        cout << endl;

        team.remove(tempID);
        cout << "\nDump after removing the node with ID: " << tempID << "\n\n";
        team.dumpTree();
        cout << "\n\nList of Robots after removing the node with ID: " << tempID << "\n";
        team.listRobots();
        cout << endl;

        cout << "\n\nTesting the different functions\n\n";

    }

    {
        // Test the insertion function
        bool result = false;
        cout << "\n1) Testing the insertion function..." << endl;
        result = tester.testInsertionFunction();
        if (result == true) {
            cout << "\n\nINSERTION TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nINSERTION TEST FAILED!" << endl;
        }
    }
    
    {
        // Test whether the tree is balanced after a decent number of insertions. (Note: this requires visiting all nodes and checking the height values)
        bool result = false;
        cout << "\n2) Testing if the tree is balanced..." << endl;
        result = tester.testBalanceOfTree();
        if (result == true) {
            cout << "\n\nBALANCED TREE TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nBALANCED TREE TEST FAILED!" << endl;
        }
    }

    {
        // Test whether the BST property is preserved after all insertions. (Note: this requires visiting all nodes and comparing key values)
        bool result = false;
        cout << "\n3) Testing whether the BST property is preserved after all insertions..." << endl;
        result = tester.testBSTProperty();
        if (result == true) {
            cout << "\n\nBST PROPERTY TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nBST PROPERTY TEST FAILED!" << endl;
        }
    }
        
    {
        // Test the remove function.
        bool result = false;
        cout << "\n4) Testing the remove function..." << endl;
        result = tester.testRemoveFunction();
        if (result == true) {
            cout << "\n\nREMOVE FUNCTION TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nREMOVE FUNCTION TEST FAILED!" << endl;
        }
    }

    {
        // Test whether the tree is balanced after multiple removals.
        bool result = false;
        cout << "\n5) Testing if the tree is balanced after multiple removals..." << endl;
        result = tester.testBalanceAfterMultipleRemovals();
        if (result == true) {
            cout << "\n\nBALANCED TREE AFTER MULTIPLE REMOVALS TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nBALANCED TREE AFTER MULTIPLE REMOVALS TEST FAILED!" << endl;
        }
    }
       
    {
        // Test whether the BST property is preserved after multiple removals.
        bool result = false;
        cout << "\n6) Testing if the BST property is preserved after multiple removals..." << endl;
        result = tester.testBSTAfterMultipleRemovals();
        if (result == true) {
            cout << "\n\nBST PROPERTY PRESERVED AFTER MULTIPLE REMOVALS TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nBST PROPERTY PRESERVED TREE AFTER MULTIPLE REMOVALS TEST FAILED!" << endl;
        }
    }

    {
        // Test the removeDead() functionality.
        bool result = false;
        cout << "\n7) Testing if DEAD robots are removed..." << endl;
        result = tester.testRemovedDeadFunction();
        if (result == true) {
            cout << "\n\nDEAD ROBOTS REMOVED TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nDEAD ROBOTS REMOVED TEST FAILED!" << endl;
        }
    }
        
    {
        // Test whether the tree allows for storage of duplicates.
        bool result = false;
        cout << "\n8) Testing whether the tree allows for storage of duplicates..." << endl;
        result = tester.testDuplicates();
        if (result == true) {
            cout << "\n\nNO DUPLICATES TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nNO DUPLICATES TEST FAILED!" << endl;
        }
    }
    
    {
        // Prove that the insertion performs in O(log n).
        bool result = false;
        cout << "\n9) Prove that the insertion operation performs in O(log n). Measure time for inserting one robot after inserting 10,000 robots ..." << endl;
        result = tester.proveInsertionTimeComplexity();
        if (result == true) {
            cout << "\n\nINSERTION PERFORMS O(LOG N) TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nINSERTION PERFORMS O(LOG N) TEST FAILED!" << endl;
        }
    }

    {
        // Prove that the insertion performs in O(log n).
        bool result = false;
        cout << "\n10) Prove that the insertion operation performs in O(log n) for increasing insertions with problable duplicates extending the time ..." << endl;
        result = tester.proveInsertionTimeComplexity2();
        if (result == true) {
            cout << "\n\nINSERTION PERFORMS O(LOG N) TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nINSERTION PERFORMS O(LOG N) TEST FAILED!" << endl;
        }
    }
        
    {
        // Prove that the removal operation performs in O(log n).
        bool result = false;
        cout << "\n11) Prove that the deletion operation performs in O(log n)..." << endl;
        result = tester.proveDeletionTimeComplexity();
        if (result == true) {
            cout << "\n\nDELETION PERFORMS O(LOG N) TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nDELETION PERFORMS O(LOG N) TEST FAILED!" << endl;
        }
    }

    {
        // Test the insertion with a robot id less than MINID.
        bool result = false;
        cout << "\n12) Test insertion of robot with ID less than IDMIN..." << endl;
        result = tester.testInsertionOutOfRangeMin();
        if (result == true) {
            cout << "\n\nINSERTION OF ROBOT WITH ID LESS THAN IDMIN FAILED! TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nINSERTION OF ROBOT WITH ID LESS THAN IDMIN PASSED! TEST FAILED!" << endl;
        }
    }
    
    {
        // Test the insertion with a robot id greater than MAXID.
        bool result = false;
        cout << "\n13) Test insertion of robot with ID greater than IDMAX..." << endl;
        result = tester.testInsertionOutOfRangeMax();
        if (result == true) {
            cout << "\n\nINSERTION OF ROBOT WITH ID GREATER THAN IDMAX FAILED! TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nINSERTION OF ROBOT WITH ID GREATER THAN IDMAX PASSED! TEST FAILED!" << endl;
        }
    }

    {
        // Test the insertion with a robot id greater than MAXID.
        bool result = false;
        cout << "\n14) Test insertion of empty Robot objects ..." << endl;
        result = tester.testInsertionEmptyRobotObjects();
        if (result == true) {
            cout << "\n\nINSERTION OF EMPTY ROBOT OBJECTS FAILED! TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nINSERTION OF EMPTY ROBOT OBJECTS PASSED! TEST FAILED!" << endl;
        }
    }
    
    {
        // Test inserting very large number of robots and whether the tree is balanced after that.
        bool result = false;
        cout << "\n15) Testing the insertion of 12,000 robots and balance of the tree..." << endl;
        result = tester.testInsertionVeryLargeTree();
        if (result == true) {
            cout << "\n\nINSERTION AND BALANCED TREE TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nINSERTION AND BALANCED TREE TEST FAILED!" << endl;
        }
    }
    
    {
        // Testing the deletion of a robot with id less than MINID.
        bool result = false;
        cout << "\n16) Testing the deletion of a robot with id less than MINID..." << endl;
        result = tester.testDeletionOutOfRangeMin();
        if (result == true) {
            cout << "\n\nDELETION OF A ROBOT WITH ID LESS THAN MINID FAILED! TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nDELETION OF A ROBOT WITH ID LESS THAN MINID PASSED! TEST FAILED!" << endl;
        }
    }
    
    {
        // Testing the deletion of a robot with id greater than MAXID.
        bool result = false;
        cout << "\n17) Testing the deletion of a robot with id greater than MAXID..." << endl;
        result = tester.testDeletionOutOfRangeMax();
        if (result == true) {
            cout << "\n\nDELETION OF A ROBOT WITH ID LESS THAN MAXID FAILED! TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nDELETION OF A ROBOT WITH ID LESS THAN MAXID PASSED! TEST FAILED!" << endl;
        }
    }

    {
        // Test deleting all the robots.
        bool result = false;
        cout << "\n18) Testing deleting all the robots from the tree..." << endl;
        result = tester.testDeleteAllRobots();
        if (result == true) {
            cout << "\n\nDELETE ALL ROBOTS FROM THE TREE TEST PASSED!" << endl;
        }
        else {
            cout << "\n\nDELETE ALL ROBOTS FROM THE TREE TEST FAILED!" << endl;
        }
    }
    return 0;
}

// Test the insertion function
bool Tester::testInsertionFunction()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 15;
    int tempID = 0;
    int ID = 0;

    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        if (i == teamSize / 2) tempID = ID;//we store this ID for later use
        Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
        team.insert(robot);
    }
    cout << "Dump after inserting " << teamSize << " nodes:\n\n";
    team.dumpTree();
    if (team.treeStatus(team.m_root)) {
        return true;
    }
    return false;
}

// Test whether the tree is balanced after a decent number of insertions. (Note: this requires visiting all nodes and checking the height values)
bool Tester::testBalanceOfTree()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 1500;
    int tempID = 0;
    int ID = 0;

    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        if (i == teamSize / 2) tempID = ID;//we store this ID for later use
        Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
        team.insert(robot);
    }
    cout << "Dump after inserting " << teamSize << " nodes:\n\n";
    team.dumpTree();
    if (team.checkImbalance(team.m_root) >= -1 && team.checkImbalance(team.m_root) <= 1) {
        return true;
    }
    return false;
}

// Test whether the BST property is preserved after all insertions. (Note: this requires visiting all nodes and comparing key values)
bool Tester::testBSTProperty()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 15;
    int tempID = 0;
    int ID = 0;

    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        if (i == teamSize / 2) tempID = ID;//we store this ID for later use
        Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
        team.insert(robot);
    }
    cout << "Dump after inserting " << teamSize << " nodes:\n\n";
    team.dumpTree();
    if (team.bstProperty(team.m_root, MINID, MAXID)) {
        return true;
    }
    return false;
}

// Test the remove function.
bool Tester::testRemoveFunction()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 10;
    int tempID = 0, tempID1 = 0;
    int ID = 0;

    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        if (i == teamSize / 2) tempID = ID;//we store this ID for later use
        if (i == teamSize / 3) tempID1 = ID;
        Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
        team.insert(robot);
    }
    cout << "Dump after inserting " << teamSize << " nodes:\n\n";
    team.dumpTree();
    team.remove(tempID);
    team.remove(tempID1);
    cout << "\nDump after removing the nodes with ID: " << tempID << " and " << tempID1 << "\n\n";
    team.dumpTree();
    cout << "\n\nList of Robots after removing the nodes with ID: " << tempID << " and " << tempID1 << "\n";
    team.listRobots();
    if (team.findThisBot(team.m_root, tempID) == nullptr && team.findThisBot(team.m_root, tempID1) == nullptr) {
        return true;
    }
    return false;
}

// Test whether the tree is balanced after multiple removals.
bool Tester::testBalanceAfterMultipleRemovals()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 15;
    int tempID = 0, tempID1 = 0, tempID2 = 0, tempID3 = 0;
    int ID = 0;

    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        if (i == teamSize - 1) tempID = ID;//we store this ID for later use
        if (i == teamSize - 2) tempID1 = ID;
        if (i == teamSize - 3) tempID2 = ID;
        if (i == teamSize - 4) tempID3 = ID;
        Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
        team.insert(robot);
    }
    cout << "Dump after inserting " << teamSize << " nodes:\n\n";
    team.dumpTree();
    team.remove(tempID);
    team.remove(tempID1);
    team.remove(tempID2);
    team.remove(tempID3);
    cout << "\nDump after removing the nodes with ID: " << tempID << ", " << tempID1 << ", " << tempID2 << ", and " << tempID3 << "\n\n";
    team.dumpTree();
    cout << "\n\nList of Robots after removing the nodes with ID: " << tempID << ", " << tempID1 << ", " << tempID2 << ", and " << tempID3 << "\n";
    team.listRobots();
    if (team.checkImbalance(team.m_root) >= -1 && team.checkImbalance(team.m_root) <= 1) {
        return true;
    }
    return false;
}
// Test whether the BST property is preserved after multiple removals.
bool Tester::testBSTAfterMultipleRemovals()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 15;
    int tempID = 0, tempID1 = 0, tempID2 = 0, tempID3 = 0;
    int ID = 0;

    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        if (i == teamSize - 4) tempID = ID;//we store this ID for later use
        if (i == teamSize - 3) tempID1 = ID;
        if (i == teamSize - 2) tempID2 = ID;
        if (i == teamSize - 1) tempID3 = ID;
        Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
        team.insert(robot);
    }
    cout << "Dump after inserting " << teamSize << " nodes:\n\n";
    team.dumpTree();
    team.remove(tempID);
    team.remove(tempID1);
    team.remove(tempID2);
    team.remove(tempID3);
    cout << "\nDump after removing the nodes with ID: " << tempID << ", " << tempID1 << ", " << tempID2 << ", and " << tempID3 << "\n\n";
    team.dumpTree();
    cout << "\n\nList of Robots after removing the nodes with ID: " << tempID << ", " << tempID1 << ", " << tempID2 << ", and " << tempID3 << "\n";
    team.listRobots();
    if (team.bstProperty(team.m_root, MINID, MAXID)) {
        return true;
    }
    return false;
}

// Test the removeDead() functionality.
bool Tester::testRemovedDeadFunction()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 10;
    int tempID = 0, tempID1 = 0;
    int ID = 0;

    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        if (i == teamSize / 2) tempID = ID;//we store this ID for later use
        if (i == teamSize - 1) tempID1 = ID;
        Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
        team.insert(robot);
    }
    cout << "Dump after inserting " << teamSize << " nodes:\n\n";
    team.dumpTree();
    team.setState(tempID, DEAD);
    team.setState(tempID1, DEAD);
    cout << "\nDump after removing the DEAD nodes: " << tempID << " and " << tempID1 << "\n\n";
    team.removeDead();
    cout << "\n\nList of Robots after removing the DEAD nodes: " << tempID << " and " << tempID1 << "\n";
    team.listRobots();
    if (team.findThisBot(team.m_root, tempID) == nullptr && team.findThisBot(team.m_root, tempID1) == nullptr) {
        return true;
    }
    return false;
}

// Test whether the tree allows for storage of duplicates.
bool Tester::testDuplicates()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 15;
    int tempID = 0;
    int ID = 0;
    int count = 0;

    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        if (i == teamSize / 2) tempID = ID;//we store this ID for later use
        Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
        team.insert(robot);
    }
    cout << "Dump after inserting " << teamSize << " nodes:\n\n";
    team.dumpTree();
    Robot robot(tempID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
    team.insert(robot);
    if (team.findThisBot(team.m_root, tempID)) {
        count += 1;
    }
    if (count == 1) {
        return true;
    }
    return false;
}

// Prove that the insertion performs in O(log n).
bool Tester::proveInsertionTimeComplexity()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 10000;
    int tempID = 0;
    int ID = 0;
    int count = 0;
    double T = 0.0;//to store running times
    clock_t start, stop;//stores the clock ticks while running the program
   
    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        if (i == teamSize / 2) tempID = ID;//we store this ID for later use
        Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
        team.insert(robot);
    }
    start = clock();
    Robot robot(tempID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
    team.insert(robot);
    stop = clock();
    T = stop - start;//number of clock ticks the algorithm took
    cout << "Insertion of one robot on a " << teamSize << " robots tree took " << T << " clock ticks (" << T / CLOCKS_PER_SEC << " seconds)!" << endl;
    if ((T / CLOCKS_PER_SEC) < Log2n(teamSize)) {
        return true;
    }
    return false;
}

// Prove that the insertion performs in O(log n) for increasing insertions
bool Tester::proveInsertionTimeComplexity2()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 10;
    int tempID = 0;
    int ID = 0;
    int count = 0;

    const int a = 2;//scaling factor for input size, everytime it will double
    double T = 0.0;//to store running times
    int numTrials = 7;
    clock_t start, stop;//stores the clock ticks while running the program
    start = clock();
    for (int k = 0; k < numTrials - 1; k++) {
        for (int i = 0; i < teamSize; i++) {
            ID = idGen.getRandNum();
            if (i == teamSize / 2) tempID = ID;//we store this ID for later use
            Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
            team.insert(robot);
        }
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "Insertion of " << teamSize << " robots took " << T << " clock ticks (" << T / CLOCKS_PER_SEC << " seconds)!" << endl;
        teamSize = teamSize * a;
    }
    if ((T / CLOCKS_PER_SEC) < Log2n(teamSize)) {
        return true;
    }
    return false;
}

// Prove that the removal operation performs in O(log n).
bool Tester::proveDeletionTimeComplexity()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 10;
    int tempID = 0, tempID1 = 0;
    int ID = 0;

    const int a = 2;//scaling factor for input size, everytime it will double
    double T = 0.0;//to store running times
    int numTrials = 10;
    clock_t start, stop;//stores the clock ticks while running the program
    for (int k = 0; k < numTrials - 1; k++) {
        for (int i = 0; i < teamSize; i++) {
            ID = idGen.getRandNum();
            if (i == teamSize / 2) tempID = ID;//we store this ID for later use
            if (i == teamSize / 3) tempID = ID;//we store this ID for later use
            Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
            team.insert(robot);
        }
    }

    start = clock();
    for (int k = 0; k < numTrials - 1; k++) {
        for (int i = 0; i < teamSize; i++) {
            team.remove(tempID);
            team.remove(tempID1);
        }
        stop = clock();
        T = stop - start;//number of clock ticks the algorithm took
        cout << "Deletion of robots took " << T << " clock ticks (" << T / CLOCKS_PER_SEC << " seconds)!" << endl;
        teamSize = teamSize * a;
    }    
    if ((T / CLOCKS_PER_SEC) < Log2n(teamSize)) {
        return true;
    }
    return false;
}

// Log2(n) test function
unsigned int Tester::Log2n(unsigned int n)
{
    return (n > 1) ? 1 + Log2n(n / 2) : 0;
}

// Test insertion out of range MINID
bool Tester::testInsertionOutOfRangeMin()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 15;
    int tempID = 225;
    int ID = 0;

    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
        team.insert(robot);
    }
    cout << "Dump after inserting " << teamSize << " nodes:\n\n";
    team.dumpTree();
    Robot robot(tempID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
    team.insert(robot);
    if (team.findThisBot(team.m_root, tempID)) {
        return false;
    }
    return true;
}

// Test insertion out of range MAXID
bool Tester::testInsertionOutOfRangeMax()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 15;
    int tempID = 558855544;
    int ID = 0;

    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
        team.insert(robot);
    }
    cout << "Dump after inserting " << teamSize << " nodes:\n\n";
    team.dumpTree();
    Robot robot(tempID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
    team.insert(robot);
    if (team.findThisBot(team.m_root, tempID)) {
        return false;
    }
    return true;
}

// Test insertion empty Robot objects
bool Tester::testInsertionEmptyRobotObjects()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 15;
    int tempID = 0;
    int ID = 0;

    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        Robot robot;
        team.insert(robot);
    }
    cout << "Dump after inserting " << teamSize << " nodes:\n\n";
    team.dumpTree();
    if (team.m_root->m_id == 0){
        return true;
    }
    return false;
}

// Test insertion very large tree
bool Tester::testInsertionVeryLargeTree()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 12000;
    int tempID = 0;
    int ID = 0;

    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        if (i == teamSize / 2) tempID = ID;//we store this ID for later use
        Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
        team.insert(robot);
    }
    cout << "Dump after inserting " << teamSize << " nodes:\n\n";
    team.dumpTree();
    if (team.checkImbalance(team.m_root) >= -1 && team.checkImbalance(team.m_root) <= 1) {
        return true;
    }
    return false;
}

// Test deletion out of range MINID
bool Tester::testDeletionOutOfRangeMin()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 10;
    int tempID = 450;
    int ID = 0;

    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        if (i == teamSize / 2) tempID = ID;//we store this ID for later use
        Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
        team.insert(robot);
    }
    team.remove(tempID);
    cout << "Dump after inserting " << teamSize << " nodes:\n\n";
    team.dumpTree();
    if (team.findThisBot(team.m_root, tempID)) {
        return false;
    }
    return true;
}

// Test insertion out of range MAXID
bool Tester::testDeletionOutOfRangeMax()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 10;
    int tempID = 776435666;
    int ID = 0;

    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        if (i == teamSize / 2) tempID = ID;//we store this ID for later use
        Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
        team.insert(robot);
    }
    team.remove(tempID);
    cout << "Dump after inserting " << teamSize << " nodes:\n\n";
    team.dumpTree();
    if (team.findThisBot(team.m_root, tempID)) {
        return false;
    }
    return true;
}

// Test deletion all robots
bool Tester::testDeleteAllRobots()
{
    Random idGen(MINID, MAXID);
    Random typeGen(0, 4);
    Robot test;
    Swarm team;
    int teamSize = 1000;
    int ID = 0;

    for (int i = 0; i < teamSize; i++) {
        ID = idGen.getRandNum();
        Robot robot(ID, static_cast<ROBOTTYPE>(typeGen.getRandNum()));
        team.insert(robot);
    }
    cout << "Dump after inserting " << teamSize << " nodes:\n\n";
    team.dumpTree();
    team.clear();
    cout << "\nDump after deleting all robots: " << "\n\n";
    team.dumpTree();
    cout << "\n\nList of Robots after deleting all robots: " << "\n";
    team.listRobots();
    if (team.m_root == nullptr) {
        return true;
    }
    return false;
}