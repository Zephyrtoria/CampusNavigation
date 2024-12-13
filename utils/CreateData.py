import csv
import random
import string


# 生成随机字符串的函数
def generate_random_string(length=6):
    return ''.join(random.choices(string.ascii_lowercase, k=length))


# 生成随机正整数的函数
def generate_random_integer(min_value=0, max_value=50):
    return random.randint(min_value, max_value)


# 写入CSV文件的函数
def create_nodes(nodes_file_name, num_rows):
    strings = []
    with open(nodes_file_name, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        # 写入随机数据
        for _ in range(num_rows):
            new_node = generate_random_string()
            strings.append(new_node)
            random_data = [
                new_node,
                generate_random_string(),
                generate_random_integer()
            ]
            writer.writerow(random_data)

    return strings


def create_edges(strings, edges_file_name, num_rows):
    with open(edges_file_name, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        for _ in range(num_rows * 2):
            element1, element2 = random.sample(strings, 2)
            integer = generate_random_integer(1, 500)
            writer.writerow([element1, element2, integer])


amount_desc = ["small", "medium", "large"]
amount_num = [10, 100, 1000]
# 配置文件名和行数
for i in range(3):
    nodes_file_name = "../resources/" + amount_desc[i] + "/nodes.csv"
    edges_file_name = "../resources/" + amount_desc[i] + "/edges.csv"
    num_rows = amount_num[i]
    strings = create_nodes(nodes_file_name, num_rows)
    create_edges(strings, edges_file_name, num_rows)
    print(f"随机数据已写入文件中！")
