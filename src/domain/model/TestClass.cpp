//
// Created by brunn on 22/06/2025.
//

#include "include/TestClass.h"

#include <iostream>

void TestClass::doSomething() const {
    std::cout << "Doing something in TestClass" << std::endl;
    if (m_callback) {
        m_callback();
    } else {
        std::cout << "No callback registered" << std::endl;
    }
}

void TestClass::registerCallback(callback cb) {
    m_callback = std::move(cb);
}
