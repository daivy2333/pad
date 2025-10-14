// main.rs

// 从 Rust 标准库导入必要的库。
// `HashMap` 用于创建从数字ID到其字符串描述的映射（例如，1 -> "有毛发"）。
// `HashSet` 用于存储已知事实的集合，防止重复并提供快速查找。
// `io` 用于处理来自命令行的用户输入。
use std::collections::{HashMap, HashSet};
use std::io;

/// 表示产生式系统中的单个 IF-THEN 规则。
/// 对于规则 "IF A and B THEN C"，A 和 B 是前件，C 是后件。
struct Rule {
    /// 一个数字ID向量，表示规则中"IF"部分的条件。
    antecedents: Vec<u32>,
    /// 规则中"THEN"部分结论的数字ID。
    consequent: u32,
}

/// 程序执行开始的主函数。
fn main() {
    // 1. 初始化知识库。此函数构建ID到描述的映射
    //    以及基于提供的文档的所有产生式规则列表。
    let (id_map, rules) = initialize_knowledge_base();

    // 2. 从用户获取初始事实集。此函数显示菜单
    //    并收集用户的输入。
    let initial_facts = get_user_facts(&id_map);

    // 如果用户没有输入任何事实，则没有内容需要处理，所以我们退出。
    if initial_facts.is_empty() {
        println!("没有提供任何前提条件，程序退出。");
        return;
    }

    // 3. 运行推理引擎。这是程序的核心，通过应用规则从现有事实中
    //    推导出新事实。它返回所有推导出的事实和推理日志。
    let (final_facts, log) = run_inference(&rules, &initial_facts, &id_map);

    // 4. 显示结果。此函数打印初始条件、逐步
    //    推理过程和最终结论（识别的动物）。
    display_results(&initial_facts, &final_facts, &log, &id_map);
}

/// 设置并返回系统的整个知识库。
/// 它包括所有条件ID到其文本描述的映射以及完整的推理规则集。
fn initialize_knowledge_base() -> (HashMap<u32, &'static str>, Vec<Rule>) {
    // 一个 HashMap，用于存储从ID（u32）到其字符串描述的映射。
    let mut id_map = HashMap::new();

    // --- 用所有已知条件填充映射 ---
    // 前提（可以由用户提供的事实）
    id_map.insert(1, "有毛发");
    id_map.insert(2, "产奶");
    id_map.insert(3, "有羽毛");
    id_map.insert(4, "会飞");
    id_map.insert(5, "会下蛋");
    id_map.insert(6, "吃肉");
    id_map.insert(7, "有犬齿");
    id_map.insert(8, "有爪");
    id_map.insert(9, "眼盯前方");
    id_map.insert(10, "有蹄");
    id_map.insert(11, "反刍");
    id_map.insert(12, "黄褐色");
    id_map.insert(13, "有斑点");
    id_map.insert(14, "有黑色条纹");
    id_map.insert(15, "长脖");
    id_map.insert(16, "长腿");
    id_map.insert(17, "不会飞");
    id_map.insert(18, "会游泳");
    id_map.insert(19, "黑白二色");
    id_map.insert(20, "善飞");

    // 中间结论（从其他事实推导出的事实）
    id_map.insert(21, "哺乳类");
    id_map.insert(22, "鸟类");
    id_map.insert(23, "食肉类");
    id_map.insert(24, "蹄类");

    // 最终结论（要识别的动物）
    id_map.insert(25, "金钱豹");
    id_map.insert(26, "虎");
    id_map.insert(27, "长颈鹿");
    id_map.insert(28, "斑马");
    id_map.insert(29, "鸵鸟");
    id_map.insert(30, "企鹅");
    id_map.insert(31, "信天翁");

    // --- 定义产生式规则 ---
    // 每个规则都创建为Rule结构体的实例。
    let rules = vec![
        // r1: IF 有毛发 THEN 是哺乳动物
        Rule { antecedents: vec![1], consequent: 21 },
        // r2: IF 产奶 THEN 是哺乳动物
        Rule { antecedents: vec![2], consequent: 21 },
        // r3: IF 有羽毛 THEN 是鸟
        Rule { antecedents: vec![3], consequent: 22 },
        // r4: IF 会飞 AND 会下蛋 THEN 是鸟
        Rule { antecedents: vec![4, 5], consequent: 22 },
        // r5: IF 吃肉 THEN 是食肉动物
        Rule { antecedents: vec![6], consequent: 23 },
        // r6: IF 有犬齿 AND 有爪 AND 眼盯前方 THEN 是食肉动物
        Rule { antecedents: vec![7, 8, 9], consequent: 23 },
        // r7: IF 是哺乳动物 AND 有蹄 THEN 是有蹄类动物
        Rule { antecedents: vec![21, 10], consequent: 24 },
        // r8: IF 是哺乳动物 AND 反刍 THEN 是有蹄类动物
        Rule { antecedents: vec![21, 11], consequent: 24 },
        // r9: IF 是哺乳动物 AND 是食肉动物 AND 黄褐色 AND 身上有暗斑点 THEN 是金钱豹
        Rule { antecedents: vec![21, 23, 12, 13], consequent: 25 },
        // r10: IF 是哺乳动物 AND 是食肉动物 AND 黄褐色 AND 有黑色条纹 THEN 是虎
        Rule { antecedents: vec![21, 23, 12, 14], consequent: 26 },
        // r11: IF 是蹄类动物 AND 有长脖 AND 有长腿 AND 身上有暗斑点 THEN 是长颈鹿
        Rule { antecedents: vec![24, 15, 16, 13], consequent: 27 },
        // r12: IF 是蹄类动物 AND 身上有黑条纹 THEN 是斑马
        Rule { antecedents: vec![24, 14], consequent: 28 },
        // r13: IF 是鸟 AND 有长脖 AND 有长腿 AND 不会飞 AND 有黑白二色 THEN 是鸵鸟
        Rule { antecedents: vec![22, 15, 16, 17, 19], consequent: 29 },
        // r14: IF 是鸟 AND 会游泳 AND 不会飞 AND 有黑白二色 THEN 是企鹅
        Rule { antecedents: vec![22, 18, 19, 17], consequent: 30 },
        // r15: IF 是鸟 AND 善飞 THEN 是信天翁
        Rule { antecedents: vec![22, 20], consequent: 31 },
    ];

    (id_map, rules)
}

