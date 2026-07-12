def main():
    with open("error_codes.rfc", "r") as f:
        t:list[str] = f.readlines()
    for line in t:
        #print(line)
        splitted = line.split(" \t")
        code = splitted[0]
        msg = splitted[1]
        test = splitted[2]
        if (len(test) > 6 and test[0] == 'R'):
            print(f"\t{msg} = {code},")

main()