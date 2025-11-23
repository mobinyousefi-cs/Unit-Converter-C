/***************************************************************************************************
 * Project: Unit Converter (Length & Weight)
 * File: converter.c
 * Author: Mobin Yousefi (GitHub: https://github.com/mobinyousefi-cs)
 * Created: 2025-11-23
 * Updated: 2025-11-23
 * License: MIT License (see LICENSE file for details)
 **************************************************************************************************/

#include "converter.h"

#include <math.h>

/*-------------------------------------------------------------------------------------------------
 * Internal conversion factors
 *
 * For length:  factors are in meters per unit.
 * For weight:  factors are in kilograms per unit.
 *------------------------------------------------------------------------------------------------*/

/* meters per length unit */
static const double LENGTH_FACTORS[LENGTH_UNIT_COUNT] = {
    [LENGTH_METER]      = 1.0,        /* meter */
    [LENGTH_KILOMETER]  = 1000.0,     /* kilometer */
    [LENGTH_CENTIMETER] = 0.01,       /* centimeter */
    [LENGTH_MILLIMETER] = 0.001,      /* millimeter */
    [LENGTH_INCH]       = 0.0254,     /* inch */
    [LENGTH_FOOT]       = 0.3048,     /* foot */
    [LENGTH_YARD]       = 0.9144,     /* yard */
    [LENGTH_MILE]       = 1609.344    /* mile */
};

/* kilograms per weight unit */
static const double WEIGHT_FACTORS[WEIGHT_UNIT_COUNT] = {
    [WEIGHT_KILOGRAM]   = 1.0,           /* kilogram */
    [WEIGHT_GRAM]       = 0.001,         /* gram */
    [WEIGHT_MILLIGRAM]  = 0.000001,      /* milligram */
    [WEIGHT_POUND]      = 0.45359237,    /* pound */
    [WEIGHT_OUNCE]      = 0.0283495231,  /* ounce */
    [WEIGHT_TONNE]      = 1000.0         /* tonne (metric ton) */
};

/*-------------------------------------------------------------------------------------------------
 * Length conversion
 *------------------------------------------------------------------------------------------------*/

double convert_length(double value, LengthUnit from, LengthUnit to)
{
    if (from < 0 || from >= LENGTH_UNIT_COUNT ||
        to   < 0 || to   >= LENGTH_UNIT_COUNT)
    {
        return NAN;
    }

    double in_meters = value * LENGTH_FACTORS[from];
    double result    = in_meters / LENGTH_FACTORS[to];
    return result;
}

/*-------------------------------------------------------------------------------------------------
 * Weight conversion
 *------------------------------------------------------------------------------------------------*/

double convert_weight(double value, WeightUnit from, WeightUnit to)
{
    if (from < 0 || from >= WEIGHT_UNIT_COUNT ||
        to   < 0 || to   >= WEIGHT_UNIT_COUNT)
    {
        return NAN;
    }

    double in_kg  = value * WEIGHT_FACTORS[from];
    double result = in_kg / WEIGHT_FACTORS[to];
    return result;
}

/*-------------------------------------------------------------------------------------------------
 * Unit name helpers
 *------------------------------------------------------------------------------------------------*/

const char *length_unit_name(LengthUnit unit)
{
    switch (unit)
    {
        case LENGTH_METER:      return "meter (m)";
        case LENGTH_KILOMETER:  return "kilometer (km)";
        case LENGTH_CENTIMETER: return "centimeter (cm)";
        case LENGTH_MILLIMETER: return "millimeter (mm)";
        case LENGTH_INCH:       return "inch (in)";
        case LENGTH_FOOT:       return "foot (ft)";
        case LENGTH_YARD:       return "yard (yd)";
        case LENGTH_MILE:       return "mile (mi)";
        default:                return "Unknown length unit";
    }
}

const char *weight_unit_name(WeightUnit unit)
{
    switch (unit)
    {
        case WEIGHT_KILOGRAM:   return "kilogram (kg)";
        case WEIGHT_GRAM:       return "gram (g)";
        case WEIGHT_MILLIGRAM:  return "milligram (mg)";
        case WEIGHT_POUND:      return "pound (lb)";
        case WEIGHT_OUNCE:      return "ounce (oz)";
        case WEIGHT_TONNE:      return "tonne (t)";
        default:                return "Unknown weight unit";
    }
}
