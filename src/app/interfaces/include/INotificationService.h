//
// Created by brunn on 22/06/2025.
//

#ifndef INOTIFICATIONSERVICE_H
#define INOTIFICATIONSERVICE_H
#include <string>

class INotificationService {
public:
    virtual ~INotificationService() = default;

    virtual void notify(std::string message) = 0;
};

#endif //INOTIFICATIONSERVICE_H
