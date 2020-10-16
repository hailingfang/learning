#! /usr/bin/env python3


def lagest_common_subsequence(seq_a, seq_b):
    common_base_counter = {}
    for i in range(len(seq_a) + 1):
        common_base_counter[(i, 0)] = 0
    for j in range(1, len(seq_b) + 1):
        common_base_counter[(0, j)] = 0
    common_base_pos = {}
    i = 0
    for ele_a in seq_a:
        i += 1
        j = 0
        for ele_b in seq_b:
            j += 1
            if ele_a == ele_b:
                common_base_counter[(i, j)] = common_base_counter[(i - 1, j - 1)] + 1
                common_base_pos[(i, j)] = 0
            elif common_base_counter[(i-1, j)] > common_base_counter[(i, j - 1)]:
                common_base_counter[(i, j)] = common_base_counter[(i - 1, j)]
                common_base_pos[(i, j)] = 1
            elif common_base_counter[(i-1, j)] < common_base_counter[(i, j - 1)]:
                common_base_counter[(i, j)] = common_base_counter[(i, j - 1)]
                common_base_pos[(i, j)] = -1
            else:
                common_base_counter[(i, j)] = common_base_counter[i - 1, j]
                common_base_pos[(i, j)] = 2
    return common_base_counter, common_base_counter[(i, j)], common_base_pos


def construct_align(lcs, lcs_amount, common_base_pos):
    max_pos = []
    seq_a = []
    seq_b = []
    for ele in lcs:
        if lcs[ele] == lcs_amount:
            max_pos.append(ele)
    for pos in max_pos:
        while pos[0] > 0 and pos[1] > 0:
            direction = common_base_pos[pos]
            if direction == 0:
                seq_a.append(pos[0])
                seq_b.append(pos[1])
                pos = (pos[0] - 1, pos[1] - 1)
            elif direction == 1:
                seq_a.append(pos[0])
                seq_b.append('-')
                pos = (pos[0] - 1, pos[1])
            elif direction == -1:
                seq_a.append('-')
                seq_b.append(pos[1])
                pos = (pos[0], pos[1] - 1)
            else:
                seq_a.append(pos[0])
                seq_b.append(pos[1])
                pos = (pos[0] - 1, pos[1] - 1)
    print(seq_a, seq_b)
    return seq_a, seq_b


def output_res(seq_a, seq_a_align, seq_b, seq_b_align):
    for pos in seq_a_align[::-1]:
        if pos != '-':
            print(seq_a[pos - 1], end='')
        else:
            print(pos, end='')
    print()
    for pos in seq_b_align[::-1]:
        if pos != '-':
            print(seq_b[pos - 1], end='')
        else:
            print(pos, end='')
    print()
    return 0


def main():
    seq_a = 'CGAGCTGAACGGGCAATGCAGGAAGAGTTCTACCTGGAACTGAAAGAAGGCTTACTGGAGCCGCTGGCAGTGACGGAACG'
    seq_b = 'GAACGGTCAATGCGGAAGAGTTCTACCTGGAACTGGAAGGCTTACTGGAGCCGCTGGCAGTGACGGAACG'
    lcs, lcs_amount, common_base_pos = lagest_common_subsequence(seq_a, seq_b)
    print(lcs_amount, common_base_pos)
    seq_a_align, seq_b_align = construct_align(lcs, lcs_amount, common_base_pos)
    output_res(seq_a, seq_a_align, seq_b, seq_b_align)
    return 0


if __name__ == '__main__':
    main()
