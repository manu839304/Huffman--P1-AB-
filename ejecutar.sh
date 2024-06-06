#!/bin/bash

debug=0
if test $# -eq 1
then
    if test $1 = "-d"
    then
        debug=1
    fi        
fi

if test -f huf
then
    rm huf
    if test $debug -eq 1
    then    
        echo "ELIMINADO: antiguo ejecutable 'huf'"
    fi
fi

if test $debug -eq 1
then    
    echo "COMPILANDO: nuevo ejecutable 'huf'"
fi
g++ huf.cc -o huf -std=c++11

if test -d decodificados
then
    rm -r decodificados
    if test $debug -eq 1
    then    
        echo "ELIMINADO: antiguo directorio 'decodificados'"
    fi
fi

if test -d codificados
then
    rm -r codificados
    if test $debug -eq 1
    then    
        echo "ELIMINADO: antiguo directorio 'codificados'"
    fi
fi


mkdir decodificados
if test $debug -eq 1
then    
    echo "CREADO: nuevo directorio 'decodificados'"
fi

mkdir codificados
if test $debug -eq 1
then    
    echo "CREADO: nuevo directorio 'codificados'"
fi


for archivo in archivos_de_prueba/*
do
    cp $archivo decodificados
    if test $debug -eq 1
    then    
        echo "COPIADO: $archivo en 'decodificados'"
    fi
done

for archivo in decodificados/*
do
    ./huf -c $archivo
    if test $debug -eq 1
    then    
        echo "COMPRIMIDO: $archivo en 'decodificados'"
    fi
done

cp decodificados/*.huf codificados

for archivo_cod in $(ls decodificados/*.huf)
do
    ./huf -d $archivo_cod
    if test $debug -eq 1
    then    
        echo "DESCOMPRIMIDO: $archivo_cod en 'decodificados'"
    fi 
    rm $archivo_cod
    if test $debug -eq 1
    then    
        echo "ELIMINADO: $archivo_cod en 'decodificados'"
    fi
done

for archivo_decod in $(ls decodificados/*)
do
    if test $debug -eq 1
    then    
        echo ""
        echo "++ BUSCANDO: $archivo_decod"
    fi
    encontrado=0
    for archivo_orig in $(ls archivos_de_prueba/*)
    do  
        if test $debug -eq 1
        then    
            echo "COMPARANDO: $archivo_decod con $archivo_orig"
        fi
        cmp -s $archivo_decod $archivo_orig
        if test $? -eq 0
        then
            if test $debug -eq 1
            then    
                echo "FICHERO ENCONTRADO"
            fi
	        encontrado=1 
            break
        fi
    done
    
    if test $encontrado -eq 1
    then
        echo "-- EXITO: Archivo original ($archivo_orig) es igual al decodificado ($archivo_decod)"
    else
        echo "-- ERROR: $archivo_decod no es correcto"
    fi
done
