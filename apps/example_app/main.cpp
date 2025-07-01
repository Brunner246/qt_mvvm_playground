#include <QApplication>
#include <QPushButton>
#include <QUuid>

#include <compare>
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include <QTimer>
#include "CustomButtonViewModel.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <ranges>

#include <PostViewModel.h>
#include <QtPostService.h>
#include <TestClass.h>

#include "CprPostService.h"
#include "Dialog.h"

class InterfaceA {
public:
    virtual ~InterfaceA() = default;

    virtual void doSomething() = 0;
};

class InterfaceB {
public:
    virtual ~InterfaceB() = default;

    virtual void doSomethingElse() = 0;
};

void doAStuff(InterfaceA *a) {
    if (a) {
        a->doSomething();
    } else {
        qDebug() << "InterfaceA is null";
    }
}

void doBStuff(InterfaceB *b) {
    if (b) {
        b->doSomethingElse();
    } else {
        qDebug() << "InterfaceB is null";
    }
}

class Impl : public InterfaceA, public InterfaceB {
public:
    ~Impl() override = default;

    void doSomething() override {
        qDebug() << "Doing something in Impl";
    }

    void doSomethingElse() override {
        qDebug() << "Doing something else";
    }
};


class Integer {
private:
    int value;

public:
    explicit Integer(const int v) : value(v) {
    }

    operator int() const {
        return value;
    }

    auto operator<=>(const Integer &other) const = default;
};

int add(const int a, const int b) {
    return a + b;
}

using operation = int (*)(int, int);

class Adder
{
public:
    int add(int a, int b) const {
        return a + b;
    }
};

void onCallback(int a, int b, operation cb) {
    const auto result = cb(a, b);
    qDebug() << result;
}

template<typename T, typename Func>
auto operator|(T &&value, Func &&func) -> decltype(func(std::forward<T>(value))) {
    return func(std::forward<T>(value));
}

std::string toUpper(const std::string &str) {
    std::string result = str;
    auto resultView = str | std::views::transform([](const char c) { return std::toupper(c); });
    result.resize(resultView.size());
    std::ranges::copy(resultView, result.begin());
    // std::ranges::transform(result, result.begin(),
    //                        [](const unsigned char c) { return std::toupper(c); });
    return result;
}

std::string addExclamation(const std::string &str) {
    return str + "!";
}


int main(int argc, char *argv[]) {
    std::ignore = argc;
    std::ignore = argv;
    const auto impl = std::make_unique<Impl>();
    doAStuff(impl.get());
    doBStuff(impl.get());


    const auto op1 = [](const int a, const int b) {
        return a + b;
    };

    const auto l1 = Integer(1);
    const auto l2 = Integer(2);

    qDebug() << "Stack variable " << &l1 << "and" << &l2;
    l1 == l2 ? qDebug() << "l1 is equal to l2" : qDebug() << "l1 is not equal to l2";

    using namespace std::literals::string_literals;
    std::string result2 = "hello"s
                          | toUpper
                          | addExclamation;
    qDebug() << "Transformed string:" << QString::fromStdString(result2);

    // int (*operation)(int, int);

    // operation = op1;
    // qInfo() << "Result of add(1, 2):" << operation(1, 2);
    // operation = add;
    // qInfo() << "Result of add(3, 4):" << operation(3, 4);
    onCallback(1, 2, op1);
    onCallback(3, 4, add);
    onCallback(5, 6, [](const int a, const int b) {
        return a % b;
    });
    // using operation = std::function<int(int, int)>;
    // const auto adder = Adder();
    // onCallback(10, 20, [&adder](int a, int b) { return adder.add(a, b); });
    // onCallback(10, 20, std::bind(&Adder::add, &adder, std::placeholders::_1, std::placeholders::_2));


    std::string efficient;
    efficient.reserve(10000);
    for (int i = 0; i < 1000; i++) {
        efficient += std::to_string(i);
    }

    QApplication::addLibraryPath("D:\\Qt6-msvc\\6.7.0\\msvc2019_64\\plugins");
    QApplication app(argc, argv);

    //QApplication app(argc, argv);

    const auto testClass = std::make_unique<TestClass>();
    testClass->registerCallback([]() {
        qDebug() << "Callback executed!";
    });
    testClass->doSomething();

    const auto vm = std::make_unique<CustomButtonViewModel>();
    vm->registerCallback(CustomButtonViewModel::OnTextChanged, [](const QString &text) {
        qDebug() << "Text changed to:" << text;
    });

    const auto dialog = new Dialog(vm.get());
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();

    // QCoreApplication app(argc, argv);
    //
    // auto* service = new CprPostService();
    // auto* useCase = new FetchPostUseCase(service);
    // auto* viewModel = new PostViewModel(useCase);
    //
    // QObject::connect(viewModel, &PostViewModel::titleChanged, [viewModel]() {
    //     std::cout << "Post Title:" << viewModel->title().toStdString();
    // });
    //
    // QObject::connect(viewModel, &PostViewModel::bodyChanged, [viewModel]() {
    //     std::cout << "Post Body:" << viewModel->body().toStdString();
    //
    //     QCoreApplication::quit();
    // });
    //
    // QTimer::singleShot(0, [viewModel]() {
    //     viewModel->fetchPost(1);
    // });
    //
    // return QCoreApplication::exec();

    return QApplication::exec();
}
