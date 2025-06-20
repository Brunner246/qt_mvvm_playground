#include <QApplication>
#include <QPushButton>
#include <QUuid>

#include "UserModel.h"
#include "UserViewModel.h"
#include <compare> // für C++20

class Integer {
private:
    int value;

public:
    explicit Integer(const int v) : value(v) {
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


int main(int argc, char *argv[]) {
    const auto op1 = [](const int a, const int b) {
        return a + b;
    };

    const auto l1 = Integer(1);
    const auto l2 = Integer(2);

    l1 == l2 ? qDebug() << "l1 is equal to l2" : qDebug() << "l1 is not equal to l2";


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
    efficient.reserve(10000); // Vorallokation einer angemessenen Größe
    for (int i = 0; i < 1000; i++) {
        efficient += std::to_string(i);
    }


    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    auto userModel = UserModel("Hans", "angmei@gmal.com");
    const auto userViewModel = new UserViewModel(&userModel);
    QObject::connect(&button, &QAbstractButton::clicked, []() {
        qDebug() << "Hello world!";
    });
    QObject::connect(&button, &QAbstractButton::clicked, userViewModel, [userViewModel] {
        // create a random UUID
        const auto uuid = QUuid::createUuid();

        userViewModel->setEmail(QString("newMail_%1@gmail.com").arg(uuid.toString(QUuid::WithoutBraces)));
    });
    QObject::connect(userViewModel, &UserViewModel::emailChanged, [](const QString &email) {
        qInfo() << "Email changed to:" << email;
    });

    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
