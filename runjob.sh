#!/bin/bash
#SBATCH --job-name=amg_job2
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=32
#SBATCH --mem=64G
#SBATCH --time=03:00:00
#SBATCH --output=slurm-%j.output
#SBATCH --error=slurm-%j.err

# Optional: load modules or activate environment
# rm -fr *.err *.out
module load spack
module load cuda/12.3.0
module load gcc/12.3.0
module load openmpi/5.0.1
module load anaconda3
module load cmake/3.27.9

cmake -B build -DCMAKE_BUILD_TYPE=Debug -DWITH_MPI=ON -DWITH_DOXYGEN=OFF -DCMAKE_BUILD_TYPE=Debug && \
cmake --build build --parallel $(nproc) 

# Recommended: enable core dumps for debugging
ulimit -c unlimited

# Run your application
mpirun -n 2 build/examples/example 1e-5 1e-5 1 $1
