#!/bin/bash
#SBATCH --job-name=amg_job
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=32
#SBATCH --mem=32G
#SBATCH --time=03:00:00
#SBATCH --output=slurm-%j.out
#SBATCH --error=slurm-%j.err

# Optional: load modules or activate environment
module load gcc openmpi

# Recommended: enable core dumps for debugging
ulimit -c unlimited

# Run your application
mpirun -n 2 build/examples/example 1e-5 1e-5 1