/// 提示用户输入初始事实，并将它们作为HashSet返回。
fn get_user_facts(id_map: &HashMap<u32, &'static str>) -> HashSet<u32> {
    println!("************************************************************************");
    println!("请输入对应条件前面的数字:");

    // 以格式化的方式显示所有可能的初始条件（ID 1-20）。
    // 我们从1到20迭代，每行打印5个条件。
    for i in 1..=20 {
        // 我们在这里使用unwrap_or作为保护措施，尽管我们知道1-20的所有键都存在。
        // {:<12} 添加填充以对齐列。
        print!("*{:<2}: {:<12}", i, id_map.get(&i).unwrap_or(&""));
        if i % 5 == 0 {
            println!("*");
        }
    }
    println!("************************************************************************");
    println!("**********************当输入数字0时 程序结束**********************");

    // 这个HashSet将存储用户提供的事实。
    let mut user_facts = HashSet::new();
    loop {
        println!("请输入: ");
        let mut input = String::new();

        // 从用户输入中读取一行文本。
        io::stdin()
            .read_line(&mut input)
            .expect("Failed to read line");

        // 将输入字符串转换为数字（u32）。
        // `trim()` 移除任何前导/尾随空白字符（如换行符）。
        match input.trim().parse::<u32>() {
            Ok(num) => {
                // 如果用户输入0，循环终止。
                if num == 0 {
                    break;
                }
                // 我们只接受对应于初始前提（1-20）的数字。
                if num > 0 && num <= 20 {
                    // 如果值是新插入的，`insert` 返回 `true`。
                    if user_facts.insert(num) {
                        println!("已添加条件: {}", id_map.get(&num).unwrap_or(&"未知条件"));
                    } else {
                        println!("条件 {} 已存在.", id_map.get(&num).unwrap_or(&"未知条件"));
                    }
                } else {
                    println!("无效输入，请输入 1-20 之间的数字, 或输入 0 结束.");
                }
            }
            Err(_) => {
                // 这处理输入不是有效数字的情况。
                println!("无效输入，请输入一个数字.");
            }
        }
    }
    user_facts
}

