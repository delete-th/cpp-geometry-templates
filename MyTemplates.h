// filename: MyTemplates.h
#ifndef MYTEMPLATES_H
#define MYTEMPLATES_H

#include <cmath>
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"

// =====================
// scalar_difference
// =====================
template <typename T>
double scalar_difference(const T& a, const T& b) {
    return std::abs(a.getScalarValue() - b.getScalarValue());
}

// =====================
// equals - relies on operator== being implemented for each type
// =====================
template <typename T>
bool equals(const T& a, const T& b) {
    return a == b; 
}

#endif

