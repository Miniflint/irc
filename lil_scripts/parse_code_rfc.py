def main():
    with open("error_codes.rfc", "r") as f:
        t:list[str] = f.readlines()
    for line in t:
        #print(line)
        splitted = line.split(" \t")
        code = splitted[0]
        msg = splitted[1]
        if (t[3] is not None):
            print(f"{msg} = {code},")

main()