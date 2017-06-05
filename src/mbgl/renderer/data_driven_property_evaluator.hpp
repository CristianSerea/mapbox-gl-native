#pragma once

#include <mbgl/style/property_value.hpp>
#include <mbgl/renderer/property_evaluation_parameters.hpp>
#include <mbgl/renderer/possibly_evaluated_property_value.hpp>

namespace mbgl {

template <typename T>
class DataDrivenPropertyEvaluator {
public:
    using ResultType = PossiblyEvaluatedPropertyValue<T>;

    DataDrivenPropertyEvaluator(const PropertyEvaluationParameters& parameters_, T defaultValue_)
        : parameters(parameters_), defaultValue(std::move(defaultValue_)) {
    }

    ResultType operator()(const style::Undefined&) const {
        return ResultType(defaultValue);
    }

    ResultType operator()(const T& constant) const {
        return ResultType(constant);
    }

    ResultType operator()(const style::CameraFunction<T>& function) const {
        return ResultType(function.evaluate(parameters.z));
    }

    template <class Function>
    ResultType operator()(const Function& function) const {
        return ResultType(function);
    }

private:
    const PropertyEvaluationParameters& parameters;
    T defaultValue;
};

template <typename T>
class DataDrivenFlooredPropertyEvaluator {
public:
    using ResultType = PossiblyEvaluatedPropertyValue<T>;

    DataDrivenFlooredPropertyEvaluator(const PropertyEvaluationParameters& parameters_,
                                       T defaultValue_)
        : parameters(floorParameters(parameters_)), defaultValue(std::move(defaultValue_)) {
    }

    ResultType operator()(const style::Undefined&) const {
        return ResultType(defaultValue);
    }

    ResultType operator()(const T& constant) const {
        return ResultType(constant);
    }

    ResultType operator()(const style::CameraFunction<T>& function) const {
        return ResultType(function.evaluate(parameters.z));
    }

    template <class Function>
    ResultType operator()(const Function& function) const {
        return ResultType(function);
    }

private:
    const PropertyEvaluationParameters parameters;
    T defaultValue;

    PropertyEvaluationParameters floorParameters(const PropertyEvaluationParameters& parameters_) {
        PropertyEvaluationParameters copy = parameters_;
        copy.z = floor(copy.z);
        return copy;
    }
};

} // namespace mbgl
