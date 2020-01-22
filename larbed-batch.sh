#!/bin/bash

#SBATCH --exclude=sem-icefield
#SBATCH --gres=gpu:1

export PATH=/usr/local/cuda:/usr/local/cuda/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/include/c++/5

export LD_LIBRARY_PATH=/usr/local/cuda/lib64:/usr/local/lib64:/usr/lib64

cd /testpool/ops/samfairman/larbedFengReview/input_data_preparation/

## run the actual reconstruction 
make -f Makefile

cd /testpool/ops/samfairman/larbedFengReview/input_data_preparation/bin
#time ./make_ar_test
#time ./make_diag_test
#time ./dump_ug_test
time ./simulate_intensity_test

##time ./pattern_to_image_test


