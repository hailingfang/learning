#!/bin/bash

#PBS -N test_job #job name
#PBS -d /gpfs/home/cyguo/fanghailing/work/qsub-test #working directory
#PBS -q batch #queue
#PBS -l nodes=2:ppn=1,mem=5mb #apply 2 nodes, 1cpu and 5mb per node
#PBS -t 1-5 #task array id

echo task:$PBS_ARRAYID 1>stdo$PBS_ARRAYID 2>stde$PBS_ARRAYID

