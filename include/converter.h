/***************************************************************************************************
 * Project: Unit Converter (Length & Weight)
 * File: converter.h
 * Author: Mobin Yousefi (GitHub: https://github.com/mobinyousefi-cs)
 * Created: 2025-11-23
 * Updated: 2025-11-23
 * License: MIT License (see LICENSE file for details)
 **************************************************************************************************/

#ifndef CONVERTER_H
#define CONVERTER_H

#include <stddef.h>

/*-------------------------------------------------------------------------------------------------
 * Length units
 * Base unit for length: meter (m)
 *------------------------------------------------------------------------------------------------*/

typedef enum
{
    LENGTH_METER = 0,
    LENGTH_KILOMETER,
    LENGTH_CENTIMETER,
    LENGTH_MILLIMETER,
    LENGTH_INCH,
    LENGTH_FOOT,
    LENGTH_YARD,
    LENGTH_MILE,
    LENGTH_UNIT_COUNT
} LengthUnit;

/*-------------------------------------------------------------------------------------------------
 * Weight units
 * Base unit for weight: kilogram (kg)
 *------------------------------------------------------------------------------------------------*/

typedef enum
{
    WEIGHT_KILOGRAM = 0,
    WEIGHT_GRAM,
    WEIGHT_MILLIGRAM,
    WEIGHT_POUND,
    WEIGHT_OUNCE,
    WEIGHT_TONNE,
    WEIGHT_UNIT_COUNT
} WeightUnit;

/*-------------------------------------------------------------------------------------------------
 * Conversion API
 *------------------------------------------------------------------------------------------------*/

/**
 * Convert length from one unit to another.
 *
 * @param value  Value to convert.
 * @param from   Source length unit.
 * @param to     Target length unit.
 * @return       Converted value, or NaN on error (invalid unit).
 */
double convert_length(double value, LengthUnit from, LengthUnit to);

/**
 * Convert weight from one unit to another.
 *
 * @param value  Value to convert.
 * @param from   Source weight unit.
 * @param to     Target weight unit.
 * @return       Converted value, or NaN on error (invalid unit).
 */
double convert_weight(double value, WeightUnit from, WeightUnit to);

/*-------------------------------------------------------------------------------------------------
 * Utility API: unit names for display
 *------------------------------------------------------------------------------------------------*/

/**
 * Get a human-readable name for a length unit (e.g., "meter (m)").
 *
 * @param unit  Length unit.
 * @return      String literal with the unit name, or "Unknown" on error.
 */
const char *length_unit_name(LengthUnit unit);

/**
 * Get a human-readable name for a weight unit (e.g., "kilogram (kg)").
 *
 * @param unit  Weight unit.
 * @return      String literal with the unit name, or "Unknown" on error.
 */
const char *weight_unit_name(WeightUnit unit);

#endif /* CONVERTER_H */
