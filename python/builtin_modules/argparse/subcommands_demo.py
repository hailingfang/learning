import argparse

def getargs():
    parser = argparse.ArgumentParser(description="Subcommands Example")
    parser.add_argument("-t", "--tt", help="option for command")

    subparser = parser.add_subparsers(title="subcommands",
                                      description="vaild subcommands",
                                      prog="subcommands_demo.py",
                                      dest="subcommand",
                                      required=True,
                                      help="subcommands")

    subcommand_a = subparser.add_parser("command_a", help="subcommand a")
    subcommand_a.add_argument("-a", "--aa", help='options for command_a')

    subcommand_b = subparser.add_parser("command_b", help="subcommand b")
    subcommand_b.add_argument("-b", "--bb", help="options for command_b")

    args = parser.parse_args()
    subcommand = args.subcommand
    if subcommand == "command_a":
        return subcommand, (args.aa)
    elif subcommand == "command_b":
        return subcommand, (args.bb)    


def main():
    subcommand, args = getargs()
    print(f"subcommand: {subcommand}")
    print(f"args: {args}")

if __name__ == "__main__":
    main()