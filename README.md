# Sudoku
Solving sudoku using C
 This is  
ALGORITHM:
Take a number from 1 , to insert.
Take a row and  column (start with 1st row and col) and check whether it has 0 or NULL.
To insert that number, check vertically,horizontally and matrix (i.e. The number should not placed in row,column and matrix  already)  
If it is already placed move to next column. If not ,insert it and move to next row.
Repeat same steps and fill all rows. 
If any row, that no column is possible to insert, then move back to previous row ,remove that number and place it in another possible place.(backtracking)
While backtracking when row becomes  1  there is no possible to go back. So,move to last row and remove  previous number and insert it in another possible place.  
Continue all steps .(Till number 9)     
