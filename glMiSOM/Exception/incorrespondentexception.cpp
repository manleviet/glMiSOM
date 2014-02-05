#include "incorrespondentexception.h"

IncorrespondentException::IncorrespondentException(QString message)
{
    mess = message;
}

const char* IncorrespondentException::what() const throw()
{
    return mess.toStdString().c_str();
}
