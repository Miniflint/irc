def parse(txt:list[str]):
	t = [line.strip() for line in txt]
	current = []
	for i, line in enumerate(t):
		if (line == "Syntax:"):
			try:
				hmm = t[i + 2].split()
				current.append("\t" + hmm[0] + ", // " + ' '.join(hmm))
			except (IndexError):
				pass
	with open("out.txt", "w") as f:
		for x in current:
			f.write(x + "\n")

def main():
	with open("output.txt", "r") as f:
		txt = f.readlines()
	parse(txt)

main()