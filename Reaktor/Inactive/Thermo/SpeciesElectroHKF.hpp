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

namespace Reaktor {

// Forward declarations
class AqueousSpecies;
struct SpeciesElectro;
struct WaterThermo;

struct FunctionG
{
    FunctionG();

    FunctionG(double T, double P, const WaterThermo& wt);

    /// The function g at temperature T and pressure P
    double g;

    /// The first-order partial derivative of function g with respect to temperature
    double gT;

    /// The first-order partial derivative of function g with respect to pressure
    double gP;

    /// The second-order partial derivative of function g with respect to temperature
    double gTT;

    /// The second-order partial derivative of function g with respect to temperature and pressure
    double gTP;

    /// The second-order partial derivative of function g with respect to pressure
    double gPP;
};

/// Calculate the electrostatic state of the aqueous species
auto speciesElectroHKF(double T, double P, const AqueousSpecies& species) -> SpeciesElectro;

/// Calculate the electrostatic state of the aqueous species using the g-function state
auto speciesElectroHKF(const FunctionG& g, const AqueousSpecies& species) -> SpeciesElectro;

} // namespace Reaktor
