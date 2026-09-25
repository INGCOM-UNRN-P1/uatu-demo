#ifndef EJERCICIO_H
#define EJERCICIO_H

#include <stdbool.h>

/**
 * Devuelve el n-ésimo número de Fibonacci (fibonacci(0) == 0, fibonacci(1) == 1).
 * Precondición: 0 <= n <= 46.
 */
int fibonacci(int n);

/**
 * Indica si n es un número primo.
 */
bool es_primo(int n);

/**
 * Devuelve n con sus dígitos en orden inverso (invertir_digitos(1230) == 321).
 * Precondición: n >= 0.
 */
int invertir_digitos(int n);

#endif
