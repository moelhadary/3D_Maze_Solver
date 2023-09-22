#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_HEIGHT 10
#define MAX_ROWS   10
#define MAX_COLS   10

typedef struct {
    int row, col, height;
} Cell;

typedef struct {
    Cell items[MAX_HEIGHT * MAX_ROWS * MAX_COLS];
    int front, rear;
} Queue;

void initQueue(Queue *queue) {
    queue->front = 0;
    queue->rear = -1;
}

bool isEmpty(Queue *queue) {
    return queue->front > queue->rear;
}

void enqueue(Queue *queue, Cell cell) {
    queue->items[++queue->rear] = cell;
}

Cell dequeue(Queue *queue) {
    return queue->items[queue->front++];
}

bool isValid(int height, int numRows, int numCols, int h, int r, int c) {
    return (h >= 0 && h < height && r >= 0 && r < numRows && c >= 0 && c < numCols);
}

bool solve3DMaze(int maze[MAX_HEIGHT][MAX_ROWS][MAX_COLS], int height, int numRows, int numCols, Cell start, Cell end) {
    Queue queue;
    initQueue(&queue);

    int dh[] = {1, -1, 0, 0, 0, 0}; // Possible moves in height dimension: up, down
    int dr[] = {0, 0, 1, -1, 0, 0}; // Possible moves in row dimension: left, right
    int dc[] = {0, 0, 0, 0, 1, -1}; // Possible moves in column dimension: forward, backward

    bool visited[MAX_HEIGHT][MAX_ROWS][MAX_COLS] = {false};
    int cost[MAX_HEIGHT][MAX_ROWS][MAX_COLS] = {0};

    enqueue(&queue, start);
    visited[start.height][start.row][start.col] = true;

    while (!isEmpty(&queue)) {
        Cell current = dequeue(&queue);

        if (current.row == end.row && current.col == end.col && current.height == end.height) {
            printf("Path found with cost: %d\n", cost[current.height][current.row][current.col]);
            return true;
        }

        for (int i = 0; i < 6; i++) {
            int newHeight = current.height + dh[i];
            int newRow = current.row + dr[i];
            int newCol = current.col + dc[i];

            if (isValid(height, numRows, numCols, newHeight, newRow, newCol) &&
                maze[newHeight][newRow][newCol] == 0 && !visited[newHeight][newRow][newCol]) {
                Cell neighbor = {newRow, newCol, newHeight};
                enqueue(&queue, neighbor);
                visited[newHeight][newRow][newCol] = true;
                cost[newHeight][newRow][newCol] = cost[current.height][current.row][current.col] + 1;
            }
        }
    }

    // printf("No path found.\n");
    return false;
}

int main() {
int maze[MAX_HEIGHT][MAX_ROWS][MAX_COLS] = {
    // Level 0 (height = 0)
    {
        // 10x10 maze
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Row 0
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 1}, // Row 1
        {1, 1, 0, 1, 1, 1, 1, 1, 1, 1}, // Row 2
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1}, // Row 3
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 1}, // Row 4
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // Row 5
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, // Row 6
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1}, // Row 7
        {1, 1, 1, 1, 0, 1, 1, 1, 0, 1}, // Row 8
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // Row 9
    },
    // Level 1 (height = 1)
    {
        // 10x10 maze (all walls to demonstrate a multi-level maze)
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Row 0
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Row 1
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Row 2
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Row 3
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Row 4
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Row 5
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Row 6
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Row 7
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Row 8
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Row 9
    },
};


int height = 2;      // Height of the 3D maze (number of levels)
int numRows = 10;    // Number of rows in each level
int numCols = 10;    // Number of columns in each level
Cell start = {0, 0, 0}; // Starting cell
Cell end = {9, 9, 0};   // Ending cell


    if (solve3DMaze(maze, height, numRows, numCols, start, end)) {
        // Path found
        printf("Path found!\n");
    } else {
        // No path found
        printf("No path found.\n");
    }

    return 0;
}
