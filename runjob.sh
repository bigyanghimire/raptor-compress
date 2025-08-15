#!/bin/bash
#
#SBATCH --job-name=amg_rank_0
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --mem=32G
#SBATCH --time=2:00:00
#SBATCH --output=%x_%j.out
#SBATCH --error=%x_%j.err
