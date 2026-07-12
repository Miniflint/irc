def main():
    with open("error_codes.rfc", "r") as f:
        t:list[str] = f.readlines()
    for line in t:
        splitted = line.split(" \t")
        code = splitted[0]
        msg = splitted[1]
        rfc = splitted[2]
        try: 
            formatting = splitted[3]
        except:
            continue
        if (len(rfc) > 6 and rfc[0] == 'R'):
            print(f"\t{msg} = {code}, //{formatting}")

main()