#!usr/bin/python3
#create_function.py
import random

def _math_function_arguments(
        _math_function, argument_count,
        number_low, number_high):
    """
    Creates pseudo-random arguments for given _math_function
    Reads number of STL functions arguments from dict
    Uses recursion, use with cautious [may throw!]
    """

    _math_function += "("
    i=1
    _math_function += _number_or_function(number_low, number_high)
    while i < argument_count:
        _math_function += ','
        _math_function += _number_or_function(number_low, number_high)
        i+=1
    return _math_function + ")"


def _number_or_function(number_low, number_high):
    """
    Returns one of the following:
    - x (function argument)
    - random number (in range [number_low, number_high])
    - function (taken from _math_function dictionary)
    """
    if random.randint(0,1) == 0:
        return "x"
    else:
        if random.randint(0,1) == 1:
            return str(round(random.uniform(number_low, number_high), 4))
        else:
            function, argument_count = random.choice(list(_math_function.items()))
            #Create random arguments for chosen function
            return _math_function_arguments(
                    function, argument_count,
                    number_low, number_high
                    )

def create_function(expression_count, number_low, number_high):
    """
    Creates randomly generated function
    expression_count - how many expressions (divided by parentheses) am I
    supposed to make?
    IMORTANT: Possible over/underflows, quite unpredictive function
    """
    number_low, number_high = float(number_low), float(number_high)
    function = "return (" + _number_or_function(number_low, number_high) + ")"

    i=0
    while i < int(expression_count):
        function += random.choice(_sign)
        function += "("
        function += _number_or_function(number_low, number_high)
        function += ")"
        i+=1
    function += ";"
    return function


_sign = ["+", "-", "/", "*"]
_math_function = {
        "std::abs":    1,
        "std::fma":    3,
        "std::fmax":   2,
        "std::fmin":   2,
        "std::fdim":   2,
        "std::exp":    1,
        "std::exp2":   1,
        "std::pow":    2,
        "std::log":    1,
        "std::log10":  1,
        "std::log2":   1,
        "std::log1p":  1,
        "std::sqrt":   1,
        "std::cbrt":   1,
        "std::hypot":  2,
        "std::sin":    1,
        "std::cos":    1,
        "std::tan":    1,
        "std::asin":   1,
        "std::atan":   1,
        "std::atan2":  2,
        "std::sinh":   1,
        "std::asinh":  1,
        "std::cosh":   1,
        "std::acosh":  1,
        "std::tanh":   1,
        "std::atanh":  1,
        "std::erf":    1,
        "std::erfc":   1,
        "std::tgamma": 1,
        "std::floor":  1,
        "std::ceil":   1,
        "std::trunc":  1,
        "std::ilogb":  1
        }

if __name__ == "__main__":
    create_function(20,-100,100)
