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

    std::string efficient;
    efficient.reserve(10000);
    for (int i = 0; i < 1000; i++) {
        efficient += std::to_string(i);
    }


    //QApplication app(argc, argv);

    const auto testClass = std::make_unique<TestClass>();
    testClass->registerCallback([]() {
        qDebug() << "Callback executed!";
    });
    testClass->doSomething();

    // const auto postService = new QtPostService();
    // const auto postUseCase = new FetchPostUseCase(postService);
    // const auto postViewModel = new PostViewModel(postUseCase);
    // postViewModel->fetchPost(2);
    // qDebug() << "Post title:" << postViewModel->title();
    // qDebug() << "Post body:" << postViewModel->body();

    // QMainWindow mainWindow;
    // mainWindow.setWindowTitle("CustomButton Example");
    // mainWindow.resize(300, 200);
    //
    // const auto centralWidget = new QWidget(&mainWindow);
    // const auto layout = new QVBoxLayout(centralWidget);
    // layout->setAlignment(Qt::AlignCenter);
    // mainWindow.setCentralWidget(centralWidget);
    //
    // const auto button = new CustomButton("Click me", centralWidget);
    // layout->addWidget(button);
    //
    // const auto viewModel = new CustomButtonViewModel();
    // qDebug() << CustomButtonViewModel::CallbackType::OnStyleChanged;
    //
    // QObject::connect(button, &QPushButton::clicked, [viewModel]() {
    //     viewModel->onClicked();
    // });
    //
    // viewModel->registerCallback(CustomButtonViewModel::OnTextChanged, [button](const QString &text) {
    //     button->setText(text);
    // });
    // viewModel->registerCallback(CustomButtonViewModel::OnStyleChanged, [button](const QString &style) {
    //     button->setStyleSheet(style);
    // });
    // viewModel->registerCallback(CustomButtonViewModel::OnLogging, [](const QString &message) {
    //     qDebug() << "Log:" << message;
    // });
    //
    // const auto styleTimer = new QTimer(centralWidget);
    // styleTimer->setInterval(3000);
    //
    // QObject::connect(styleTimer, &QTimer::timeout, [toggle = false, viewModel]() mutable {
    //     const QString altStyle = "QPushButton {"
    //             "    background-color: #e84a86;"
    //             "    color: white;"
    //             "    border-radius: 6px;"
    //             "    padding: 8px 16px;"
    //             "    font-size: 14px;"
    //             "    font-weight: bold;"
    //             "}"
    //             "QPushButton:hover {"
    //             "    background-color: #d83a76;"
    //             "}"
    //             "QPushButton:pressed {"
    //             "    background-color: #c82a66;"
    //             "}";
    //
    //     const auto style = toggle ? CustomButton::defaultStyle() : altStyle;
    //     toggle = !toggle;
    //     qDebug() << "Changing style to:" << toggle;
    //     viewModel->setStyle(style);
    // });
    //
    // styleTimer->start();
    // viewModel->setText("Initial Text");
    //
    // mainWindow.show();
    // return QApplication::exec();

    // return EXIT_SUCCESS;

    QCoreApplication app(argc, argv);

    auto* service = new QtPostService();
    auto* useCase = new FetchPostUseCase(service);
    auto* viewModel = new PostViewModel(useCase);

    QObject::connect(viewModel, &PostViewModel::titleChanged, [viewModel]() {
        std::cout << "Post Title:" << viewModel->title().toStdString();
    });

    QObject::connect(viewModel, &PostViewModel::bodyChanged, [viewModel]() {
        std::cout << "Post Body:" << viewModel->body().toStdString();

        QCoreApplication::quit();
    });

    QTimer::singleShot(0, [viewModel]() {
        viewModel->fetchPost(1);
    });

    return QCoreApplication::exec();
}
