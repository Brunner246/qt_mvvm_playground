//
// Created by brunn on 22/06/2025.
//

#ifndef TESTCLASS_H
#define TESTCLASS_H
#include <functional>
#include <model_export.h>

class MODEL_API TestClass {
public:
    void doSomething() const;

    using callback = std::function<void()>;
    void registerCallback(callback cb);

private:
    callback m_callback;

};



#endif //TESTCLASS_H
