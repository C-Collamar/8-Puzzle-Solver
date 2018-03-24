# 8-Puzzle-Solver
An C-implementation solving the 8-puzzle problem using the uninformed search strategy _BFS (Breadth-First Search)_ and heusitic search strategy _A*_. The goal is to empirically compare both strategies' space and time performance.

For each strategy, the program collects and outputs the following information:
* sequence of moves corresponding to the solution (e.g. up, down, left, right)
* total number of nodes expanded
* total number of nodes generated
* length of the solution path (number of moves)

## Test Cases
**Goal board configuration**:
<table>
  <tr>
    <td>1</td>
    <td>2</td>
    <td>3</td>
  </tr>
  <tr>
    <td>8</td>
    <td>0</td>
    <td>4</td>
  </tr>
  <tr>
    <td>7</td>
    <td>6</td>
    <td>5</td>
  </tr>
</table>

**Initial board configurations**:
<table>
  <tr>
    <td>
      <table>
        <caption>Easy</caption>
        <tr>
          <td>1</td>
          <td>3</td>
          <td>4</td>
        </tr>
        <tr>
          <td>8</td>
          <td>6</td>
          <td>2</td>
        </tr>
        <tr>
          <td>7</td>
          <td>0</td>
          <td>5</td>
        </tr>
      </table>
    </td>
    <td>
      <table>
        <caption>Medium</caption>
        <tr>
          <td>2</td>
          <td>8</td>
          <td>1</td>
        </tr>
        <tr>
          <td>0</td>
          <td>4</td>
          <td>3</td>
        </tr>
        <tr>
          <td>7</td>
          <td>6</td>
          <td>5</td>
        </tr>
      </table>
    </td>
    <td>
      <table>
        <caption>Hard</caption>
        <tr>
          <td>2</td>
          <td>8</td>
          <td>1</td>
        </tr>
        <tr>
          <td>4</td>
          <td>6</td>
          <td>3</td>
        </tr>
        <tr>
          <td>7</td>
          <td>5</td>
          <td>0</td>
        </tr>
      </table>
    </td>
    <td>
      <table>
        <caption>Worst</caption>
        <tr>
          <td>5</td>
          <td>6</td>
          <td>7</td>
        </tr>
        <tr>
          <td>4</td>
          <td>0</td>
          <td>8</td>
        </tr>
        <tr>
          <td>3</td>
          <td>2</td>
          <td>1</td>
        </tr>
      </table>
    </td>
  </tr>
</table>

Notes:
* While A* performs well even on the worst case, the program crashes before the [BFS function][1] completes due to its memory-hogging nature. Tested as a 32-bit executable running on a 64-bit Windows® 7 OS with Intel® Core™ i5 and 8 GB RAM.
* While there are 9! total number of configurations possible to input, only half of them are solvable. Read more about the solvability of certain configurations of the n-puzzle in this Wikipedia [article][2] or in this MathWorld [explanation][3].

## Compilation
On Windows, compile and run using the following commands
```cmd
gcc main.c -o Solver.exe
Solver.exe
```
On Linux, compile and run using the following commands
```shell
gcc main.c -o Solver
./Solver
```

[1]: https://github.com/C-Collamar/8-Puzzle-Solver/blob/1ce3bfe8b8b2fdac013fd8fcfa9c851817fefdde/main.c#L61
[2]: https://en.wikipedia.org/wiki/15_puzzle#Solvability
[3]: http://mathworld.wolfram.com/15Puzzle.html
