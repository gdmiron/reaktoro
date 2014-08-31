/*
 * Reaktor is a C++ library for computational reaction modelling.
 *
 * Copyright (C) 2014 Allan Leal
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// C++ includes
#include <functional>
#include <vector>

// Reaktor includes
#include <Reaktor/Common/Index.hpp>
#include <Reaktor/Common/Matrix.hpp>
#include <Reaktor/Common/PartialScalar.hpp>
#include <Reaktor/Common/PartialUtils.hpp>
#include <Reaktor/Common/Vector.hpp>

namespace Reaktor {

/**
 * Defines a type that represents the result of a vector-valued function and its gradient and Hessian
 *
 * A @ref PartialVector instance is a convenient way of expressing the result of a vector-valued function
 * evaluation that possibly includes its gradient and Hessian. See below for an example of its usage.
 *
 * @code
 * PartialVector myVectorFunction(double x, double y)
 * {
 *     // Creates a PartialVector instance with dimension 2
 *     PartialVector res = partialScalar(zeros(2), zeros(2, 2));
 *
 *     // Sets the function result of the evaluation
 *     func(res) << x + y, x - y;
 *
 *     // Sets the gradient result of the evaluation
 *     grad(res) << 1,  1,
 *                  1, -1;
 *
 *     return res;
 * }
 * @endcode
 *
 * In the code above, a vector-valued function @c myVectirFunction is defined. The utility function
 * @ref partialVector is used to create a @ref PartialVector instance, while the functions @ref func and
 * @ref grad are used to access the function and gradient results of the function evaluation.
 *
 * @see partialVector, func, grad, hessian
 */
using PartialVector = std::tuple<Vector, Matrix, std::vector<Matrix>>;

/**
 * Creates a @ref PartialVector instance
 * @param val The value of the function evaluation
 * @return A @ref PartialVector instance with uninitialized gradient and Hessian
 */
template<typename Value>
inline auto partialVector(Value&& val) -> PartialVector
{
    return PartialVector{std::forward<Value>(val), Matrix(), std::vector<Matrix>()};
}

/**
 * Creates a @ref PartialVector instance
 * @param val The value of the function evaluation
 * @param grad The gradient of the function evaluation
 * @return A @ref PartialVector instance with uninitialized Hessian
 */
template<typename Value, typename Grad>
inline auto partialVector(Value&& val, Grad&& grad) -> PartialVector
{
    return PartialVector{std::forward<Value>(val), std::forward<Grad>(grad), std::vector<Matrix>()};
}

/**
 * Creates a @ref PartialVector instance
 * @param val The value of the function evaluation
 * @param grad The gradient of the function evaluation
 * @param hessian The Hessian of the function evaluation
 * @return A @ref PartialVector instance
 */
template<typename Value, typename Grad, typename Hessian>
inline auto partialVector(Value&& val, Grad&& grad, Hessian&& hessian) -> PartialVector
{
    return PartialVector{std::forward<Value>(val), std::forward<Grad>(grad), std::forward<Hessian>(hessian)};
}

/**
 * Creates a @ref PartialScalar instance as the component of a @ref PartialVector instance
 * @param vec The @ref PartialVector instance from which the @ref PartialScalar instance is built
 * @param i The index of the component of the @ref PartialVector instance that defines the @ref PartialScalar instance
 * @return A @ref PartialScalar instance
 */
inline auto partialScalar(const PartialVector& vec, Index i) -> PartialScalar
{
    PartialScalar sca;
    if(i < func(vec).rows()) func(sca) = func(vec)[i];
    if(i < grad(vec).rows()) grad(sca) = grad(vec).row(i);
    if(i < hessian(vec).size()) hessian(sca) = hessian(vec)[i];

    return sca;
}

} // namespace Reaktor
