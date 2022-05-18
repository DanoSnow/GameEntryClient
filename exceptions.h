#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>
using namespace std;

class IncompleteParameters : public runtime_error{
public:
    IncompleteParameters();
};
class Rejected : public runtime_error{
public:
    Rejected();
};
class WrongConfirm : public runtime_error{
public:
    WrongConfirm();
};

#endif // EXCEPTIONS_H
