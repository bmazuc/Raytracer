#ifndef RAYTRACER_APPLICATION_POSITIVE_INT_VALIDATOR_H
#define RAYTRACER_APPLICATION_POSITIVE_INT_VALIDATOR_H

#include <QIntValidator>

/**
 * Extends QIntValidator with a configurable lower bound
 * for application input fields.
 */
class PositiveIntValidator : public QIntValidator
{
    Q_OBJECT

public:
    explicit PositiveIntValidator(unsigned int inMin, QObject* parent = nullptr);

    /**
     *  Extends QIntValidator to reject values below the specified minimum.
     *
     * @param input Input string being validated.
     * @param pos Current cursor position in the input string.
     * @return Validation state indicating whether the input is acceptable.
     */
    QValidator::State validate(QString& input, int& pos) const override;

private:
    int min;
};

#endif // RAYTRACER_APPLICATION_POSITIVE_INT_VALIDATOR_H