/// 运行前向链接推理引擎。
/// 它接受规则和初始事实，并重复应用规则来推导新事实
/// 直到找不到更多新事实。
fn run_inference(
    rules: &Vec<Rule>,
    initial_facts: &HashSet<u32>,
    id_map: &HashMap<u32, &'static str>,
) -> (HashSet<u32>, Vec<String>) {
    // 克隆初始事实以创建我们的工作事实集。
    let mut facts = initial_facts.clone();
    // 一个向量，用于存储每个推理步骤的描述。
    let mut log = Vec::new();
    // 一个标志，用于跟踪在当前遍历中是否添加了新事实。
    // 我们从 `true` 开始，确保循环至少运行一次。
    let mut new_fact_added = true;

    // 这是推理引擎的主循环。只要新事实
    // 正在被推导，它就会继续。当对规则的完整遍历没有产生新事实时，
    // 推理过程就完成了。
    while new_fact_added {
        // 在每次遍历开始时重置标志。
        new_fact_added = false;

        // 遍历规则库中的每条规则。
        for rule in rules {
            // 优化：如果我们已经知道这条规则的结论，
            // 就没有必要检查其条件。我们可以跳到下一条规则。
            if facts.contains(&rule.consequent) {
                continue;
            }

            // 检查当前规则的所有条件（前件）是否存在于我们的事实库中。
            // `iter().all(...)` 是一种方便的方法，用于检查条件是否对迭代器中的所有项都成立。
            let all_antecedents_present = rule.antecedents.iter().all(|ant| facts.contains(ant));

            // 如果满足所有条件，我们就"触发"规则。
            if all_antecedents_present {
                // 1. 将新结论（后件）添加到我们的事实集中。
                facts.insert(rule.consequent);
                // 2. 将标志设置为true，表示我们应该再次运行循环
                //    因为事实集已经改变。
                new_fact_added = true;

                // 3. 创建一个日志条目来解释这个推理步骤。
                //    首先，获取所有前件事实的文本描述。
                let antecedent_descs: Vec<&str> = rule
                    .antecedents
                    .iter()
                    .map(|id| *id_map.get(id).unwrap_or(&"未知"))
                    .collect();
                //    然后，获取新结论的描述。
                let consequent_desc = *id_map.get(&rule.consequent).unwrap_or(&"未知");
                //    格式化日志条目并将其添加到我们的日志中。
                let log_entry = format!("{}->{}", antecedent_descs.join(", "), consequent_desc);
                log.push(log_entry);
            }
        }
    }

    // 返回最终的、完整的事实集和推理日志。
    (facts, log)
}

/// 以用户友好的格式显示推理过程的结果。
fn display_results(
    initial_facts: &HashSet<u32>,
    final_facts: &HashSet<u32>,
    log: &Vec<String>,
    id_map: &HashMap<u32, &'static str>,
) {
    println!("\n前提条件为:");
    // 收集用户提供的事实的初始描述。
    let initial_descs: Vec<&str> = initial_facts
        .iter()
        .map(|id| *id_map.get(id).unwrap_or(&""))
        .collect();
    // 将它们作为单行打印，用空格分隔。
    println!("{}", initial_descs.join(" "));

    println!("\n推理过程如下:");
    // 打印推理日志中的每个条目。
    for entry in log {
        println!("{}", entry);
    }

    // 推理后，检查是否达到了任何最终的动物结论（ID 25-31）。
    let mut final_animal_id = None;
    for id in 25..=31 {
        if final_facts.contains(&id) {
            final_animal_id = Some(id);
            break; // 找到第一个后停止。
        }
    }

    println!("\n所识别的动物为:");
    // 打印最终结果。
    match final_animal_id {
        Some(id) => println!("{}", id_map.get(&id).unwrap_or(&"未知动物")),
        None => println!("无法识别出任何动物。"),
    }
}