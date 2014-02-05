#ifndef INCORRESPONDENTEXCEPTION_H
#define INCORRESPONDENTEXCEPTION_H

#include <exception>
#include <QString>

using namespace std;

class IncorrespondentException : public exception
{
public:
    IncorrespondentException(QString message);
    ~IncorrespondentException() throw() {}

    virtual const char* what() const throw();

private:
    QString mess;
};

#endif // INCORRESPONDENTEXCEPTION_H
