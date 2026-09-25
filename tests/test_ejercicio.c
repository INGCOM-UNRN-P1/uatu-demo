#include <stdio.h>

#include "../src/ejercicio.h"

static int fallas = 0;

static void verificar(bool condicion, const char *descripcion)
{
    printf("[%s] %s\n", condicion ? " OK " : "FALLA", descripcion);
    if (!condicion)
    {
        fallas++;
    }
}

int main(void)
{
    verificar(fibonacci(0) == 0, "fibonacci(0) == 0");
    verificar(fibonacci(1) == 1, "fibonacci(1) == 1");
    verificar(fibonacci(10) == 55, "fibonacci(10) == 55");
    verificar(fibonacci(46) == 1836311903, "fibonacci(46) == 1836311903");

    verificar(!es_primo(0), "0 no es primo");
    verificar(!es_primo(1), "1 no es primo");
    verificar(es_primo(2), "2 es primo");
    verificar(es_primo(97), "97 es primo");
    verificar(!es_primo(91), "91 no es primo");
    verificar(!es_primo(-7), "los negativos no son primos");

    verificar(invertir_digitos(0) == 0, "invertir_digitos(0) == 0");
    verificar(invertir_digitos(1230) == 321, "invertir_digitos(1230) == 321");
    verificar(invertir_digitos(12345) == 54321, "invertir_digitos(12345) == 54321");

    printf("\n%d prueba(s) fallida(s)\n", fallas);
    return fallas == 0 ? 0 : 1;
}
