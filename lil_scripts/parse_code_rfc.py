def main():
    with open("error_codes.rfc", "r") as f:
        t:list[str] = f.readlines()
    names = []
    functionNameCall = []
    functionNameServer = []
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
            #print(f"\t{msg} = {code}, //{formatting}")
            names.append(f'"{str(code)}"')
            functionNameCall.append(f"&Server::handle{msg.title().replace("_", "")}")
            functionNameServer.append(f"bool Server::handle{msg.title().replace("_", "")}(Client &c)")
    fullNames = ', '.join(names)
    fullFunctionNameCall = ', '.join(functionNameCall)
    fullfunctionNameServer = ';\n'.join(functionNameServer)

    print("const std::string[] = {" + fullNames + "}")
    print("const Server::replyMsg[] = {" + fullFunctionNameCall + "}")
    print(fullfunctionNameServer)


main()