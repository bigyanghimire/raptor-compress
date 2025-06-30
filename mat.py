from scipy.io import mmread
import numpy as np

# Read the MatrixMarket file
sparse_matrix = mmread('examples/LFAT5.mtx')

# Convert to a dense NumPy array
dense_matrix = sparse_matrix.toarray()

# Print the dense matrix in a human-readable way
np.set_printoptions(
    suppress=True,
    formatter={'float_kind': lambda x: f"{x:10g}"},  # 10 chars per number
    linewidth=200
)
print(dense_matrix)