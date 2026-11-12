#ifndef RAYTRACER_APPLICATION_POSITIVE_INT_VALIDATOR_H
#define RAYTRACER_APPLICATION_POSITIVE_INT_VALIDATOR_H

#include <QIntValidator>

class PositiveIntValidator : public QIntValidator
{
    Q_OBJECT

public:
    explicit PositiveIntValidator(unsigned int inMin, QObject* parent = nullptr);

    QValidator::State validate(QString& input, int& pos) const override;

private:
    int min;
};

#endif // RAYTRACER_APPLICATION_POSITIVE_INT_VALIDATOR_H