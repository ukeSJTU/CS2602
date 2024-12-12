#include <iostream>

#include "SeqString.h"

using namespace datastructures;

int main()
{
    String s1(50), s2("abd"), s3(s2), s4("sjtu");

    std::cout << "Initial state of strings:" << std::endl;
    std::cout << "s1: ";
    s1.disp();
    std::cout << std::endl;
    std::cout << "s2: ";
    s2.disp();
    std::cout << std::endl;
    std::cout << "s3: ";
    s3.disp();
    std::cout << std::endl;

    std::cout << "Length of s2 is: " << s2.length() << std::endl;

    if (s2.equal(s3)) {
        std::cout << "s2 is equal to s3" << std::endl;
    } else {
        std::cout << "s2 is not equal to s3" << std::endl;
    }

    if (s1.equal(s3)) {
        std::cout << "s1 is equal to s3" << std::endl;
    } else {
        std::cout << "s1 is not equal to s3" << std::endl;
    }

    s1.assign(s2);
    std::cout << "After assigning s2 to s1, s1: ";
    s1.disp();
    std::cout << std::endl;

    s1.insert(1, s4);
    std::cout << "After inserting s4 into s1 at position 1, s1: ";
    s1.disp();
    std::cout << std::endl;

    s3.remove(1, 2);
    std::cout << "After removing 2 characters from s3 starting at position 1, s3: ";
    s3.disp();
    std::cout << std::endl;

    String &s5 = s1.subString(2, 4);
    std::cout << "Substring of s1 from position 2 with length 4, s5: ";
    s5.disp();
    std::cout << std::endl;

    return 0;
}