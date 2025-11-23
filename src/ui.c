/***************************************************************************************************
 * Project: Unit Converter (Length & Weight)
 * File: ui.c
 * Author: Mobin Yousefi (GitHub: https://github.com/mobinyousefi-cs)
 * Created: 2025-11-23
 * Updated: 2025-11-23
 * License: MIT License (see LICENSE file for details)
 **************************************************************************************************/

#include "ui.h"
#include "converter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

/*-------------------------------------------------------------------------------------------------
 * Internal helpers: input handling
 *------------------------------------------------------------------------------------------------*/

#define INPUT_BUFFER_SIZE 128

static int read_line(char *buffer, size_t size)
{
    if (fgets(buffer, (int)size, stdin) == NULL)
    {
        return 0; /* EOF or error */
    }

    /* Remove trailing newline if present */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }

    return 1;
}

static int prompt_int(const char *prompt, int min, int max, int *out_value)
{
    char buffer[INPUT_BUFFER_SIZE];

    for (;;)
    {
        printf("%s", prompt);
        fflush(stdout);

        if (!read_line(buffer, sizeof(buffer)))
        {
            fprintf(stderr, "Error: failed to read input.\n");
            return 0;
        }

        errno = 0;
        char *endptr = NULL;
        long value = strtol(buffer, &endptr, 10);

        if (errno != 0 || endptr == buffer || *endptr != '\0')
        {
            printf("Invalid input. Please enter an integer.\n");
            continue;
        }

        if (value < min || value > max)
        {
            printf("Please enter a value between %d and %d.\n", min, max);
            continue;
        }

        *out_value = (int)value;
        return 1;
    }
}

static int prompt_double(const char *prompt, double *out_value)
{
    char buffer[INPUT_BUFFER_SIZE];

    for (;;)
    {
        printf("%s", prompt);
        fflush(stdout);

        if (!read_line(buffer, sizeof(buffer)))
        {
            fprintf(stderr, "Error: failed to read input.\n");
            return 0;
        }

        errno = 0;
        char *endptr = NULL;
        double value = strtod(buffer, &endptr);

        if (errno != 0 || endptr == buffer || *endptr != '\0')
        {
            printf("Invalid input. Please enter a numeric value.\n");
            continue;
        }

        *out_value = value;
        return 1;
    }
}

/*-------------------------------------------------------------------------------------------------
 * Internal helpers: menus
 *------------------------------------------------------------------------------------------------*/

static void print_banner(void)
{
    printf("============================================================\n");
    printf("             Unit Converter (Length & Weight)               \n");
    printf("============================================================\n");
}

static void print_main_menu(void)
{
    printf("\nMain Menu:\n");
    printf("  1) Length conversion\n");
    printf("  2) Weight conversion\n");
    printf("  0) Exit\n\n");
}

static void print_length_units(void)
{
    printf("\nLength Units:\n");
    for (int i = 0; i < LENGTH_UNIT_COUNT; ++i)
    {
        printf("  %d) %s\n", i + 1, length_unit_name((LengthUnit)i));
    }
    printf("\n");
}

static void print_weight_units(void)
{
    printf("\nWeight Units:\n");
    for (int i = 0; i < WEIGHT_UNIT_COUNT; ++i)
    {
        printf("  %d) %s\n", i + 1, weight_unit_name((WeightUnit)i));
    }
    printf("\n");
}

static void run_length_conversion(void)
{
    print_length_units();

    int from_index = 0;
    int to_index   = 0;

    if (!prompt_int("Select source unit (number): ",
                    1, LENGTH_UNIT_COUNT, &from_index))
    {
        return;
    }

    if (!prompt_int("Select target unit (number): ",
                    1, LENGTH_UNIT_COUNT, &to_index))
    {
        return;
    }

    double value = 0.0;
    if (!prompt_double("Enter value to convert: ", &value))
    {
        return;
    }

    LengthUnit from_unit = (LengthUnit)(from_index - 1);
    LengthUnit to_unit   = (LengthUnit)(to_index - 1);

    double result = convert_length(value, from_unit, to_unit);

    if (isnan(result))
    {
        printf("Conversion error: invalid units.\n");
        return;
    }

    printf("\nResult:\n");
    printf("  %f %s = %f %s\n\n",
           value,  length_unit_name(from_unit),
           result, length_unit_name(to_unit));
}

static void run_weight_conversion(void)
{
    print_weight_units();

    int from_index = 0;
    int to_index   = 0;

    if (!prompt_int("Select source unit (number): ",
                    1, WEIGHT_UNIT_COUNT, &from_index))
    {
        return;
    }

    if (!prompt_int("Select target unit (number): ",
                    1, WEIGHT_UNIT_COUNT, &to_index))
    {
        return;
    }

    double value = 0.0;
    if (!prompt_double("Enter value to convert: ", &value))
    {
        return;
    }

    WeightUnit from_unit = (WeightUnit)(from_index - 1);
    WeightUnit to_unit   = (WeightUnit)(to_index - 1);

    double result = convert_weight(value, from_unit, to_unit);

    if (isnan(result))
    {
        printf("Conversion error: invalid units.\n");
        return;
    }

    printf("\nResult:\n");
    printf("  %f %s = %f %s\n\n",
           value,  weight_unit_name(from_unit),
           result, weight_unit_name(to_unit));
}

/*-------------------------------------------------------------------------------------------------
 * Public API
 *------------------------------------------------------------------------------------------------*/

void run_converter(void)
{
    int running = 1;

    while (running)
    {
        print_banner();
        print_main_menu();

        int choice = 0;
        if (!prompt_int("Select an option: ", 0, 2, &choice))
        {
            /* On read error, terminate gracefully */
            break;
        }

        switch (choice)
        {
            case 1:
                run_length_conversion();
                break;

            case 2:
                run_weight_conversion();
                break;

            case 0:
                running = 0;
                printf("Exiting Unit Converter. Goodbye!\n");
                break;

            default:
                printf("Unknown option. Please try again.\n");
                break;
        }

        if (running)
        {
            printf("Press ENTER to continue...");
            char buffer[INPUT_BUFFER_SIZE];
            read_line(buffer, sizeof(buffer));
        }
    }
}
