#!/bin/bash

#PBS -N qsub-example #task name
#PBS -q batch #queue
#PBS -l nodes=4:ppn=4,mem=16gb #4nodes, 4 cpus per node, 16GB per node
#PBS -t 1-40 #tast ids
#PBS -d /working/directory
#PBS -o /stdout/stdo
#pBS -e /stderr/stde

lines=()
while IFS=$'	' read -r line
do
    lines+=("${line}")
done < list.tsv
IFS=' ' read -r -a line <<< ${lines[${PBS_ARRAYID}] }
sample=${line[0]}
echo $sample

