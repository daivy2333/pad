// main.rs

// 从标准库导入必要的集合。
// `BinaryHeap` 是一个优先队列，非常适合 A* 算法的"开放列表"。它将评分最高的节点保持在顶部。
// `HashMap` 用于高效存储从一个节点到另一个节点的路径（`came_from` 映射）和到达每个节点的成本（`g_score`）。
use std::collections::{BinaryHeap, HashMap};
// `cmp::Ordering` 用于实现我们优先队列所需的自定义比较逻辑。
use std::cmp::Ordering;

// 定义迷宫的尺寸。
const MAZE_WIDTH: usize = 5;
const MAZE_HEIGHT: usize = 5;

// 代表搜索网格中的一个节点。
#[derive(Debug, Copy, Clone, Eq, PartialEq)]
struct Node {
    // 节点在迷宫中的 (x, y) 坐标。
    position: (usize, usize),
    // f_score 是通过此节点的路径的总估计成本。
    // f_score = g_score（从起点开始的成本）+ h_score（到终点的启发式估计）。
    f_score: u32,
}

// A* 算法需要一个按 f_score 对节点进行排序的优先队列。
// Rust 中的 `BinaryHeap` 是一个最大堆，意味着它总是返回最大的项目。
// 为了让它表现得像一个最小堆（我们需要获取具有最低 f_score 的节点），
// 我们必须反转比较逻辑。
// 在这里，如果 `self` 的 `f_score` 比 `other` 低，`self.cmp(other)` 将返回 `Greater`，
// 实际上在堆的眼中使"最小"的项目变成"最大"。

impl Ord for Node {
    fn cmp(&self, other: &Self) -> Ordering {
        other.f_score.cmp(&self.f_score)
    }
}

