#include <iterator>

/*
 * how can we check if a range is valid?
 * You can't. https://stackoverflow.com/questions/18266349/how-to-check-if-a-range-specified-by-iterators-is-valid */

namespace ezhidze {
    template<typename iterator, typename predicate>
    bool all_of(iterator first, iterator last, predicate pred) {
        if constexpr (std::is_base_of_v<std::input_iterator_tag, typename std::iterator_traits<iterator>::iterator_category>) {
            while (first != last) {
                if (!pred(*first)) return false;
                ++first;
            }
            return true;
        } else
            throw std::invalid_argument(
                    "Expected input_iterator, provided " + std::iterator_traits<iterator>::iterator_category);
    }

    template<typename iterator, typename predicate>
    bool any_of(iterator first, iterator last, predicate pred) {
        if constexpr (std::is_base_of_v<std::input_iterator_tag, typename std::iterator_traits<iterator>::iterator_category>) {
            while (first != last) {
                if (pred(*first)) return true;
                ++first;
            }
            return false;
        } else
            throw std::invalid_argument(
                    "Expected input_iterator, provided " + std::iterator_traits<iterator>::iterator_category);
    }

    template<typename iterator, typename predicate>
    bool none_of(iterator first, iterator last, predicate pred) {
        if constexpr (std::is_base_of_v<std::input_iterator_tag, typename std::iterator_traits<iterator>::iterator_category>) {
            while (first != last) {
                if (pred(*first)) return false;
                ++first;
            }
            return true;
        } else
            throw std::invalid_argument(
                    "Expected input_iterator, provided " + std::iterator_traits<iterator>::iterator_category);
    }

    template<typename iterator, typename predicate>
    bool one_of(iterator first, iterator last, predicate pred) {
        if constexpr (std::is_base_of_v<std::input_iterator_tag, typename std::iterator_traits<iterator>::iterator_category>) {
            uint64_t counter = 0;
            while (first != last) {
                if (counter > 1) return false;
                if (pred(*first)) ++counter;
                ++first;
            }
            if (counter == 0) return false;
            return true;
        } else
            throw std::invalid_argument(
                    "Expected input_iterator, provided " + std::iterator_traits<iterator>::iterator_category);
    }

    template<typename iterator>
    bool is_sorted(iterator first, iterator last) {
        if constexpr (std::is_base_of_v<std::forward_iterator_tag, typename std::iterator_traits<iterator>::iterator_category>) {
            iterator next = first;
            for (++next; next != last; ++first, ++next) if (*next < *first) return false;
            return true;
        } else
            throw std::invalid_argument(
                    "Expected forward_iterator, provided " + std::iterator_traits<iterator>::iterator_category);
    }

    template<typename iterator, typename predicate>
    bool is_sorted(iterator first, iterator last, predicate pred) {
        if constexpr (std::is_base_of_v<std::forward_iterator_tag, typename std::iterator_traits<iterator>::iterator_category>) {
            iterator next = first;
            for (++next; next != last; ++first, ++next) if (pred(*next, *first)) return false;
            return true;
        } else
            throw std::invalid_argument(
                    "Expected forward_iterator, provided " + std::iterator_traits<iterator>::iterator_category);
    }

    template<typename iterator, typename predicate>
    bool is_partitioned(iterator first, iterator last, predicate pred) {
        if constexpr (std::is_base_of_v<std::input_iterator_tag, typename std::iterator_traits<iterator>::iterator_category>) {
            while (first != last && pred(*first)) ++first;

            while (first != last) {
                if (pred(*first)) return false;
                ++first;
            }

            return true;
        } else
            throw std::invalid_argument(
                    "Expected input_iterator, provided " + std::iterator_traits<iterator>::iterator_category);
    }

    template<typename iterator, typename T>
    iterator find_not(iterator first, iterator last, const T& v) {
        if constexpr (std::is_base_of_v<std::input_iterator_tag, typename std::iterator_traits<iterator>::iterator_category>) {
            while (first != last) {
                if (*first != v) return first;
                ++first;
            }
            return last;
        } else
            throw std::invalid_argument(
                    "Expected input_iterator, provided " + std::iterator_traits<iterator>::iterator_category);
    }

    template<typename iterator, typename T>
    iterator find_backward(iterator first, iterator last, const T& v) {
        if constexpr (std::is_base_of_v<std::bidirectional_iterator_tag, typename std::iterator_traits<iterator>::iterator_category>) {
            iterator previous = last;
            --previous;
            while (previous != first) {
                if (*previous == v) return previous;
                --previous;
            }
            if (*first == v) return first;

            return last;
        } else
            throw std::invalid_argument(
                    "Expected bidirectional_iterator, provided " + std::iterator_traits<iterator>::iterator_category);
    }

    template<typename iterator>
    bool is_palindrome(iterator first, iterator last) {
        if constexpr (std::is_base_of_v<std::bidirectional_iterator_tag, typename std::iterator_traits<iterator>::iterator_category>) {
            --last;
            while (first != last) {
                if (*first != *last) return false;
                ++first;
                --last;
            }
            return true;
        } else
            throw std::invalid_argument(
                    "Expected bidirectional_iterator, provided " + std::iterator_traits<iterator>::iterator_category);
    }

    template<typename iterator, typename predicate>
    bool is_palindrome(iterator first, iterator last, predicate pred) {
        if constexpr (std::is_base_of_v<std::bidirectional_iterator_tag, typename std::iterator_traits<iterator>::iterator_category>) {
            --last;
            while (first != last) {
                if (!pred(*first, *last)) return false;
                ++first;
                --last;
            }
            return true;
        } else
            throw std::invalid_argument(
                    "Expected bidirectional_iterator, provided " + std::iterator_traits<iterator>::iterator_category);
    }
}