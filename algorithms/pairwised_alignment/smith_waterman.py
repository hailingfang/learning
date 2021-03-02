import argparse
from biolib import Fasta_parser, EDNAFULL, EBLOSUM62


def parse_args():
    """what?"""
    parser = argparse.ArgumentParser(prog='waterman', description='align two\
                                     sequence by smith waterman alogrithum.')
    parser.add_argument('-seqa', help='first sequence fasta file.', type=str,
                        required=True)
    parser.add_argument('-seqb', help='second sequence fasta file.', type=str,
                        required=True)
    parser.add_argument('-seq_type', choices=['nucl', 'prot'], help='sequence\
                        type inter nucl or prot', required=True)
    parser.add_argument('-gapopen', help='plenalty for a gap.', default=10,
                        type=float)
    parser.add_argument('gapextend', help='plenalty for extend a gap.',
                        default=0.5, type=float)
    args = parser.parse_args()
    seqa_f, seqb_f, seqtype, gapopen, gapextend = \
        args.seqa, args.seqb, args.seq_type, args.gapopen, args.gapextend
    return seqa_f, seqb_f, seqtype, gapopen, gapextend


def waterman(seq_a, seq_b, score_matrix, gapopen, gapexpand):
    
    pass


def main():
    seqa_f, seqb_f, seqtype, gapopen, gapexten = parse_args()
    seqa = Fasta_parser(seqa_f)
    seqb = Fasta_parser(seqb_f)
    seqa = seqa.data[seqa.heads[0]]
    seqb = seqb.data[seqb.heads[0]]
    print(seqa, seqb)


main()
