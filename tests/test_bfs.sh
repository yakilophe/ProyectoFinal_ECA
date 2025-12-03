#!/bin/bash

# IMPORTANTE: El ejecutable compilado se encuentra en la carpeta de build, NO aquí.
EXECUTABLE="../grafo_ejecutable" 

# --- Prueba 1: Carga de Grafo Predefinido y BFS ---

EXPECTED_OUTPUT_PART="A B D E C"
INPUT_SEQUENCE="1\nA\n"

echo "--- Iniciando Prueba de Sistema: BFS en Grafo 1 desde A ---"

# Ejecuta el programa y le pasa la entrada simulada
OUTPUT_RESULT=$(echo -e "$INPUT_SEQUENCE" | $EXECUTABLE)

# Verifica la salida
if echo "$OUTPUT_RESULT" | grep -q "$EXPECTED_OUTPUT_PART"; then
    echo "✅ Prueba BFS PASSED: El recorrido esperado se encontró."
    exit 0
else
    echo "❌ Prueba BFS FAILED: El recorrido esperado no se encontró."
    echo "--- Salida Completa del Programa ---"
    echo "$OUTPUT_RESULT"
    echo "========================================"
    exit 1
fi