impl PartialOrd for Node {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

/// 程序开始的 main 函数。
fn main() {
    // 根据实验文档定义迷宫布局。
    // 0 代表可行走路径，1 代表障碍物（墙壁）。
    let maze = [
        [0, 0, 0, 0, 0],
        [1, 0, 1, 0, 1],
        [0, 0, 0, 0, 1],
        [0, 1, 0, 0, 0],
        [0, 0, 0, 1, 0],
    ];

    // 定义迷宫的起点和终点。
    let start = (0, 0);
    let end = (4, 4);

    println!("Original Maze:");
    print_maze(&maze, &vec![]); // 首先打印不带路径的迷宫。

    // 调用 A* 搜索算法来找到路径。
    match a_star_search(&maze, start, end) {
        Some(path) => {
            println!("\nPath Found!");
            print_maze(&maze, &path);
        }
        None => {
            println!("\nNo path could be found from start to end.");
        }
    }
}

/// 实现 A* 搜索算法以在迷宫中找到最短路径。
/// 它返回一个 `Option<Vec<(usize, usize)>>`。如果找到路径，它返回 `Some(path)`，
/// 否则返回 `None`。
fn a_star_search(
    maze: &[[i32; MAZE_WIDTH]; MAZE_HEIGHT],
    start: (usize, usize),
    end: (usize, usize),
) -> Option<Vec<(usize, usize)>> {
    // "开放列表"：按 f_score 排序的待评估节点优先队列。
    let mut open_list = BinaryHeap::new();

    // `came_from` 映射存储路径。对于任何节点 `n`，`came_from[n]` 是从起点到 n 的最便宜路径上紧邻的前一个节点。
    let mut came_from: HashMap<(usize, usize), (usize, usize)> = HashMap::new();

    // `g_score` 映射存储从起点节点到任何给定节点的最便宜路径的成本。
    let mut g_score: HashMap<(usize, usize), u32> = HashMap::new();
    // 起始节点的 g_score 为 0。
    g_score.insert(start, 0);

    // 计算起始节点的初始 f_score 并将其推入开放列表。
    let start_f_score = heuristic(start, end);
    open_list.push(Node {
        position: start,
        f_score: start_f_score,
    });

    // 算法的主循环。只要开放列表中还有待评估的节点，它就会继续。
    while let Some(current_node) = open_list.pop() {
        let current_pos = current_node.position;

        // 如果我们已经到达终点，就完成了！现在可以重建路径了。
        if current_pos == end {
            return Some(reconstruct_path(came_from, current_pos));
        }

        // 探索当前节点的邻居（上、下、左、右）。
        for neighbor_pos in get_neighbors(current_pos, maze) {
            // 在此网格中，从一个节点到其邻居的距离始终为 1。
            let tentative_g_score = g_score.get(&current_pos).unwrap_or(&u32::MAX) + 1;

            // 如果这条到邻居的新路径比之前记录的任何路径更好...
            if tentative_g_score < *g_score.get(&neighbor_pos).unwrap_or(&u32::MAX) {
                // ...那么更新我们的记录。
                came_from.insert(neighbor_pos, current_pos);
                g_score.insert(neighbor_pos, tentative_g_score);

                // 计算邻居的 f_score 并将其添加到开放列表中进行评估。
                let f_score = tentative_g_score + heuristic(neighbor_pos, end);
                open_list.push(Node {
                    position: neighbor_pos,
                    f_score,
                });
            }
        }
    }

    // 如果循环结束而我们还没有到达终点，这意味着无法找到路径。
    None
}

/// 启发式函数（`h(n)`）：估计从一个节点到目标的成本。
/// 我们使用曼哈顿距离，这对于只能上、下、左、右移动的网格非常适用。
/// 它是 x 和 y 坐标绝对差值的总和。
fn heuristic(a: (usize, usize), b: (usize, usize)) -> u32 {
    ((a.0 as i32 - b.0 as i32).abs() + (a.1 as i32 - b.1 as i32).abs()) as u32
}

/// 获取给定节点的有效邻居。
/// 邻居是有效的，如果它在迷宫边界内并且是可走路径（不是障碍物）。
fn get_neighbors(
    pos: (usize, usize),
    maze: &[[i32; MAZE_WIDTH]; MAZE_HEIGHT],
) -> Vec<(usize, usize)> {
    let mut neighbors = Vec::new();
    let (x, y) = pos;

    // 四种可能的移动：上、下、左、右。
    let moves = [(-1, 0), (1, 0), (0, -1), (0, 1)];

    for (dx, dy) in moves.iter() {
        let new_x = x as i32 + dx;
        let new_y = y as i32 + dy;

        // 检查新位置是否在迷宫边界内。
        if new_x >= 0 && new_x < MAZE_WIDTH as i32 && new_y >= 0 && new_y < MAZE_HEIGHT as i32 {
            let nx = new_x as usize;
            let ny = new_y as usize;

            // 检查新位置是否可走（不是 '1'）。
            if maze[ny][nx] == 0 {
                neighbors.push((nx, ny));
            }
        }
    }
    neighbors
}

/// 从 `came_from` 映射重建路径，从终点开始
/// 向后追溯到起点。
fn reconstruct_path(
    came_from: HashMap<(usize, usize), (usize, usize)>,
    mut current: (usize, usize),
) -> Vec<(usize, usize)> {
    let mut path = vec![current];
    while let Some(&previous) = came_from.get(&current) {
        current = previous;
        path.push(current);
    }
    // 当前路径是从终点到起点的，所以我们将其反转。
    path.reverse();
    path
}

/// 将迷宫打印到控制台。
/// 它用 '*' 标记路径，用 '1' 标记障碍物，用 '0' 标记可走区域。
fn print_maze(maze: &[[i32; MAZE_WIDTH]; MAZE_HEIGHT], path: &[(usize, usize)]) {
    // 创建迷宫的可变副本以在上面绘制路径。
    let mut display_maze = [[' '; MAZE_WIDTH]; MAZE_HEIGHT];

    for y in 0..MAZE_HEIGHT {
        for x in 0..MAZE_WIDTH {
            display_maze[y][x] = if maze[y][x] == 1 { '1' } else { '0' };
        }
    }

    // 用星号标记路径。
    for &(x, y) in path {
        display_maze[y][x] = '*';
    }

    // 打印最终网格。
    for y in 0..MAZE_HEIGHT {
        for x in 0..MAZE_WIDTH {
            print!("  {}  ", display_maze[y][x]);
        }
        println!();
    }
}