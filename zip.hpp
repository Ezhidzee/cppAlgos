#pragma once

#include <iterator>
#include <utility>

template<typename T, typename U>
class zip {
private:
    T::iterator container1Begin;

    T::iterator container1End;

    U::iterator container2Begin;

    U::iterator container2End;
public:
    using value_type = std::pair<typename T::value_type, typename U::value_type>;

    using reference = std::pair<typename T::value_type, typename U::value_type> &;

    using pointer = std::pair<typename T::value_type, typename U::value_type> *;

    using difference_type = std::ptrdiff_t;

    using iterator_concept = std::input_iterator_tag;

    using iterator_category = std::input_iterator_tag;

    zip(T &c1, U &c2) {
        container1Begin = c1.begin();
        container1End = c1.end();
        container2Begin = c2.begin();
        container2End = c2.end();
    }

    zip &operator=(const zip &v) {
        container1Begin = v.container1Begin;
        container1End = v.container1End;
        container2Begin = v.container2Begin;
        container2End = v.container2End;
    }

    ~zip() = default;

    zip &begin() { return *this; }

    zip &end() { return *this; }

    value_type operator*() { return std::pair<typename T::value_type, typename U::value_type>(*container1Begin, *container2Begin); }

    zip &operator++() {
        ++container1Begin;
        ++container2Begin;
        return *this;
    }

    zip operator++(int) {
        zip t = *this;
        ++container1Begin;
        ++container2Begin;
        return t;
    }

    bool operator==(zip &v) {
        return container1Begin == v.container1Begin && container1End == v.container1End &&
               container2Begin == v.container2Begin && container2End == v.container2End;
    }

    bool operator!=(zip &v) { return container1Begin != container1End && container2Begin != container2End; }
};