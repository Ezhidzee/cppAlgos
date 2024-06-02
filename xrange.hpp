#pragma once

#include <iterator>

template<typename T>
class xrange {
private:
    T rangeBegin;

    T rangeEnd;

    T rangeStep;
public:
    using value_type = T;

    using reference = T &;

    using pointer = T *;

    using difference_type = std::ptrdiff_t;

    using iterator_concept = std::input_iterator_tag;

    using iterator_category = std::input_iterator_tag;

    xrange(T _rangeBegin, T _rangeEnd, T _rangeStep = T(1)) : rangeBegin(_rangeBegin), rangeEnd(_rangeEnd),
                                                              rangeStep(_rangeStep) {
        if (_rangeEnd == _rangeBegin) {
            throw std::range_error("Range cannot be empty");
        } else if (_rangeStep == T()) {
            throw std::range_error("Step cannot be zero");
        } else if ((_rangeBegin < _rangeEnd && _rangeStep < T()) || (_rangeBegin > _rangeEnd && _rangeStep > T())) {
            throw std::range_error("Negative step");
        }
    }

    explicit xrange(T _rangeEnd) : rangeBegin(T(0)), rangeEnd(_rangeEnd), rangeStep(T(1)) {
        if (_rangeEnd == rangeBegin) throw std::range_error("Range cannot be empty");
    }

    xrange &operator=(const xrange &v) {
        rangeBegin = v.rangeBegin;
        rangeEnd = v.rangeEnd;
        rangeStep = v.rangeStep;
    }

    ~xrange() = default;

    xrange &begin() { return *this; }

    xrange &end() { return *this; }

    value_type operator*() { return rangeBegin; }

    pointer operator->() { return &rangeBegin; }

    xrange &operator++() {
        rangeBegin = rangeBegin + rangeStep;
        return *this;
    }

    xrange operator++(int) {
        xrange t = *this;
        rangeBegin = rangeBegin + rangeStep;
        return t;
    }

    bool operator==(xrange &v) {
        return rangeBegin == v.rangeBegin && rangeEnd == v.rangeEnd && rangeStep == v.rangeStep;
    }

    bool operator!=(xrange &v) {
        if (rangeStep > T()) {
            return rangeBegin < v.rangeEnd;
        } else return rangeBegin > v.rangeEnd;
    }
};