#include <limits>

#include "types.h"

const dish::IntegerT dish::BOOLEAN_NBYTES(static_cast< dish::IntegerT >(sizeof(dish::BooleanT)));
const dish::BooleanT dish::BOOLEAN_MIN(false);
const dish::BooleanT dish::BOOLEAN_MAX(true);

const dish::IntegerT dish::INTEGER_NBYTES(static_cast< dish::IntegerT >(sizeof(dish::IntegerT)));
const dish::IntegerT dish::INTEGER_MIN(std::numeric_limits< dish::IntegerT >::min());
const dish::IntegerT dish::INTEGER_MAX(std::numeric_limits< dish::IntegerT >::max());
const dish::IntegerT dish::INTEGER_EPS(1);

const dish::IntegerT dish::REAL_NBYTES(static_cast< dish::IntegerT >(sizeof(dish::RealT)));
const dish::RealT dish::REAL_MIN(std::numeric_limits< dish::RealT >::min());
const dish::RealT dish::REAL_MAX(std::numeric_limits< dish::RealT >::max());
const dish::RealT dish::REAL_EPS(std::numeric_limits< dish::RealT >::epsilon());

