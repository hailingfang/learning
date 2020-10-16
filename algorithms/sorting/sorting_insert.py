#! /usr/bin/env python3
"""
sorting argorithoms
"""


class Binary_tree:
    def __init__(self, value=None):
        self.value = value
        self.left = None
        self.right = None

    def add_node(self, value):
        if value <= self.value:
            if self.left is None:
                self.left = Binary_tree(value)
            else:
                self.left.add_node(value)
        else:
            if self.right is None:
                self.right = Binary_tree(value)
            else:
                self.right.add_node(value)

    def traverse(self):
        def recursive_func(node, container):
            if node.left:
                recursive_func(node.left, container)
                container.append(node.value)
            else:
                container.append(node.value)
            if node.right:
                recursive_func(node.right, container)
            return 0

        container = []
        recursive_func(self, container)
        return container


class Sorting:
    """soring methods class"""
    def sorting_insert_m1(self, num_list):
        dt_out = [num_list[0]]
        for ele in num_list[1:]:
            i = 0
            while True:
                if dt_out[i] > ele:
                    dt_out = dt_out[:i] + [ele] + dt_out[i:]
                    break
                i += 1
                if i == len(dt_out):
                    dt_out.append(ele)
                    break
        return dt_out

    def sorting_insert_m2(self, num_list):
        for i in range(1, len(num_list)):
            for j in range(i-1, -1, -1):
                if num_list[i] < num_list[j]:
                    num_list[i], num_list[j] = num_list[j], num_list[i]
                    i = j
                else:
                    break
        return 0

    def sorting_merge(self, num_list):
        def merge_list(l1, l2):
            l1_len = len(l1)
            l2_len = len(l2)
            dt_out = []
            i = j = 0
            while True:
                if i < l1_len and j < l2_len:
                    if l1[i] < l2[j]:
                        dt_out.append(l1[i])
                        i += 1
                    else:
                        dt_out.append(l2[j])
                        j += 1
                else:
                    break
            if i == l1_len:
                dt_out += l2[j:]
                pass
            elif j == l2_len:
                dt_out += l1[i:]
            else:
                raise Exception('Error1')
            return dt_out
            
        num_len = len(num_list)
        if num_len > 1:
            half_len = int(num_len/2)
            left_sub = num_list[:half_len]
            right_sub = num_list[half_len:]
            left_sorted = self.sorting_merge(left_sub)
            right_sorted = self.sorting_merge(right_sub)
            sorted_list = merge_list(left_sorted, right_sorted)
            return sorted_list
        else:
            return num_list

    def sorting_binary_tree(self, num_list):
        root = Binary_tree(num_list[0])
        num_list = num_list[1:]
        for i in num_list:
            root.add_node(i)
        res = root.traverse()

        return res


#  testing part  #
if __name__ == '__main__':
    from statistics import random as ran
    solution = Sorting()
    l_num = []
    for i in range(10):
        l_num.append(round(ran.uniform(1, 100)))
    print(l_num)
#    l_s = solution.sorting_insert_m1(l_num)
#    print(l_s)
#
#    l_num = []
#    for i in range(10):
#        l_num.append(round(ran.uniform(1, 100)))
#    print(l_num)
#    solution.sorting_insert_m2(l_num)
#    print(l_num)
#
#    l_num = []
#    for i in range(10):
#        l_num.append(round(ran.uniform(1, 100)))
#    print(l_num)
#    l_s = solution.sorting_merge(l_num)
#    print(l_s)
    res = solution.sorting_binary_tree(l_num)
    print(res)



