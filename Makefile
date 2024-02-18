#*****************************************************************
# File:   Makefile
# Author: Manel Jorda Puig Rubio
# Date:   febrero 2024
# Coms:   Ejecutar "make" para compilar
#         Ejecutar "make clean" para limpiar (borrar lo que genere)
#*****************************************************************
#---------------------------------------------------------
# macros
RM = /bin/rm -f # para limpiar
CC = g++         # compilador
#---------------------------------------------------------
ARBOL_LIB=./arbol
ARBOL=${ARBOL_LIB}/arbol
#---------------------------------------------------------
# opciones compilación y enlazado ("linkado")
CPPFLAGS = -g -I. -I${ARBOL_LIB} -O2 -std=c++11 -fmax-errors=1 # opciones compilación
#---------------------------------------------------------
# vars
EJEC = huf
#
all: ${EJEC}
#---------------------------------------------------------
# compilar
${EJEC}.o: ${EJEC}.hh ${EJEC}.cc
	${CC} -c ${EJEC}.cc -o ${EJEC}.o ${CPPFLAGS}
#
${ARBOL}.o: ${ARBOL}.hh ${ARBOL}.cc
	${CC} -c ${ARBOL}.cc -o ${ARBOL}.o ${CPPFLAGS}
#
# "linkar"
#---------------------------------------------------------
${EJEC}: ${EJEC}.o ${ARBOL}.o
	${CC} ${EJEC}.o ${ARBOL}.o -o ${EJEC} ${CPPFLAGS}
#---------------------------------------------------------
# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	${RM} ${ARBOL}.o ${EJEC}.o ${EJEC}
