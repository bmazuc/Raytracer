#include "PositiveIntValidator.h"

PositiveIntValidator::PositiveIntValidator(unsigned int inMin, QObject* parent)
    : QIntValidator(static_cast<int>(inMin), INT_MAX, parent), min(inMin)
{
}

QValidator::State PositiveIntValidator::validate(QString& input, int& pos) const
{
    // Allow empty string so the user can clear the field
    if (input.isEmpty()) 
    {
        return QValidator::Intermediate;
    }

    bool ok = false;
    int value = input.toInt(&ok);

    if (!ok || value < min)
    {
        return QValidator::Invalid;
    }

    // Let the base class enforce the 1 to INT_MAX upper bound
    return QIntValidator::validate(input, pos);
}