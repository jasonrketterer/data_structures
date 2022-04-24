//
// Created by Jason Ketterer on 4/24/22.
//

#ifndef LIST_TEST_H
#define LIST_TEST_H

#include <iostream>
#include <sstream>
#include <string>

template <typename T>
class ListIterator;

template <typename T>
class ConstListIterator;

template <typename T>
class List;

class ListTest {
public:
    explicit ListTest() : list{}, test_msgs{}, cout_strbuf{}, cout_output{}, cerr_output{} {
        // remember std::cout's stream buffer
        cout_strbuf = std::cout.rdbuf();
        // remember std::cerr's stream buffer
        cerr_strbuf = std::cerr.rdbuf();
        // redirect std::cout to string buffer cout_output
        std::cout.rdbuf(cout_output.rdbuf());
        // redirect std::cerr to string buffer cerr_output
        std::cerr.rdbuf(cerr_output.rdbuf());
    }
    ~ListTest() {
        list.Clear();
    }

    void runTests() {
        testPushFront();
        testPushBack();
        testPopFront();

        // restore std::cout's and std::cerr's buffers
        std::cout.rdbuf(cout_strbuf);
        std::cerr.rdbuf(cerr_strbuf);

        // print results
        std::cerr << test_msgs;
        std::cout << "\nList tests complete.\n";
    }

private:
    List<int> list;
    std::string test_msgs;
    std::streambuf * cout_strbuf;
    std::streambuf * cerr_strbuf;
    std::ostringstream cout_output;
    std::ostringstream  cerr_output;

    void reset() {
        cout_output.str("");
        cerr_output.str("");
        list.Clear();
    }

    void testPushFront() {
        list.PushFront(3); list.PushFront(2); list.PushFront(1);
        std::string expected = "1 , 2 , 3";
        list.Display(std::cout);
        if(cout_output.str() != expected) {
            test_msgs += "PushFront() did not match expected output: \n\n";
            test_msgs += "Output: " + cout_output.str() + "\n";
            test_msgs += "Expected: " + expected + "\n\n";
        }
        reset();
    }

    void testPushBack() {
        list.PushBack(1); list.PushBack(2); list.PushBack(3);
        std::string expected = "1 , 2 , 3";
        list.Display(std::cout);
        if(cout_output.str() != expected) {
            test_msgs += "PushBack() did not match expected output: \n\n";
            test_msgs += "Output:   " + cout_output.str() + "\n";
            test_msgs += "Expected: " + expected + "\n\n";
        }
        reset();
    }

    void testPopFront() {
        // attempt to pop empty list
        list.PopFront();
        std::string expected = List<int>::POP_FRONT_ERR_MSG + "\n";
        if(cerr_output.str() != expected) {
            test_msgs += "PopFront() on empty list did not match expected output: \n\n";
            test_msgs += "Output:   " + cerr_output.str() + "\n";
            test_msgs += "Expected: " + expected + "\n";
        }
        reset();
        expected = "";
        // test peeking at front of list and popping front
        list.PushFront(3); list.PushFront(2); list.PushFront(1);
        int front, expectedFront = 1;
        while(!list.Empty()) {
            front = list.Front();
            list.PopFront();
            if(front != expectedFront) {
                test_msgs += "PopFront() did not match expected output: \n\n";
                test_msgs += "Output:   " + std::to_string(front) + "\n";
                test_msgs += "Expected: " + std::to_string(expectedFront) + "\n";
            }
            expectedFront++;
        }
        reset();
    }
};

#endif //LIST_TEST_H
