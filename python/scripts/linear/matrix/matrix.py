'''
@Author: grehex
@Date: 2020-03-28 15:52:32
@LastEditTime: 2020-03-29 12:18:48
@Description: 
'''
import copy
import numpy

def array(lst):
    row = len(lst)
    col = len(lst[0])
    mat = Matrix(row, col)
    for i in range(row):
        if(len(lst[i]) != col):
            raise TypeError('column unmatched')
        mat.matrix[i][:] = lst[i][:]
    return mat

class Matrix:
    def __init__(self, row, column):
        self.row, self.column = row, column
        self.matrix = [[0 for _ in range(column)] for _ in range(row)]

    def __str__(self):
        return str(self.matrix)

    def __getitem__(self, indices):
        if isinstance(indices, tuple):
            slice_row = slice(indices[0], indices[0]+1) if isinstance(indices[0], int) \
                        else indices[0]
            slice_col = slice(indices[1], indices[1]+1) if isinstance(indices[1], int) \
                        else indices[1]        
            row_indices = range(*slice_row.indices(self.row))
            col_indices = range(*slice_col.indices(self.column))
            new_row, new_col = len(row_indices), len(col_indices)
            mat = Matrix(new_row, new_col)
            for row_dst, row_src in enumerate(row_indices):
                for col_dst, col_src in enumerate(col_indices):
                    mat.matrix[row_dst][col_dst] = self.matrix[row_src][col_src]
            return mat
        if isinstance(indices, slice):
            row = len(range(*indices.indices(self.row)))
            col = self.column
            mat = Matrix(row, col)
            mat.matrix[:] = self.matrix[indices]
            return mat
        if isinstance(indices, int):
            col = self.column
            mat = Matrix(1, col)
            mat.matrix[0] = self.matrix[indices]
            return mat

    def __setitem__(self, indices, vals):
        if isinstance(indices, slice):
            slice_row = indices
            slice_col = slice(self.column)
        elif isinstance(indices, tuple):
            slice_row = slice(indices[0], indices[0]+1) if isinstance(indices[0], int) \
                        else indices[0]
            slice_col = slice(indices[1], indices[1]+1) if isinstance(indices[1], int) \
                        else indices[1]
        elif isinstance(indices, int):
            slice_row = slice(indices, indices+1)
            slice_col = slice(self.column)
            print(slice_row, slice_col)             
        else:
            raise TypeError()
        row_indices = range(*slice_row.indices(self.row))
        col_indices = range(*slice_col.indices(self.column))
        row, col = len(row_indices), len(col_indices)
        if vals.row != row:
            raise TypeError('row unmatched')        
        for row_src, row_dst in enumerate(row_indices):
            if vals.column != col:
                raise TypeError('column unmatched')
            for col_src, col_dst in enumerate(col_indices):
                self.matrix[row_dst][col_dst] = vals.matrix[row_src][col_src]
            

    def __add__(self, other):
        if not isinstance(other, Matrix):
            raise TypeError('type error')
        if self.row != other.row or self.column != other.column:
            raise Exception('row and column matchs error')
        mat = Matrix(self.row, self.column)
        for row in range(self.row):
            for col in range(self.column):
                mat.matrix[row][col] = self.matrix[row][col] + other.matrix[row][col]
        return mat
    
    def __len__(self):
        return self.row

