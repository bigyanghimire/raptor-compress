from scipy.io import mmread
import numpy as np
def print_nonzero_submatrix(matrix, row_start, row_end, col_start, col_end):
    """
    Print non-zero values in a submatrix defined by row and column range.

    Parameters:
        matrix (scipy.sparse or np.ndarray): The matrix to extract from.
        row_start (int): Starting row index (inclusive).
        row_end (int): Ending row index (exclusive).
        col_start (int): Starting column index (inclusive).
        col_end (int): Ending column index (exclusive).
    """
    # Convert to dense if it's sparse
    if not isinstance(matrix, np.ndarray):
        matrix = matrix.toarray()

    submatrix = matrix[row_start:row_end, col_start:col_end]

    print(f"Non-zero values from rows {row_start} to {row_end - 1}, "
          f"columns {col_start} to {col_end - 1}:")

    rows, cols = submatrix.shape
    for i in range(rows):
        for j in range(cols):
            val = submatrix[i, j]
            if val != 0:
                print(f"({row_start + i}, {col_start + j}) = {val}")

np.set_printoptions(threshold=np.inf)
# Read the MatrixMarket file
sparse_matrix = mmread('examples/LFAT5.mtx')

# Convert to a dense NumPy array
dense_matrix = sparse_matrix.toarray()
#print("dense ",dense_matrix[1])
# Print the dense matrix in a human-readable way
np.set_printoptions(
    suppress=True,
    formatter={'float_kind': lambda x: f"{x:10g}"},  # 10 chars per number
    linewidth=200
)
#print_nonzero_submatrix(dense_matrix, 9997,19999, 0, 9997)
print(dense_matrix)