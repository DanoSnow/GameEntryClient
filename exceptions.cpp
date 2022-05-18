#include "exceptions.h"

IncompleteParameters::IncompleteParameters() : runtime_error ("Incomplete parameters at player or password"){}
Rejected::Rejected() : runtime_error ("Cancel"){}
WrongConfirm::WrongConfirm() : runtime_error ("Please, confirm your password"){}
